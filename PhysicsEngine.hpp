#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Block.hpp"
#include "EnemyFactory.hpp"

class PhysicsEngine
{
public:
    static const int MAX_PLATFORMS = 80;
private:
    void applyGravity(Player& player, float dt) const;
    void checkPlatforms(Player& player, float dt) const;
    void checkFloor(Player& player) const;
    void wrapScreen(Player& player) const;
    void checkSnowballCollisions(Player& player, Enemy** enemies, int enemyCount) const;
    void checkEnemyPlayerCollisions(Player& player, Enemy** enemies, int enemyCount) const;

    Block* blocks[MAX_PLATFORMS];
    int blockCount;

    static const float GRAVITY;
    static const float TERMINAL_VELOCITY;

public:
    PhysicsEngine();

    Block* createBlockArray();
    void addPlatform(Block* block);
    void clearPlatforms();
    
    
    //for 1 player
    void update(Player& player, float dt);
    void update(Player& player, Enemy** enemies, int enemyCount, float dt);
    //for both players
    void update(Player& p1, Player& p2, float dt); 
    void update(Player& p1, Player& p2, Enemy** enemies, int enemyCount, float dt);
};

