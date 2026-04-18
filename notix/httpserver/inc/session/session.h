#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <chrono>

struct Session {
    std::string session_id;

    std::string user_id;   
    std::vector<std::string> history; 

    std::unordered_map<std::string, std::string> kv; 

    std::chrono::steady_clock::time_point last_active;
};