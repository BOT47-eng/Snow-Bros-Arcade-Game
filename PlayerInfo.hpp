#pragma once

#include <iostream>

struct PlayerInfo {
    std::string username = "Guest";
    long long passwordHash;
    std::string email;
    std::string created;
};