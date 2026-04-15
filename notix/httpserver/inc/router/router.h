#pragma once

#include "router_rules.h"
#include <string>
#include <string_view>
#include <vector>

namespace router
{
  class Router
  {
  public:
    enum class match_kind
    {
      none,
      static_match,
      dynamic_match
    };

    struct match_result
    {
      match_kind kind{match_kind::none};
      static_route static_target{static_route::none};
      route_params params{};
    };

    Router();

    void add_dynamic_route(http::verb method, std::string pattern);

    match_result match(http::verb method, std::string_view target) const;

    static const Router &default_router();

  private:
    std::vector<dynamic_route> dynamic_routes_;
  };
}
