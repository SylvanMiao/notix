#pragma once
#include "const.h"
#include "HttpConnection.h"

// 服务器类，使用 enable_shared_from_this 以便在异步操作中安全地获取 shared_ptr
class CServer : public std::enable_shared_from_this<CServer>
{
public:
    CServer(boost::asio::io_context &ioc, unsigned short& port);
    void Start();
private:
    tcp::acceptor _acceptor;
    net::io_context& _ioc;
    tcp::socket _socket;
};