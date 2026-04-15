#pragma once

#include "global.h"
#include <string>
#include <string_view>

namespace router
{
	enum class static_route
	{
		none,
		count,
		time,
		email
	};

	inline constexpr std::string_view CountRoute = "/count";
	inline constexpr std::string_view TimeRoute = "/time";
	inline constexpr std::string_view EmailRoute = "/email";

	/**
	 * @brief 规范化请求 target，仅保留 path 并去除末尾多余 '/'.
	 */
	std::string normalize_target(std::string_view raw_target);

	/**
	 * @brief 按 method + target 匹配静态路由。
	 */
	static_route match_static_route(http::verb method, std::string_view target);
}

