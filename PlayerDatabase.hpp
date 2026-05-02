#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include "PlayerInfo.hpp"
#include "LeaderBoard.hpp"

using namespace std;

struct PlayerSaveData 
{
    string username;
    int current_level;
    int current_score;
    int lives_remaining;
    int gem_count;
    int high_score;
    string last_updated;
    bool shop_items[5];
};

class PlayerDatabaseManager {
private:
    string dataDirectory;
    string formatDate(string date);
    string getPlayerFilePath(const string& username);
    bool fileExists(const string& filepath);
    string getCurrentDateTime();

public:
    PlayerDatabaseManager();

    bool savePlayerProgress(const PlayerSaveData& data, Leaderboard* ld = nullptr);
    bool loadPlayerProgress(const string& username, PlayerSaveData& data);
    bool playerSaveExists(const string& username);
};