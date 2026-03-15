#pragma once

#include <beast/http.hpp>
#include <beast.hpp>
#include <asio.hpp>
#include <memory>
#include <iostream>
namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
