#pragma once

#include "global.h"
#include <string>
#include <string_view>
#include <unordered_map>

namespace router
{

    using route_params = std::unordered_map<std::string, std::string>;

	enum class static_route
	{
		none,
		count,
		time,
		email
	};

    struct dynamic_route
	{
		http::verb method;
		std::string pattern;
	};


	inline constexpr std::string_view CountRoute = "/count";
	inline constexpr std::string_view TimeRoute = "/time";
	inline constexpr std::string_view EmailRoute = "/email";
    inline constexpr std::string_view TimeByZoneRoute = "/time/{zone}";
	inline constexpr std::string_view EmailBySourceRoute = "/email/{source}";

	/**
	 * @brief 规范化请求 target，仅保留 path 并去除末尾多余 '/'.
	 */
	std::string normalize_target(std::string_view raw_target);

	/**
	 * @brief 按 method + target 匹配静态路由。
	 */
	static_route match_static_route(http::verb method, std::string_view target);

	/**
	 * @brief 匹配动态路由模板，成功时写入路径参数。
	 */
	bool match_dynamic_route(const dynamic_route &route,
													 http::verb method,
													 std::string_view target,
													 route_params &params);
}

