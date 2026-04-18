#pragma once

#include <mysql/mysql.h>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <string>

struct MysqlConfig
{
  std::string host;
  unsigned int port{3306};
  std::string user;
  std::string password;
  std::string database;
  unsigned int pool_size{8};
  unsigned int connect_timeout_sec{5};
};

class MysqlPool
{
public:
  class ConnectionGuard
  {
  public:
    ConnectionGuard(MysqlPool *pool, MYSQL *conn);
    ~ConnectionGuard();

    ConnectionGuard(const ConnectionGuard &) = delete;
    ConnectionGuard &operator=(const ConnectionGuard &) = delete;

    MYSQL *get() const;

  private:
    MysqlPool *pool_;
    MYSQL *conn_;
  };

  explicit MysqlPool(const MysqlConfig &config);
  ~MysqlPool();

  MysqlPool(const MysqlPool &) = delete;
  MysqlPool &operator=(const MysqlPool &) = delete;

  ConnectionGuard acquire();

private:
  MYSQL *create_connection();
  void release(MYSQL *conn);

  MysqlConfig config_;
  std::mutex mutex_;
  std::condition_variable cv_;
  std::queue<MYSQL *> idle_;
  unsigned int created_{0};
};
