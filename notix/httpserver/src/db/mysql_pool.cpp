#include "db/mysql_pool.h"

#include <iostream>
#include <mutex>
#include <stdexcept>

namespace
{
  std::once_flag g_mysql_init_flag;
}

MysqlPool::ConnectionGuard::ConnectionGuard(MysqlPool *pool, MYSQL *conn)
    : pool_(pool), conn_(conn)
{
}

MysqlPool::ConnectionGuard::~ConnectionGuard()
{
  if (pool_ && conn_)
  {
    pool_->release(conn_);
  }
}

MYSQL *MysqlPool::ConnectionGuard::get() const
{
  return conn_;
}

MysqlPool::MysqlPool(const MysqlConfig &config) : config_(config)
{
  std::call_once(g_mysql_init_flag, []()
                 { mysql_library_init(0, nullptr, nullptr); });
}

MysqlPool::~MysqlPool()
{
  std::lock_guard<std::mutex> lock(mutex_);
  while (!idle_.empty())
  {
    mysql_close(idle_.front());
    idle_.pop();
  }
}

MysqlPool::ConnectionGuard MysqlPool::acquire()
{
  std::unique_lock<std::mutex> lock(mutex_);
  if (!idle_.empty())
  {
    MYSQL *conn = idle_.front();
    idle_.pop();
    return ConnectionGuard(this, conn);
  }

  if (created_ < config_.pool_size)
  {
    ++created_;
    lock.unlock();
    MYSQL *conn = create_connection();
    if (!conn)
    {
      lock.lock();
      --created_;
      lock.unlock();
      throw std::runtime_error("mysql connection create failed");
    }
    return ConnectionGuard(this, conn);
  }

  cv_.wait(lock, [this]()
           { return !idle_.empty(); });
  MYSQL *conn = idle_.front();
  idle_.pop();
  return ConnectionGuard(this, conn);
}

MYSQL *MysqlPool::create_connection()
{
  MYSQL *conn = mysql_init(nullptr);
  if (!conn)
  {
    return nullptr;
  }

  unsigned int timeout = config_.connect_timeout_sec;
  mysql_options(conn, MYSQL_OPT_CONNECT_TIMEOUT, &timeout);

  if (!mysql_real_connect(conn,
                          config_.host.c_str(),
                          config_.user.c_str(),
                          config_.password.c_str(),
                          config_.database.c_str(),
                          config_.port,
                          nullptr,
                          0))
  {
    std::cerr << "mysql connect failed: " << mysql_error(conn) << std::endl;
    mysql_close(conn);
    return nullptr;
  }

  mysql_set_character_set(conn, "utf8mb4");
  return conn;
}

void MysqlPool::release(MYSQL *conn)
{
  std::lock_guard<std::mutex> lock(mutex_);
  idle_.push(conn);
  cv_.notify_one();
}
