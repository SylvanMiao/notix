#include "Cserver.h"

CServer::CServer(boost::asio::io_context &ioc, unsigned short &port):
  _ioc(ioc), _acceptor(ioc, tcp::endpoint(tcp::v4(), port)), _socket(_ioc)
{

}

void CServer::Start(){
  auto self = shared_from_this();
  _acceptor.async_accept(_socket, [self](beast::error_code ec){
    try{
      //  出错的情况下放弃这个连接，继续监听其他连接
      if (ec) {
        self->Start();
        return;
      }
      // 创建新连接，并且创建HttpConnection类来管理这个连接
      std::make_shared<HttpConnection>(std::move(_socket))->Start();
      
      // 继续监听
      self->Start();

    }catch (std::exception &e){
      
    }
  });

}
