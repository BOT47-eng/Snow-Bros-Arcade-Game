#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include "PlayerInfo.hpp"
#include "LeaderBoard.hpp"

struct PlayerSaveData 
{
    std::string username;
    int current_level;
    int current_score;
    int lives_remaining;
    int gem_count;
    int high_score;
    std::string last_updated;
    bool shop_items[5];
};

class PlayerDatabaseManager {
private:
    std::string dataDirectory;
    std::string formatDate(std::string date);
    std::string getPlayerFilePath(const std::string& username);
    bool fileExists(const std::string& filepath);
    std::string getCurrentDateTime();

public:
    PlayerDatabaseManager();

    bool savePlayerProgress(const PlayerSaveData& data, Leaderboard* ld = nullptr);
    bool loadPlayerProgress(const std::string& username, PlayerSaveData& data);
    bool playerSaveExists(const std::string& username);
};