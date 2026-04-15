#include "staticroute.h"

namespace router
{
  std::string normalize_target(std::string_view raw_target)
  {
    std::string path(raw_target);
    auto query_pos = path.find('?');
    if (query_pos != std::string::npos)
    {
      path = path.substr(0, query_pos);
    }

    auto fragment_pos = path.find('#');
    if (fragment_pos != std::string::npos)
    {
      path = path.substr(0, fragment_pos);
    }

    if (path.empty())
    {
      return "/";
    }

    while (path.size() > 1 && path.back() == '/')
    {
      path.pop_back();
    }

    return path;
  }

  static_route match_static_route(http::verb method, std::string_view target)
  {
    const auto normalized_target = normalize_target(target);

    if (method == http::verb::get)
    {
      if (normalized_target == CountRoute)
      {
        return static_route::count;
      }
      if (normalized_target == TimeRoute)
      {
        return static_route::time;
      }
      return static_route::none;
    }

    if (method == http::verb::post)
    {
      return normalized_target == EmailRoute ? static_route::email : static_route::none;
    }

    return static_route::none;
  }
}
