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

using namespace sf;
using namespace std;

struct BlockData {
	float x, y, width, height;
};

struct EnemyData {
	string type;
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
	RenderWindow* window;
	Font* fontHeader;
	Font* fontNormal;
	PlayerInfo* players;
	bool player1Active;
	bool player2Active;
	bool isSinglePlayer;

	void drawLevelSelect(int gameMode);
	void drawLevel(int levelIndex);
	void drawGameOver(int p1Score, int p2Score, bool p1Alive, bool p2Alive);
	void drawShop(Player& p1, Player& p2, bool singlePlayer);
	int drawPauseMenu(Player& p1, Player& p2, bool singlePlayer);
	bool runLevel(int levelIndex, Player& p1, Player& p2);
	Enemy* createEnemy(const string& type, float x, float y);

public:
	LevelManager();
	~LevelManager();

	bool loadLevelConfig(const string& filepath);
	void startGame(int gameMode, RenderWindow* w, Font* fHeader, Font* fNormal, PlayerInfo* p, bool p1Login, bool p2Login);
	int getLevelCount();
	bool isLevelUnlocked(int levelIndex);
	bool isLevelCompleted(int levelIndex);
	void setLevelCompleted(int levelIndex);
};