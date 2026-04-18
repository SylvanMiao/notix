#pragma once

#include <cstdint>
#include <string>

struct SessionRecord
{
    std::string session_id;
    std::string user_id;
    std::string data_json;
    std::int64_t last_active_epoch{0};
    std::int64_t expires_at_epoch{0};
};