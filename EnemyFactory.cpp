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
void Enemy::setDx(float d) 
{
    dx = d ; 
}
void Enemy::setDy(float d) 
{
    dy = d ;
} 
void Enemy::setEnemyTexture(sf::Texture T) 
{
    EnemySpriteTexture = T ;
}
void Enemy::setEnemyHitBoxSprite(HitboxSprite h) 
{
    EnemySprite = h ;
}
void Enemy::setEnemySpriteAnimationsTexture_X(sf::Texture *t , const int SIZE)
{
    EnemySpriteAnimationsTextures_X = new sf::Texture[SIZE] ;
    for(int st = 0 ; st <= SIZE -1 ;  st++)
    {
        EnemySpriteAnimationsTextures_X[st] = t[st] ;
    }
}
void Enemy::setEnemySpriteAnimationsTexture_Y(sf::Texture *t , const int SIZE) 
{
    EnemySpriteAnimationsTextures_Y = new sf::Texture[SIZE] ;
    for(int st = 0 ; st <= SIZE - 1 ;  st++)
    {
        EnemySpriteAnimationsTextures_Y[st] = t[st] ;
    }
}
void Enemy::setEnemySpriteAnimation_X(sf::Sprite *S  , const int SIZE) 
{
    EnemySpriteAnimations_X = new sf::Sprite[SIZE] ; 
    for(int st = 0 ; st <= SIZE - 1 ; st++)
    {
        EnemySpriteAnimations_X[st] = S[st]; 
    }
}
void Enemy::setEnemySpriteAnimation_Y(sf::Sprite *S  , const int SIZE)
{
    EnemySpriteAnimations_Y = new sf::Sprite[SIZE] ; 
    for(int st = 0 ; st <= SIZE - 1 ; st++)
    {
        EnemySpriteAnimations_Y[st] = S[st]; 
    }
}
void Enemy::setTotalAnimationNumber_X(int n) 
{
    TotalAnimationNumber_X = n  ;
}
void Enemy::setTotalAnimationNumber_Y(int n) 
{
    TotalAnimationNumber_Y = n  ; 
}

void Enemy::UpateAnimationPerFrameofEnemy_X()
{
    EnemySprite.setTexture(EnemySpriteAnimationsTextures_X[CurrentIndexofAnimation_X]) ;
    CurrentIndexofAnimation_X = (CurrentIndexofAnimation_X + 1) % TotalAnimationNumber_X ;
}
void Enemy::UpateAnimationPerFrameofEnemy_Y()
{
    EnemySprite.setTexture(EnemySpriteAnimationsTextures_Y[CurrentIndexofAnimation_Y]) ; 
    CurrentIndexofAnimation_Y = (CurrentIndexofAnimation_Y + 1) % TotalAnimationNumber_Y ;
}