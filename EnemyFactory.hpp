#pragma once
#include <iostream>
#include <cstring>
#include <SFML/Graphics.hpp>
#include "Hitbox.h"
#include "hitbox.cpp"
#include "Block.h"


#ifndef ENEMYFACTORY 
#define ENEMYFACTORY 


///////////////////////
/// Base Abstract Class + All the Derived Classes 

class Enemy
{
protected:
///////////////////////
//// Basic Properties
int health ; 
float x;
float y; 
float Vx ;
float Vy ;

float CopyVx ;  // To use incase the actual value is 0
float CopyVy ; 

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
void setVx(float d) ;
void setVy(float d) ; 
void setCopyVx(float d) ;
void setCopyVy(float d) ; 
void setEnemyTexture(const sf::Texture& T) ; 
void setEnemyHitBoxSprite() ; 
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
sf::Vector2f getPos() const {return {x , y};}
float getVx() const {return Vx;}
float getVy() const {return Vy;}
HitboxSprite getEnemySprite() const {return EnemySprite ; }
FloatRect getEnemyHitBox() const {return EnemySprite.getGlobalHitbox(); }




public :
Enemy(): health(0) , x(0) ,  y(0) , Vx(0) , Vy(0) , CopyVx(0) , CopyVy(0) , TotalAnimationNumber_X(0) , TotalAnimationNumber_Y(0) , CurrentIndexofAnimation_X(0) , CurrentIndexofAnimation_Y(0) 
{
    EnemySpriteAnimationsTextures_X = nullptr ;
    EnemySpriteAnimations_X = nullptr ;
    EnemySpriteAnimationsTextures_Y = nullptr ;
    EnemySpriteAnimations_Y = nullptr ;
} 
Enemy(int h , float x , float y  , float dx  , float dy) : health(h) , x(x) , y(y) , Vx(dx)  , Vy(dy) 
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
virtual void CreateEnemy(float x , float y) = 0 ;
virtual void Update(sf::RenderWindow &mywindow , const float dt , Block *B , const int BLOCKSIZE) = 0 ;
virtual void Draw(sf::RenderWindow &mywindow) = 0 ;
}; 
#endif

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
sf::Clock timeToChangeDirection ; 
sf::Clock timeToJump ; 
sf::Clock  JumpInterval ; // To Keep track of the Jump time and bring it back to land

public:

Botom() : isLeft(false) , isRight(true) , isJumping(false) , isFallingDown(false) , gravityfactor(980) , Enemy()
{
    timeToChangeDirection.restart() ; 
    timeToJump.restart() ; 
    JumpInterval.restart() ;
} 
void UpdateDirection_X()
{
    if(timeToChangeDirection.getElapsedTime().asSeconds() > 3)
    {
        setVx(-getVx()) ; 
        timeToChangeDirection.restart() ; 
    }
}




