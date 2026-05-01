#include "EnemyFactory.hpp"

void Enemy::sethealth(int h){health = h ; }
void Enemy::setPos(float x  , float y)
{
this->x  = x ;
this->y =  y ;
}
void Enemy::setPos(sf::Vector2f v)
{
   x = v.x; 
   y = v.y ;
}
void Enemy::setVx(float d) 
{
    Vx = d ; 
}
void Enemy::setVy(float d) 
{
    Vy = d ;
} 
void Enemy::setCopyVx(float d)
{
    CopyVx = d ; 
}

void Enemy::setCopyVy(float d)
{
    CopyVy = d ; 
}
void Enemy::setEnemyTexture(const sf::Texture& T) 
{
    EnemySpriteTexture = T ;
}

void Enemy::setEnemyHitBoxSprite() // Just Call it To change the current Set Texture
{
    EnemySpriteTexture.setSmooth(true) ;
    EnemySpriteTexture.setRepeated(true) ; 
    EnemySprite.setTexture(EnemySpriteTexture, true); // true = reset texture rect to full texture
    
    sf::Vector2u texSize = EnemySpriteTexture.getSize();
    EnemySprite.setTextureRect(sf::IntRect(0, 0, texSize.x, texSize.y));
    
    sf::FloatRect bounds = EnemySprite.getLocalBounds();
    EnemySprite.setHitbox(bounds);
    EnemySprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
}

void Enemy::applySnow(float amount, int playerID)
{
    if (!isFullyCoated)
    {
        snowAccumulated += amount;
        if (snowAccumulated >= health)
        {
            snowAccumulated = health;
            isFullyCoated = true;
            snowballCreatorPlayer = playerID;
            if (!isBoss)
            {
                convertToSnowball();
            }
            else
            {
                Vx = 0;
                Vy = 0;
                shakeTimer.restart();
            }
        }
    }
}

void Enemy::updateCoatedState()
{
    if (isSnowball)
    {
        updateSnowballState(0);
        return;
    }

    if (isFullyCoated)
    {
        if (shakeTimer.getElapsedTime().asSeconds() >= 5)
        {
            shakeOffSnow();
        }
    }
    else if (snowAccumulated > 0)
    {
        float slowFactor = 1.0f - (snowAccumulated / health);
        float currentSpeed = originalSpeed * slowFactor;

        if (Vx > 0)
        {
            Vx = currentSpeed;
        }
        else if (Vx < 0)
        {
            Vx = -currentSpeed;
        }
    }
}

void Enemy::shakeOffSnow()
{
    snowAccumulated = 0;
    isFullyCoated = false;
    if (originalSpeed > 0)
        Vx = originalSpeed;
    else
        Vx = -originalSpeed;
}

void Enemy::convertToSnowball()
{
    isSnowball = true;
    snowballStaticTimer = 0;
    snowballKillCount = 0;
    snowballVelocityX = 0;
    snowballVelocityY = 0;
    snowballOnGround = false;
    Vx = 0;
    Vy = 0;

    animSnowballRoll.loadSprite(frames, 4, 0.1f, true);
    animSnowballBreakout.loadSprite(breakoutFrames, 4, 0.1f, false);
    currentSnowballAnim = &animSnowballRoll;

    EnemySprite.setTexture(snowballTexture, true);

    float targetSize = 100.0f;
    float scaleX = targetSize / 230.0f;
    float scaleY = targetSize / 278.0f;
    EnemySprite.setScale(scaleX, scaleY);

    FloatRect hitbox;
    hitbox.width = 230;
    hitbox.height = 278;
    EnemySprite.setOrigin(Vector2f(hitbox.width / 2.0, hitbox.height / 2.0));
    EnemySprite.setHitbox(hitbox);
    EnemySprite.setTextureRect(animSnowballRoll.getCurrentFrame());
}

void Enemy::updateSnowballState(float dt)
{
    if (!isSnowball)
        return;

    if (isSnowballBreakingOut)
    {
        currentSnowballAnim->update(dt);
        EnemySprite.setTextureRect(currentSnowballAnim->getCurrentFrame());

        if (currentSnowballAnim->isFinished())
        {
            breakOutOfSnowball();
        }
        return;
    }

    snowballStaticTimer += dt;
    if (snowballStaticTimer >= 5.0f)
    {
        isSnowballBreakingOut = true;
        currentSnowballAnim = &animSnowballBreakout;
        currentSnowballAnim->reset();
        return;
    }

    if (snowballVelocityX != 0)
    {
        x += snowballVelocityX * dt;
    }

    snowballVelocityY += 980.0f * dt;
    if (snowballVelocityY > 800.0f)
        snowballVelocityY = 800.0f;

    y += snowballVelocityY * dt;
    EnemySprite.setPosition(x, y);

    animSnowballRoll.update(dt);
    EnemySprite.setTextureRect(animSnowballRoll.getCurrentFrame());
}


void Enemy::breakOutOfSnowball()
{
    isSnowball = false;
    isSnowballBreakingOut = false;
    snowAccumulated = 0;
    isFullyCoated = false;
    snowballStaticTimer = 0;
    snowballVelocityX = 0;
    snowballVelocityY = 0;
  
    setEnemyHitBoxSprite();

    if (snowballPushDirection != 0)
        sethealth(-1);
    else
    {
        sethealth(healthOriginal);
        if ((rand() % 2) % 2)
            Vx = originalSpeed;
        else
            Vx = -originalSpeed;
    }

    snowballPushDirection = 0;

    animSnowballRoll.reset();
    animSnowballBreakout.reset();
}