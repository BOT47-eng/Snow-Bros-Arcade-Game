#pragma once
#include <iostream>
#include <cstring>
#include <SFML/Graphics.hpp>
#include "Hitbox.h"


#ifndef ENEMYFACTORY 
#define ENEMYFACTORY 


///////////////////////
/// Base Abstract Class + All the Derived Classes 

class Enemy
{
private :
///////////////////////
//// Basic Properties
int health ; 
float x;
float y; 
float dx ;
float dy ;

////////////////////////////////
///// Different Sprite Animation 
sf::Texture EnemySpriteTexture ; 
HitboxSprite EnemySprite;
sf::Texture *EnemySpriteAnimationsTextures_X ; 
sf::Sprite *EnemySpriteAnimations_X ; // It will only store the different animation of enemy wrt x movement  , which we can assign to the main sprite hitbox
sf::Texture *EnemySpriteAnimationsTextures_Y ; 
sf::Sprite *EnemySpriteAnimations_Y ; // It will only store the different animation of enemy wrt y movement  , which we can assign to the main sprite hitbox
int TotalAnimationNumber_X;
int TotalAnimationNumber_Y;

int CurrentIndexofAnimation_X ; 
int CurrentIndexofAnimation_Y ; 



///////////////////////////
///// All Other Necessary Functions for an Enemy Class 

void UpateAnimationPerFrameofEnemy_X() ;
void UpateAnimationPerFrameofEnemy_Y() ;
 

public:
/////////////////////////////
//////// Setters 
void sethealth(int  h) ; 
void setPos(float x  , float y) ;
void setPos(sf::Vector2f v) ; 
void setDx(float d) ;
void setDy(float d) ; 
void setEnemyTexture(sf::Texture T) ; 
void setEnemyHitBoxSprite(HitboxSprite h) ; 
void setEnemySpriteAnimationsTexture_X(sf::Texture *t , const int SIZE) ; 
void setEnemySpriteAnimationsTexture_Y(sf::Texture *t , const int SIZE) ; 
void setEnemySpriteAnimation_X(sf::Sprite *S  , const int SIZE) ;
void setEnemySpriteAnimation_Y(sf::Sprite *S  , const int SIZE) ;
void setTotalAnimationNumber_X(int n) ;
void setTotalAnimationNumber_Y(int n) ;


////////////////////////////
////// Getters 
int getHealth() const {return health;}
float getPosX() const {return x;}
float getPosY() const {return y;}
Vector2f getPos() const {return {x , y};}
float getDx() const {return dx;}
float getDy() const {return dy;}






public :
Enemy(): health(0) , x(0) ,  y(0) , dx(0) , dy(0) , TotalAnimationNumber_X(0) , TotalAnimationNumber_Y(0) , CurrentIndexofAnimation_X(0) , CurrentIndexofAnimation_Y(0)
{
    EnemySpriteAnimationsTextures_X = nullptr ;
    EnemySpriteAnimations_X = nullptr ;
    EnemySpriteAnimationsTextures_Y = nullptr ;
    EnemySpriteAnimations_Y = nullptr ;
} 
Enemy(int h , float x , float y  , float dx  , float dy) : health(h) , x(x) , y(y) , dx(dx)  , dy(dy) 
{
    EnemySpriteAnimationsTextures_X = nullptr ;
    EnemySpriteAnimations_X = nullptr ;
    EnemySpriteAnimationsTextures_Y = nullptr ;
    EnemySpriteAnimations_Y = nullptr ;
    TotalAnimationNumber_X = 0; 
    TotalAnimationNumber_Y = 0; 

}


virtual ~Enemy()
{
    delete [] EnemySpriteAnimationsTextures_X ;
    delete [] EnemySpriteAnimations_X ;
    delete [] EnemySpriteAnimationsTextures_Y ;
    delete [] EnemySpriteAnimations_Y ;
}


//////////////////////
//// Main Functions for Every Enemy 
virtual void CreateEnemy() = 0 ;
virtual void Update() = 0 ;
virtual void Draw() = 0 ;
}; 
#endif ENEMYFACTORY 

///////////////////////////////////////////////////////////////
/////////// Dereiving All the other Necessary Enemy Classes


#ifndef BOTOM
#define BOTOM

class Botom : public Enemy
{
private : 

bool isLeft ; // For whenever change in x is negative 
bool isRight; // For whenever change in x is positive 
bool isJumping ; // For whenever change in y is negative hence true 
bool isFallingDown ; // For whenever change in y is postive hence true 
float gravityfactor ;

public:

Botom() : isLeft(false) , isRight(true) , isJumping(false) , isFallingDown(false) , gravityfactor(9.8751054205) {} //hehe






}; 




#endif