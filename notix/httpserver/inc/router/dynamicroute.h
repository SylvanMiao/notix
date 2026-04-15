#pragma once

#include "global.h"
#include <string>
#include <string_view>
#include <unordered_map>

namespace router
{
	using route_params = std::unordered_map<std::string, std::string>;

	struct dynamic_route
	{
		http::verb method;
		std::string pattern;
	};

	inline constexpr std::string_view TimeByZoneRoute = "/time/{zone}";
	inline constexpr std::string_view EmailBySourceRoute = "/email/{source}";

	/**
	 * @brief 匹配动态路由模板，成功时写入路径参数。
	 */
	bool match_dynamic_route(const dynamic_route &route,
													 http::verb method,
													 std::string_view target,
													 route_params &params);
}

