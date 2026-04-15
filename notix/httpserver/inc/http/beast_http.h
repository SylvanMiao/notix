#pragma once
#include "global.h"
#include "router.h"
#include <iostream>

/*
beast的http类
*/
class http_connection : public std::enable_shared_from_this<http_connection>
{
public:
  static constexpr std::size_t MaxBodySize = 1024 * 1024; // 1MB

  /**
   * @brief 构造一个 HTTP 连接对象。
   * @param socket 已建立的 TCP socket，将被移动到连接对象内部管理。
   */
  http_connection(tcp::socket socket);

  /**
   * @brief 启动连接处理流程。
   *
   * 会触发异步读取请求并启动超时检测。
   * 即 read_request 与 check_deadline
   */
  void start();

  /**
   * @brief 异步读取 HTTP 请求。
   *
   * 内部会应用请求体大小限制，并在读取完成后进入请求处理逻辑。
   */
  void read_request();

  // 检查超时连接
  /**
   * @brief 检查连接超时并在必要时关闭连接。
   */
  void check_deadline();

  /**
   * @brief 根据 HTTP Method 分发请求。
   *        目前支持get与post
   */
  void process_request();

  // get消息路由
  /**
   * @brief 处理 GET 请求路由并构造响应。
   */
  void create_get_response();

  /**
   * @brief 处理 POST 请求路由并构造响应。
   */
  void create_post_response();

  /**
   * @brief 处理动态 GET 路由并构造响应。
   */
  void create_dynamic_get_response(const router::route_params &params);

  /**
   * @brief 处理动态 POST 路由并构造响应。
   */
  void create_dynamic_post_response(const router::route_params &params);

  /**
   * @brief 将响应异步写回客户端并记录访问日志。
   */
  void write_response();

  /**
   * @brief 在读取阶段等早期错误场景下返回简化错误响应。
   * @param status HTTP 状态码。
   * @param error_code 业务错误码。
   * @param message 错误描述。
   */
  void send_simple_error(http::status status, int error_code, const std::string &message);

  /**
   * @brief 构造统一 JSON 错误响应。
   * @param status HTTP 状态码。
   * @param error_code 业务错误码。
   * @param message 错误描述。
   */
  void send_error(http::status status, int error_code, const std::string &message);

  /**
   * @brief 判断请求的 Content-Type 是否为 JSON。
   * @return true 表示 Content-Type 包含 application/json；否则返回 false。
   */
  bool is_json_content_type() const;

  /**
   * @brief 解析并校验 email JSON 请求体。
   * @param src_root 解析后的 JSON 对象。
   * @return true 表示成功；false 表示已写入错误响应。
   */
  bool parse_email_body(Json::Value &src_root);

  /**
   * @brief 记录传输层错误日志。
   * @param phase 错误发生阶段（如 read/write）。
   * @param error 错误信息文本。
   */
  void log_transport_error(const std::string &phase, const std::string &error);

private:
  tcp::socket _socket;
  beast::flat_buffer _buffer{8192};
  http::request_parser<http::dynamic_body> _request_parser;
  http::request<http::dynamic_body> _request;
  http::response<http::dynamic_body> _response;
  std::chrono::steady_clock::time_point _request_start;
  std::string _last_error_reason;
  // 定时器
  net::steady_timer _timer{
      _socket.get_executor(), std::chrono::seconds(60)};
};
