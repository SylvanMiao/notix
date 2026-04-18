#pragma once

#include "router_rules.h"
#include <string>
#include <string_view>
#include <vector>

namespace router
{
  /**
   * @brief 路由分发器
   *
   * 负责组合静态路由与动态路由规则，向上层提供统一的匹配入口
   */
  class Router
  {
  public:
    /**
     * @brief 路由匹配结果类型
     */
    enum class match_kind
    {
      none,         ///< 未匹配到任何路由
      static_match, ///< 命中静态路由
      dynamic_match ///< 命中动态路由
    };

    /**
     * @brief 路由匹配返回值
     */
    struct match_result
    {
      match_kind kind{match_kind::none};             ///< 匹配结果类型
      static_route static_target{static_route::none}; ///< 静态路由类型（仅 static_match 时有效）
      dynamic_route_id dynamic_target{dynamic_route_id::none}; ///< 动态路由类型（仅 dynamic_match 时有效）
      route_params params{};                         ///< 动态参数（仅 dynamic_match 时有效）
    };

    /**
     * @brief 构造 Router，并初始化默认动态路由规则
     */
    Router();

    /**
     * @brief 在动态路由注册表中增加规则
     * @param method 路由对应的 HTTP 方法
     * @param pattern 动态路由模板（示例：`/time/{zone}`）
     */
    void add_dynamic_route(dynamic_route_id id, http::verb method, std::string pattern);

    /**
     * @brief 匹配请求路由
     *
     * 匹配顺序为：静态路由优先，动态路由次之
     *
     * @param method 请求 HTTP 方法
     * @param target 请求路径（可包含 query，内部会规范化）
     * @return match_result 匹配结果与可能的动态参数
     */
    match_result match(http::verb method, std::string_view target) const;

    /**
     * @brief 获取默认路由器单例
     * @return const Router& 默认 Router 实例引用
     */
    static const Router &default_router();

  private:
    std::vector<dynamic_route> dynamic_routes_;
  };
}
