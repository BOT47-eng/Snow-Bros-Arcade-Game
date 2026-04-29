#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Block.hpp"

class PhysicsEngine
{
public:
    static const int MAX_PLATFORMS = 80;
private:
    void applyGravity(Player& player, float dt) const;
    void checkPlatforms(Player& player, float dt) const;
    void checkFloor(Player& player) const;
    void wrapScreen(Player& player) const;

    Block* blocks[MAX_PLATFORMS];
    int blockCount;

    static const float GRAVITY;
    static const float TERMINAL_VELOCITY;

public:
    PhysicsEngine();

    void addPlatform(Block* block);
    void clearPlatforms();

    //for 1 player
    void update(Player& player, float dt);
    //for both players
    void update(Player& p1, Player& p2, float dt); 
};

