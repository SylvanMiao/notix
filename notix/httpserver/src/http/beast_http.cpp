#include "beast_http.h"
#include "program_state_test.h"
#include "router.h"

http_connection::http_connection(tcp::socket socket) : _socket(std::move(socket))
{
  _request_parser.body_limit(MaxBodySize);
}

void http_connection::start()
{
  read_request();
  check_deadline();
}

void http_connection::read_request()
{
  auto self = shared_from_this();
  _request_parser.body_limit(MaxBodySize);
  http::async_read(_socket, _buffer, _request_parser,
          [self](beast::error_code ec, std::size_t bytes_transferred)
          {
            boost::ignore_unused(bytes_transferred);
            if (!ec)
            {
              self->_request = self->_request_parser.release();
              self->process_request();
              return;
            }

            if (ec == http::error::body_limit)
            {
              self->send_simple_error(http::status::payload_too_large, 1400,
                                      "request body too large");
              return;
            }

            self->log_transport_error("read_request", ec.message());
          });
}

void http_connection::check_deadline()
{
  auto self = shared_from_this();
  _timer.async_wait([self](boost::system::error_code ec)
                    {
      if (!ec){
        self->_socket.close(ec);
      } });
}

void http_connection::process_request()
{
  _request_start = std::chrono::steady_clock::now();
  _last_error_reason.clear();
  _response.body().clear();

  _response.version(_request.version());
  _response.keep_alive(false);
  _response.set(http::field::server, "Beast");

  const auto method = _request.method();
  const auto route_result = router::Router::default_router().match(method, _request.target());

  switch (method)
  {
  case http::verb::get:
  {
    _response.result(http::status::ok);
    if (route_result.kind == router::Router::match_kind::static_match)
    {
      create_get_response();
      break;
    }

    if (route_result.kind == router::Router::match_kind::dynamic_match)
    {
      create_dynamic_get_response(route_result.params);
      break;
    }

    send_error(http::status::not_found, 1404, "route not found");
    break;
  }

  case http::verb::post:
  {
    _response.result(http::status::ok);
    if (route_result.kind == router::Router::match_kind::static_match)
    {
      create_post_response();
      break;
    }

    if (route_result.kind == router::Router::match_kind::dynamic_match)
    {
      create_dynamic_post_response(route_result.params);
      break;
    }

    send_error(http::status::not_found, 1404, "route not found");
    break;
  }

  default:
    send_error(http::status::method_not_allowed, 1401,
               "invalid request method: " + std::string(_request.method_string()));
    break;
  }

  write_response();
}

void http_connection::create_get_response()
{
  const auto target = router::normalize_target(_request.target());

  if (target == router::CountRoute)
  {
    _response.set(http::field::content_type, "text/html");
    std::string html;
    if (program_state_test::load_text_file("static/count.html", html))
    {
      program_state_test::replace_all(html, "{{count}}", std::to_string(program_state_test::request_count()));
      beast::ostream(_response.body()) << html;
    }
    else
    {
      beast::ostream(_response.body())
          << "<html>\n"
          << "<head><title>Request count</title></head>\n"
          << "<body>\n"
          << "<h1>Request count</h1>\n"
          << "<p>There have been "
          << program_state_test::request_count()
          << " requests so far.</p>\n"
          << "</body>\n"
          << "</html>\n";
    }
  }
  else if (target == router::TimeRoute)
  {
    _response.set(http::field::content_type, "text/html");
    std::string html;
    if (program_state_test::load_text_file("static/time.html", html))
    {
      program_state_test::replace_all(html, "{{now}}", std::to_string(program_state_test::now()));
      beast::ostream(_response.body()) << html;
    }
    else
    {
      beast::ostream(_response.body())
          << "<html>\n"
          << "<head><title>Server Time</title></head>\n"
          << "<body>\n"
          << "<h1>Server Time</h1>\n"
          << "<p>Current unix timestamp: "
          << program_state_test::now()
          << "</p>\n"
          << "</body>\n"
          << "</html>\n";
    }
  }
  else
  {
    send_error(http::status::not_found, 1404, "route not found");
  }
}

void http_connection::create_post_response()
{
  const auto target = router::normalize_target(_request.target());
  if (target != router::EmailRoute)
  {
    send_error(http::status::not_found, 1404, "route not found");
    return;
  }

  Json::Value src_root;
  if (!parse_email_body(src_root))
  {
    return;
  }

  this->_response.set(http::field::content_type, "application/json; charset=utf-8");
  Json::Value root;
  auto email = src_root["email"].asString();
  std::cout << "email is " << email << std::endl;
  root["error"] = 0;
  root["email"] = src_root["email"];
  root["msg"] = "receive email post success";
  std::string jsonstr = root.toStyledString();
  beast::ostream(this->_response.body()) << jsonstr;
}

