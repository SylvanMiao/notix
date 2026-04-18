#include "session/session_manager.h"

#include <cstring>
#include <iostream>
#include <sstream>

MysqlSessionStorage::MysqlSessionStorage(std::shared_ptr<MysqlPool> pool) : pool_(std::move(pool))
{
}

bool MysqlSessionStorage::ensure_table()
{
  if (table_ready_)
  {
    return true;
  }

  auto guard = pool_->acquire();
  MYSQL *conn = guard.get();
  const char *sql =
      "CREATE TABLE IF NOT EXISTS sessions ("
      "session_id VARCHAR(64) PRIMARY KEY,"
      "user_id VARCHAR(64) NOT NULL,"
      "data_json TEXT,"
      "last_active BIGINT NOT NULL,"
      "expires_at BIGINT NOT NULL"
      ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;";

  if (mysql_real_query(conn, sql, std::strlen(sql)) != 0)
  {
    std::cerr << "create sessions table failed: " << mysql_error(conn) << std::endl;
    return false;
  }

  table_ready_ = true;
  return true;
}

std::string MysqlSessionStorage::escape(MYSQL *conn, const std::string &input)
{
  std::string escaped;
  escaped.resize(input.size() * 2 + 1);
  unsigned long len = mysql_real_escape_string(conn, &escaped[0], input.c_str(), input.size());
  escaped.resize(len);
  return escaped;
}

bool MysqlSessionStorage::save(const SessionRecord &session)
{
  if (!ensure_table())
  {
    return false;
  }

  auto guard = pool_->acquire();
  MYSQL *conn = guard.get();

  const auto session_id = escape(conn, session.session_id);
  const auto user_id = escape(conn, session.user_id);
  const auto data_json = escape(conn, session.data_json);

  std::ostringstream ss;
  ss << "INSERT INTO sessions (session_id, user_id, data_json, last_active, expires_at) VALUES ('"
     << session_id << "','" << user_id << "','" << data_json << "'," << session.last_active_epoch
     << "," << session.expires_at_epoch << ") "
     << "ON DUPLICATE KEY UPDATE "
     << "user_id=VALUES(user_id), data_json=VALUES(data_json), last_active=VALUES(last_active), "
     << "expires_at=VALUES(expires_at);";

  const auto sql = ss.str();
  if (mysql_real_query(conn, sql.c_str(), sql.size()) != 0)
  {
    std::cerr << "save session failed: " << mysql_error(conn) << std::endl;
    return false;
  }

  return true;
}

std::optional<SessionRecord> MysqlSessionStorage::load(const std::string &session_id)
{
  if (!ensure_table())
  {
    return std::nullopt;
  }

  auto guard = pool_->acquire();
  MYSQL *conn = guard.get();
  const auto safe_id = escape(conn, session_id);

  std::ostringstream ss;
  ss << "SELECT user_id, data_json, last_active, expires_at FROM sessions WHERE session_id='"
     << safe_id << "' LIMIT 1;";
  const auto sql = ss.str();

  if (mysql_real_query(conn, sql.c_str(), sql.size()) != 0)
  {
    std::cerr << "load session failed: " << mysql_error(conn) << std::endl;
    return std::nullopt;
  }

  MYSQL_RES *res = mysql_store_result(conn);
  if (!res)
  {
    return std::nullopt;
  }

  MYSQL_ROW row = mysql_fetch_row(res);
  if (!row)
  {
    mysql_free_result(res);
    return std::nullopt;
  }

  SessionRecord record;
  record.session_id = session_id;
  record.user_id = row[0] ? row[0] : "";
  record.data_json = row[1] ? row[1] : "";
  record.last_active_epoch = row[2] ? std::stoll(row[2]) : 0;
  record.expires_at_epoch = row[3] ? std::stoll(row[3]) : 0;

  mysql_free_result(res);
  return record;
}

bool MysqlSessionStorage::remove(const std::string &session_id)
{
  if (!ensure_table())
  {
    return false;
  }

  auto guard = pool_->acquire();
  MYSQL *conn = guard.get();
  const auto safe_id = escape(conn, session_id);

  std::ostringstream ss;
  ss << "DELETE FROM sessions WHERE session_id='" << safe_id << "';";
  const auto sql = ss.str();

  if (mysql_real_query(conn, sql.c_str(), sql.size()) != 0)
  {
    std::cerr << "remove session failed: " << mysql_error(conn) << std::endl;
    return false;
  }

  return true;
}

void MysqlSessionStorage::cleanup_expired(std::int64_t now_epoch)
{
  if (!ensure_table())
  {
    return;
  }

  auto guard = pool_->acquire();
  MYSQL *conn = guard.get();

  std::ostringstream ss;
  ss << "DELETE FROM sessions WHERE expires_at < " << now_epoch << ";";
  const auto sql = ss.str();
  mysql_real_query(conn, sql.c_str(), sql.size());
}
