#include "HttpConnection.h"

HttpConnection::HttpConnection(tcp::socket socket): _socket(std::move(socket))
{
}

void HttpConnection::Start()
{
  auto self = shared_from_this();
  http::async_read(_socket, _buffer, _request, [self](beast::error_code ec,
      std::size_t bytes_transferred) {
          try {
              if (ec) {
                  std::cout << "http read err is " << ec.what() << std::endl;
                  return;
              }
              //处理读到的数据
              boost::ignore_unused(bytes_transferred);
              self->HandleReq();
              self->CheckDeadline();
          }
          catch (std::exception& exp) {
              std::cout << "exception is " << exp.what() << std::endl;
          }
      }
  );
}