void http_connection::create_dynamic_get_response(const router::route_params &params)
{
  _response.set(http::field::content_type, "application/json; charset=utf-8");

  Json::Value root;
  root["error"] = 0;
  root["route"] = "dynamic";
  root["timestamp"] = static_cast<Json::Int64>(program_state_test::now());

  auto zone_it = params.find("zone");
  root["zone"] = zone_it != params.end() ? zone_it->second : "unknown";

  beast::ostream(_response.body()) << root.toStyledString();
}

void http_connection::create_dynamic_post_response(const router::route_params &params)
{
  Json::Value src_root;
  if (!parse_email_body(src_root))
  {
    return;
  }

  _response.set(http::field::content_type, "application/json; charset=utf-8");

  Json::Value root;
  root["error"] = 0;
  root["route"] = "dynamic";
  root["email"] = src_root["email"];

  auto source_it = params.find("source");
  root["source"] = source_it != params.end() ? source_it->second : "unknown";
  root["msg"] = "receive dynamic email post success";

  beast::ostream(_response.body()) << root.toStyledString();
}

bool http_connection::parse_email_body(Json::Value &src_root)
{
  if (!is_json_content_type())
  {
    send_error(http::status::unsupported_media_type, 1415,
               "content-type must be application/json");
    return false;
  }

  if (_request.body().size() == 0)
  {
    send_error(http::status::bad_request, 1402, "request body is empty");
    return false;
  }

  auto &body = this->_request.body();
  auto body_str = boost::beast::buffers_to_string(body.data());
  std::cout << "receive body is " << body_str << std::endl;

  Json::Reader reader;
  const bool parse_success = reader.parse(body_str, src_root);
  if (!parse_success)
  {
    send_error(http::status::bad_request, 1001, "invalid json body");
    return false;
  }

  if (!src_root.isMember("email") || !src_root["email"].isString() ||
      src_root["email"].asString().empty())
  {
    send_error(http::status::bad_request, 1002,
               "field 'email' is required and must be a non-empty string");
    return false;
  }

  return true;
}

void http_connection::write_response()
{
  auto self = shared_from_this();
  _response.content_length(_response.body().size());
  http::async_write(
      _socket,
      _response,
      [self](beast::error_code ec, std::size_t)
      {
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                              std::chrono::steady_clock::now() - self->_request_start)
                              .count();
        std::cout << "[HTTP] " << self->_request.method_string() << " "
                  << self->_request.target() << " status="
                  << static_cast<unsigned>(self->_response.result_int())
                  << " cost_ms=" << elapsed_ms;
        if (!self->_last_error_reason.empty())
        {
          std::cout << " error=\"" << self->_last_error_reason << "\"";
        }
        if (ec)
        {
          std::cout << " write_error=\"" << ec.message() << "\"";
        }
        std::cout << std::endl;

        self->_socket.shutdown(tcp::socket::shutdown_send, ec);
        self->_timer.cancel();
      });
}

void http_connection::send_simple_error(http::status status, int error_code, const std::string &message)
{
  _request_start = std::chrono::steady_clock::now();
  _response.version(11);
  _response.keep_alive(false);
  _response.set(http::field::server, "Beast");
  send_error(status, error_code, message);
  write_response();
}

void http_connection::send_error(http::status status, int error_code, const std::string &message)
{
  _response.result(status);
  _response.set(http::field::content_type, "application/json; charset=utf-8");
  _last_error_reason = message;

  _response.body().clear();
  Json::Value root;
  root["error"] = error_code;
  root["message"] = message;
  root["status"] = static_cast<int>(status);
  beast::ostream(_response.body()) << root.toStyledString();
}

bool http_connection::is_json_content_type() const
{
  if (!_request.base().count(http::field::content_type))
  {
    return false;
  }

  std::string content_type(_request[http::field::content_type]);
  std::transform(content_type.begin(), content_type.end(), content_type.begin(),
                 [](unsigned char c)
                 { return static_cast<char>(std::tolower(c)); });
  return content_type.find("application/json") != std::string::npos;
}

void http_connection::log_transport_error(const std::string &phase, const std::string &error)
{
  std::cout << "[HTTP] transport_error phase=" << phase << " reason=\""
            << error << "\"" << std::endl;
}
