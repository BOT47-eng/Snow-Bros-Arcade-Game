#include "PhysicsEngine.hpp"
#include "GameUnit.hpp"
#include <cmath>

const float PhysicsEngine::GRAVITY = 980.f;
const float PhysicsEngine::TERMINAL_VELOCITY = 800.f;

PhysicsEngine::PhysicsEngine() : blockCount(0)
{
    for (int i = 0; i < MAX_PLATFORMS; i++)
        blocks[i] = nullptr;
}

void PhysicsEngine::addPlatform(Block* block)
{
    if (blockCount < MAX_PLATFORMS)
        blocks[blockCount++] = block;
}

void PhysicsEngine::clearPlatforms()
{
    for (int i = 0; i < MAX_PLATFORMS; i++)
        blocks[i] = nullptr;
    blockCount = 0;
}

void PhysicsEngine::update(Player& player, float dt)
{
    if (!player.isAlive()) 
        return;

    player.setOnGround(false);

    applyGravity(player, dt);
    player.applyVelocity(dt);
    checkPlatforms(player, dt);
    checkFloor(player);
    wrapScreen(player);
}

void PhysicsEngine::update(Player& p1, Player& p2, float dt)
{
    update(p1, dt);
    update(p2, dt);
}

void PhysicsEngine::applyGravity(Player& player, float dt) const
{
    if (player.isOnGround()) 
        return;

    float Vy = player.getVelocityY() + GRAVITY * dt;
    if (Vy > TERMINAL_VELOCITY)
        Vy = TERMINAL_VELOCITY;
    player.setVelocityY(Vy);
}

void PhysicsEngine::checkPlatforms(Player& player, float dt) const
{
    for (int i = 0; i < blockCount; i++)
    {
        Block* block = blocks[i];

        if (!block)
            continue;

        FloatRect playerHitbox = player.getHitbox();
        FloatRect blockHitbox = block->getHitbox();

        if (!playerHitbox.intersects(blockHitbox))
            continue;

        //Using previous frame checking if player is above platform
        //Only then will he land on top of platform
        float Vy = player.getVelocityY();
        float prevBottom = playerHitbox.top + playerHitbox.height - Vy * dt;
        bool wasAbove = false;   

        if (prevBottom <= blockHitbox.top + 4.5f)
        {
            wasAbove = true;
        }

        if (Vy >= 0 && wasAbove)
            player.landPush(blockHitbox.top);
        
    }
}

void PhysicsEngine::checkFloor(Player& player) const
{
    float floorY = GameUnit::HEIGHT - 8;
    FloatRect playerHitbox = player.getHitbox();
    if (playerHitbox.top + playerHitbox.height >= floorY)
        player.landPush(floorY);
}

void PhysicsEngine::wrapScreen(Player& player) const
{
    FloatRect playerHitbox = player.getHitbox();
    Vector2f  pos = player.getPosition();

    if (playerHitbox.left + playerHitbox.width < 0)
        player.setPosition(Vector2f(GameUnit::WIDTH, pos.y));
    else if (playerHitbox.left > GameUnit::WIDTH)
        player.setPosition(Vector2f(0, pos.y));
}