void CreateEnemy(float x , float y) override
{
    ///////////////////////////////////////
    ////// Creating the Enemy first 
    sf::Texture EnemyTexture;
    sf::IntRect area(2 , 934 , 88 , 93) ; 
    if(!EnemyTexture.loadFromFile("Resources/SnowBrosAssets/Images/Botom_Pink.png" , area))
    {
        cout << "Error in Loading the file\n" ;
        exit(0) ;
    }
    setEnemyTexture(EnemyTexture) ;
    setEnemyHitBoxSprite() ; 
    /////////////////////////
    /// Change the SIZE TODO 
    
    
    /////////////////////////////////////////////
    ///// Now Setting the Properties of the Enemy
    setPos(x , y) ;
    setVx(1000) ;  /// TEST TO CHANGE LATER
    setVy(1000) ;  // TEST TO CHANGE LATER 
    setCopyVx(1000) ;
    setCopyVy(1000) ; 
}
////////////////////////////////////////////////////////////////////////////////////////////
/////////////////// UPDATE FUNCTION AND ALL IT'S RELATED FUNCTIONS FOR THE BOTOM ENEMY CLASS 
void UpdateX(float dt)
{
    x += Vx * dt ; 
}
void UpdateY(float dt)
{
    y += Vy * dt ;
}
void CheckCollionsWithScreen(const float width , const float height)
{
    if (x + EnemySprite.getGlobalBounds().width > width)
    {
        x = width - EnemySprite.getGlobalBounds().width; 
        setVx(-abs(getVx())); 
    }
    else if (x < 0)
    {
        x = 0; 
        setVx(abs(getVx())); 
    }

    if (y + EnemySprite.getGlobalBounds().height > height)
    {
        y = height - EnemySprite.getGlobalBounds().height; 
        setVy(0); // It has to walk so change in y is now 0 else if bounce setVy(-abs(getVy())) ; 
    }
    else if (y < 0)
    {
        y = 0;
        setVy(abs(getVy())); 
    }
    EnemySprite.setPosition(x, y);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//// Return True if It is on land else it return false in which case we have add the gravity factor
bool CheckCollosionsWithPlatforms(sf::RenderWindow &mywindow, Block *b, const int SIZE)
{
    bool OnLand = false ;

    for(int st = 0; st < SIZE; st++)
    {
        sf::FloatRect enemyBox = EnemySprite.getGlobalHitbox();
        sf::FloatRect blockBox = b[st].getHitbox();
        sf::FloatRect overlap; 

        // If they touch, calculate the overlap area
        if (enemyBox.intersects(blockBox, overlap)) 
        {
            // Calculates the horizontal area i.e THE SIDES
            if (overlap.width < overlap.height) 
            {
                if (enemyBox.left < blockBox.left) 
                {
                    x = blockBox.left - enemyBox.width; 
                    setVx(-abs(getVx()));               
                }
                else 
                {
                    x = blockBox.left + blockBox.width; 
                    setVx(abs(getVx()));             
                }
            }
            else // Calculates the vertical area  i.e THE TOP
            {
                if (enemyBox.top < blockBox.top) 
                {
                    y = blockBox.top - enemyBox.height; 
                    setVy(0);             
                    true ;
                }
            }
            
            // CRITICAL: Update the sprite's position immediately so it doesn't get stuck
            EnemySprite.setPosition(x, y);
        }
    }
    return OnLand ;
}

void EnemyWantsToJumporNot()
{
    if(timeToJump.getElapsedTime().asSeconds() > 5)
    {
        if(rand() % 2)
        {
            isJumping = true ;
            JumpInterval.restart() ;
        }
        timeToJump.restart() ; 
    }
}

void Update(sf::RenderWindow &mywindow , const float dt , Block *B , const int BLOCKSIZE) override
{

    //////////////////////////////////////////
    /// Update the Position  of the sprite 

    // JUST A TEST CHANGE ACCORDING TO NEED 
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
      {  setVy(getVy());
        UpdateY(dt) ;}
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
       { setVy(-getVy());
        UpdateY(dt) ;
       }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        UpdateX(dt) ; 
    UpdateDirection_X() ;

    EnemySprite.setPosition(x , y) ;


    CheckCollionsWithScreen(mywindow.getSize().x  , mywindow.getSize().y) ; 
    bool CheckCollosionAndAlsoTellIfEnemyisOnLand = CheckCollosionsWithPlatforms(mywindow , B , BLOCKSIZE);
    if(!CheckCollosionAndAlsoTellIfEnemyisOnLand)
    {
        // Add the gravity factor because if it was on land then Vy is 0 
        isFallingDown = true ;
        setVy(gravityfactor) ; 
    }
    else
    {
        // Else enemy is on land set it's Vx 
        setVx(CopyVx) ; 
    }
    
    EnemyWantsToJumporNot() ; 

    if(isJumping && float(JumpInterval.getElapsedTime().asSeconds()) < 0.3)
    {
        setVx(0) ; 
        const int JumpFactorToSpeed = 1000 ;
        setVy(-getVy() - JumpFactorToSpeed) ;
    }
    else
    {
        isJumping = false ; 
        setVy(gravityfactor) ; 
    }
    UpdateY(dt);

    /// If the enemy Jumps Ignore  the platform collosions and go up till the box it is currently colliding with is not below it.

}





void Draw(sf::RenderWindow &mywindow)  override
{
    /// ONLY DRAW DON'T CLEAR OR DISPLAY



    mywindow.draw(Enemy::getEnemySprite()) ; 

}

}; 




#endif