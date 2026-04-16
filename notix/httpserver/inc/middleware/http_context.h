#pragma once

#include "global.h"
#include "router.h"

namespace middleware
{
  /**
   * @brief 中间件统一上下文（适配 Beast 请求生命周期）
   *
   * 将底层 request/response、路由匹配结果和共享状态打包，避免中间件直接依赖
   * `router::dynamic_route` 这种“规则类型”。
   */
  struct HttpContext
  {
    http::request<http::dynamic_body> &request;
    http::response<http::dynamic_body> &response;
    const router::Router::match_result &route_match;
    std::string &last_error_reason;

    bool terminated{false};

    HttpContext(http::request<http::dynamic_body> &req,
                http::response<http::dynamic_body> &res,
                const router::Router::match_result &match,
                std::string &error_reason_ref)
        : request(req), response(res), route_match(match), last_error_reason(error_reason_ref)
    {
    }

    /** @brief 获取规范化请求路径 */
    std::string target() const
    {
      return router::normalize_target(request.target());
    }

    /** @brief 获取请求方法 */
    http::verb method() const
    {
      return request.method();
    }

    /** @brief 终止后续中间件与路由处理 */
    void stop()
    {
      terminated = true;
    }
  };
}
