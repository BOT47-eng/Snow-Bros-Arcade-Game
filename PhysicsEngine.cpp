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

Block* PhysicsEngine::createBlockArray()
{
    Block* blocksArray = new Block[blockCount];

    for (int i = 0; i < blockCount; i++)
    {
        blocksArray[i] = *blocks[i];
    }

    return blocksArray;
}

void PhysicsEngine::update(Player& player, Enemy** enemies, int enemyCount, float dt)
{
    Block* arr = createBlockArray();

    update(player, dt);
    for (int i = 0; i < enemyCount; i++)
    {
        if (!enemies[i])
            continue;
        enemies[i]->update(dt, arr, blockCount);
    }
    checkSnowballCollisions(player, enemies, enemyCount);
    checkEnemyPlayerCollisions(player, enemies, enemyCount);
    delete[] arr;
}

void PhysicsEngine::update(Player& p1, Player& p2, Enemy** enemies, int enemyCount, float dt)
{
    Block* arr = createBlockArray();
    update(p1, dt);
    update(p2, dt);
    for (int i = 0; i < enemyCount; i++)
    {
        if (!enemies[i])
            continue;
        enemies[i]->update(dt, arr, blockCount);
    }
    checkSnowballCollisions(p1, enemies, enemyCount);
    checkSnowballCollisions(p2, enemies, enemyCount);

    checkEnemyPlayerCollisions(p1, enemies, enemyCount);
    checkEnemyPlayerCollisions(p2, enemies, enemyCount);
    delete[] arr;
}

void PhysicsEngine::checkSnowballCollisions(Player& player, Enemy** enemies, int enemyCount) const
{
    for (int i = 0; i < Player::MAX_BALLS; i++)
    {
        Snowball& ball = player.getBall(i);
        if (!ball.isActive())
            continue;

        for (int j = 0; j < enemyCount; j++)
        {
            if (!enemies[j])
                continue;

            if (ball.getHitbox().intersects(enemies[j]->getEnemyHitBox()))
            {
                if (enemies[j]->getIsFullyCoated())
                {
                    enemies[j]->sethealth(0);
                    ball.setActive(false);

                    //player score attribution, will use virtual function in enemy class
                    player.addScore(100);
                    delete enemies[j];
                    enemies[j] = nullptr;
                }
                else
                {
                    enemies[j]->applySnow(ball.getSnowAmount());
                    ball.setActive(false);
                }
            }
        }
    }
}

void PhysicsEngine::checkEnemyPlayerCollisions(Player& player, Enemy** enemies, int enemyCount) const
{
    if (!player.isAlive() || player.isInvincible())
        return;

    for (int i = 0; i < enemyCount; i++)
    {
        if (!enemies[i])
            continue;

        if (enemies[i]->getHealth() <= 0 || enemies[i]->getIsFullyCoated())
            continue;

        cout << "Enemy" << endl;

        if (player.getHitbox().intersects(enemies[i]->getEnemyHitBox()))
        {
            cout << "HIT" << endl;
            player.takeDamage();
            break;
        }
    }
}