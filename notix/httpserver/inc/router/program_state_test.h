#pragma once
#include "beast_http.h"

/*
program_state_test 主要进行一些路由功能的支持
*/
namespace program_state_test
{
  // 返回计数
  inline std::size_t request_count()
  {
    static std::size_t count = 0;
    return ++count;
  }

  // 返回时间
  inline std::time_t now()
  {
    return std::time(0);
  }

  // 加载html文件
  inline bool load_text_file(const std::string &path, std::string &content)
  {
    std::ifstream file(path);
    if (!file.is_open())
    {
      return false;
    }

    std::ostringstream ss;
    ss << file.rdbuf();
    content = ss.str();
    return true;
  }

  // 把html文件里面的字符串内容进行替换
  inline void replace_all(std::string &source, const std::string &from, const std::string &to)
  {
    if (from.empty())
    {
      return;
    }

    std::size_t start_pos = 0;
    while ((start_pos = source.find(from, start_pos)) != std::string::npos)
    {
      source.replace(start_pos, from.length(), to);
      start_pos += to.length();
    }
  }
}