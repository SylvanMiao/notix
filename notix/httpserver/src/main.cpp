#include "beast_http.h"

void http_server(tcp::acceptor &acceptor)
{
  acceptor.async_accept(
      [&acceptor](boost::system::error_code ec, tcp::socket socket)
      {
        if (!ec)
        {
          std::make_shared<http_connection>(std::move(socket))->start();
        }
        http_server(acceptor);
      });
}


int main()
{
  try
  {
    auto const address = net::ip::make_address("127.0.0.1");
    unsigned short port = static_cast<unsigned short>(8080);
    net::io_context ioc{1};
    tcp::acceptor acceptor{ioc, {address, port}};
    http_server(acceptor);
    ioc.run();
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
    return EXIT_FAILURE;
  }
}