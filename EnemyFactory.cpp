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

void Enemy::applySnow(float amount)
{
    if (!isFullyCoated)
    {
        snowAccumulated += amount;
        if (snowAccumulated >= health)
        {

            snowAccumulated = health;
            isFullyCoated = true;
            Vx = 0;
            Vy = 0;
            shakeTimer.restart();
        }
    }
}

void Enemy::updateCoatedState()
{
    if (isFullyCoated)
    {
        if (shakeTimer.getElapsedTime().asSeconds() >= 5)
        {
            shakeOffSnow();
        }
    }
    else if (snowAccumulated > 0)
    {
        float slowFactor = 1.0 - (snowAccumulated / health);
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