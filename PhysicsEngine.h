#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Block.h"

class PhysicsEngine
{
public:
    static const int MAX_PLATFORMS = 64;
private:
    void applyGravity(Player& player, float dt) const;
    void checkPlatforms(Player& player, float dt) const;
    void checkFloor(Player& player) const;
    void wrapScreen(Player& player) const;

    float m_screenWidth;
    float m_screenHeight;

    Block* m_blocks[MAX_PLATFORMS];
    int m_blockCount;

    static const float GRAVITY;
    static const float MAX_FALL_SPEED;

public:
    PhysicsEngine(float screenWidth, float screenHeight);

    void addPlatform(Block* block);
    void clearPlatforms();

    //for 1 player
    void update(Player& player, float dt);
    //for both players
    void update(Player& p1, Player& p2, float dt); 
};