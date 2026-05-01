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

void PhysicsEngine::handleSnowballPhysics(Enemy* snowball, Block* blocks, int blockCount, float dt) const
{
    if (!snowball || !snowball->getIsSnowball())
        return;

    float newVx = snowball->getSnowballVelocityX();
    float newVy = snowball->getSnowballVelocityY();
    newVy += GRAVITY * dt;
    if (newVy > TERMINAL_VELOCITY)
        newVy = TERMINAL_VELOCITY;

    float newX = snowball->getPosX() + newVx * dt;
    float newY = snowball->getPosY() + newVy * dt;

    snowball->setPos(newX, newY);
    snowball->setSnowballVelocityX(newVx);
    snowball->setSnowballVelocityY(newVy);
    snowball->getEnemySprite().setPosition(newX, newY);

    FloatRect snowballBox = snowball->getEnemyHitBox();
    bool onPlatform = false;

    for (int i = 0; i < blockCount; i++)
    {
        if (!blocks[i].getHitbox().intersects(snowballBox))
            continue;

        FloatRect blockBox = blocks[i].getHitbox();
        float prevBottom = snowballBox.top + snowballBox.height - newVy * dt;

        if (prevBottom <= blockBox.top + 4.5f && newVy >= 0)
        {
            snowball->setPos(snowball->getPosX(), blockBox.top - snowballBox.height / 2.0f);
            snowball->setSnowballVelocityY(0);
            onPlatform = true;
            break;
        }
    }

    float floorY = GameUnit::HEIGHT - 40;
    if (snowballBox.top + snowballBox.height >= floorY)
    {
        snowball->setPos(snowball->getPosX(), floorY - snowballBox.height / 2.0f);
        snowball->setSnowballVelocityY(0);
        onPlatform = true;
    }

    snowball->setSnowballOnGround(onPlatform);
}

void PhysicsEngine::handleSnowballBoundary(Enemy* snowball) const
{
    if (!snowball)
        return;

    FloatRect box = snowball->getEnemyHitBox();
    float vx = snowball->getSnowballVelocityX();

    if (box.left < 0 && vx < 0)
    {
        snowball->setSnowballVelocityX(-vx);
        snowball->setPos(20, snowball->getPosY());
    }
    else if (box.left + box.width > GameUnit::WIDTH && vx > 0)
    {
        snowball->setSnowballVelocityX(-vx);
        snowball->setPos(GameUnit::WIDTH - snowball->getEnemyHitBox().width / 2.0, snowball->getPosY());
    }
}

void PhysicsEngine::checkSnowballEnemyCollisions(Player& player, Enemy* snowball, Enemy** enemies, int enemyCount) const
{
    if (!snowball || !snowball->getIsSnowball())
        return;

    FloatRect snowballBox = snowball->getEnemyHitBox();

    for (int i = 0; i < enemyCount; i++)
    {
        if (!enemies[i] || enemies[i] == snowball)
            continue;

        if (enemies[i]->getIsSnowball() || enemies[i]->getHealth() <= 0)
            continue;

        if (!snowballBox.intersects(enemies[i]->getEnemyHitBox()))
            continue;

        int killCount = snowball->getSnowballKillCount();
        int points = static_cast<int>(enemies[i]->getScore() * std::pow(1.10, killCount));
        player.addScore(points);

        snowball->incrementSnowballKillCount();
        enemies[i]->sethealth(0);

        delete enemies[i];
        enemies[i] = nullptr;
    }
}

void PhysicsEngine::update(Player& player, Enemy** enemies, int enemyCount, float dt)
{
    Block* arr = createBlockArray();

    update(player, dt);
    for (int i = 0; i < enemyCount; i++)
    {
        if (!enemies[i])
            continue;

        if (enemies[i]->getIsSnowball())
        {
            enemies[i]->updateSnowballState(dt);
            handleSnowballPhysics(enemies[i], arr, blockCount, dt);
            handleSnowballBoundary(enemies[i]);
            checkSnowballEnemyCollisions(player, enemies[i], enemies, enemyCount);
        }
        else
        {
            enemies[i]->update(dt, arr, blockCount);
            enemies[i]->updateCoatedState();
        }

        if (enemies[i]->getHealth() <= -1)
        {
            player.addScore(enemies[i]->getScore());
            delete enemies[i];
            enemies[i] = nullptr;
        }

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

        if (enemies[i]->getIsSnowball())
        {
            enemies[i]->updateSnowballState(dt);
            handleSnowballPhysics(enemies[i], arr, blockCount, dt);
            handleSnowballBoundary(enemies[i]);
            checkSnowballEnemyCollisions(p1, enemies[i], enemies, enemyCount);
            checkSnowballEnemyCollisions(p2, enemies[i], enemies, enemyCount);
        }
        else
        {
            enemies[i]->update(dt, arr, blockCount);
            enemies[i]->updateCoatedState();
        }

        if (enemies[i]->getHealth() <= -1)
        {
            p1.addScore(enemies[i]->getScore());
            delete enemies[i];
            enemies[i] = nullptr;
        }

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
                if (enemies[j]->getIsSnowball())
                {
                    float pushDir = 0;
                    if (player.isFacingRight())
                        pushDir = 1;
                    else
                        pushDir = -1;
                    enemies[j]->setSnowballVelocityX(200.0f * pushDir);
                    enemies[j]->setSnowballVelocityY(0);
                    enemies[j]->setSnowballPushDirection(pushDir);
                    ball.setActive(false);
                    continue;
                }

                if (enemies[j]->getIsFullyCoated())
                {
                    ball.setActive(false);
                }
                else
                {
                    enemies[j]->applySnow(ball.getSnowAmount());
                    ball.setActive(false);
                    if (enemies[j]->getIsSnowball())
                        handleSnowballPhysics(enemies[j], *blocks, blockCount, 0.05);
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

        if (enemies[i]->getHealth() <= 0 || enemies[i]->getIsFullyCoated() || enemies[i]->getIsSnowball())
            continue;

        if (player.getHitbox().intersects(enemies[i]->getEnemyHitBox()))
        {
            player.takeDamage();
            break;
        }
    }
}