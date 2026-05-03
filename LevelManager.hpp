#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include "Block.hpp"
#include "Player.hpp"
#include "PhysicsEngine.hpp"
#include "InputManager.hpp"
#include "EnemyFactory.hpp"
#include "PlayerInfo.hpp"
#include "Shop.hpp"
#include "PlayerDatabase.hpp"
#include "LeaderBoard.hpp"

struct BlockData {
	float x, y, width, height;
};

struct EnemyData {
	std::string type;
	float x, y;
};

struct LevelData {
	int levelNumber;
	bool isBossLevel;
	EnemyData* enemies;
	int enemyCount;
	BlockData* blocks;
	int blockCount;
};

class LevelManager {
private:
	LevelData* levels;
	int levelCount;
	bool* levelUnlocked;
	bool* levelCompleted;
	sf::RenderWindow* window;
	sf::Font* fontHeader;
	sf::Font* fontNormal;
	PlayerInfo* players;
	bool player1Active;
	bool player2Active;
	bool isSinglePlayer;
	Player p1;
	Player p2;
	Shop* shop;
	PlayerDatabaseManager saveManager;
	PlayerSaveData p1SaveData;
	PlayerSaveData p2SaveData;
	Leaderboard* leaderboard;
	sf::Sprite* backgrounds;
	sf::Texture backgroundSpriteSheet;

	void drawLevelSelect(int gameMode);
	void drawGameOver(int p1Score, int p2Score, bool p1Alive, bool p2Alive);
	void drawShop(Player& player);
	int drawPauseMenu(Player& p1, Player& p2, bool singlePlayer);
	bool runLevel(int levelIndex, Player& p1, Player& p2);
	Enemy* createEnemy(const std::string& type, float x, float y);
	void savePlayerProgress(Player& p1, Player& p2, int levelIndex);
	void loadPlayerProgress(const std::string& username, Player& player, bool isPlayer1);
	void applyPersistentEffects(Player& player, const PlayerSaveData& saveData);
	void resetLevelState(Player& p1, Player& p2);

public:
	LevelManager(Leaderboard* ld);
	~LevelManager();

	bool loadLevelConfig(const std::string& filepath);
	void startGame(int gameMode, sf::RenderWindow* w, sf::Font* fHeader, sf::Font* fNormal, PlayerInfo* p, bool p1Login, bool p2Login);
	int getLevelCount();
	bool isLevelUnlocked(int levelIndex);
	bool isLevelCompleted(int levelIndex);
	void setLevelCompleted(int levelIndex);

};