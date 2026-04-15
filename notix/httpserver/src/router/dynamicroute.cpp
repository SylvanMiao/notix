#include "dynamicroute.h"
#include "staticroute.h"
#include <vector>

namespace router
{
  namespace
  {
    std::vector<std::string> split_segments(const std::string &path)
    {
      std::vector<std::string> segments;
      std::size_t start = 0;

      while (start < path.size())
      {
        while (start < path.size() && path[start] == '/')
        {
          ++start;
        }

        if (start >= path.size())
        {
          break;
        }

        auto end = path.find('/', start);
        if (end == std::string::npos)
        {
          segments.emplace_back(path.substr(start));
          break;
        }

        segments.emplace_back(path.substr(start, end - start));
        start = end + 1;
      }

      return segments;
    }

    bool is_placeholder(const std::string &segment)
    {
      return segment.size() > 2 && segment.front() == '{' && segment.back() == '}';
    }

    std::string placeholder_name(const std::string &segment)
    {
      return segment.substr(1, segment.size() - 2);
    }
  }

  bool match_dynamic_route(const dynamic_route &route,
                           http::verb method,
                           std::string_view target,
                           route_params &params)
  {
    params.clear();

    if (route.method != method)
    {
      return false;
    }

    const auto normalized_target = normalize_target(target);
    const auto normalized_pattern = normalize_target(route.pattern);

    const auto target_segments = split_segments(normalized_target);
    const auto pattern_segments = split_segments(normalized_pattern);

    if (target_segments.size() != pattern_segments.size())
    {
      return false;
    }

    for (std::size_t i = 0; i < pattern_segments.size(); ++i)
    {
      const auto &pattern_part = pattern_segments[i];
      const auto &target_part = target_segments[i];

      if (is_placeholder(pattern_part))
      {
        const auto key = placeholder_name(pattern_part);
        if (key.empty())
        {
          return false;
        }
        params[key] = target_part;
        continue;
      }

      if (pattern_part != target_part)
      {
        return false;
      }
    }

    return true;
  }
}
