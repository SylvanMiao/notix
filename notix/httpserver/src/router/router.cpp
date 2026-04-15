#include "router.h"

namespace router
{
  Router::Router()
  {
    add_dynamic_route(http::verb::get, std::string(TimeByZoneRoute));
    add_dynamic_route(http::verb::post, std::string(EmailBySourceRoute));
  }

  void Router::add_dynamic_route(http::verb method, std::string pattern)
  {
    dynamic_routes_.push_back(dynamic_route{method, std::move(pattern)});
  }

  Router::match_result Router::match(http::verb method, std::string_view target) const
  {
    match_result result;
    const auto normalized_target = normalize_target(target);

    const auto static_target = match_static_route(method, normalized_target);
    if (static_target != static_route::none)
    {
      result.kind = match_kind::static_match;
      result.static_target = static_target;
      return result;
    }

    for (const auto &route : dynamic_routes_)
    {
      route_params params;
      if (match_dynamic_route(route, method, normalized_target, params))
      {
        result.kind = match_kind::dynamic_match;
        result.params = std::move(params);
        return result;
      }
    }

    return result;
  }

  const Router &Router::default_router()
  {
    static const Router router_instance;
    return router_instance;
  }
}
