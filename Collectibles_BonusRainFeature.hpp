#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.hpp"
#include "Player.cpp"
#include "Block.hpp"
#include "Projectile.hpp"


//////////////////////////////////////////////////
////// This Class will contains all the collectibles + Rain Feature as well it will made as a function 


class Collectible : public Projectile
{
private :
sf::Texture SpriteSheet ;
sf::Texture GemSpriteSheet ;
float x  ;
float y  ;

bool isSushi ; 
bool isMoney ;
bool isGem ; 

Player *P ; 
sf::Clock time ;
float totalTimetoSwitch = 2 ;

public :

Collectible() {} // Better to use the other contructor 
~Collectible()
{
    // Don't Delete the player it is not created in heap! bhaii
}
Collectible(Player *P)
{
    if(!SpriteSheet.loadFromFile("Resources/SnowBrosAssets/Images/Items.png"))
    {
        cout << "Error in loading the spritesheet in Collectibles Class\n" ;
        exit(0); 
    }
    if(!GemSpriteSheet.loadFromFile("Resources/SnowBrosAssets/Images/gemSprite.png"))
    {
        cout << "Error in loading the spritesheet in Collectibles Class\n" ;
        exit(0); 
    }

    isSushi = false ; 
    isMoney = false ; 
    isGem = false ;
    this->P = P ;

    Vx = 0 ;
    Vy = 200 ;
}
void CreateMoney(float x , float y) 
{
    sprite.setTexture(SpriteSheet) ;
    sprite.setTextureRect({54 , 990 , 193 , 258});
    sprite.setScale(0.3 , 0.3) ; 
    sprite.setScale(0.25 , 0.25) ;  
    this->x  = x ;
    this->y = y ;

    isMoney  = true ;
    setActive(true) ;

}
void CreateSushi(float x , float y)
{
    sprite.setTexture(SpriteSheet) ;
    sprite.setTextureRect({169  , 84 , 129 , 83});
    sprite.setScale(0.25 , 0.25) ; 
    sprite.setPosition(x , y) ;
    this->x  = x ;
    this->y = y ;

    isSushi  = true ;
    setActive(true) ;
}
void CreateGems(float x,  float y)
{
    sprite.setTexture(GemSpriteSheet) ;
    sprite.setScale(0.13 , 0.13) ; 
    sprite.setPosition(x , y) ;
    this->x  = x ;
    this->y = y ;

    isGem  = true ;
    setActive(true) ;

}


//////////////////////////////////////////////////////
//////////////////// All the Functions Related to it 
void DirectionSwitcherToMakeitFeelReal()
{
    if(time.getElapsedTime().asSeconds() >= totalTimetoSwitch)
    {
        Vy = -Vy ; 
        time.restart() ;
    }
}

void UpdateY(float dt)
{
    y += Vy  * dt ;
}
void update(float dt) override
{
    if(!active)
    {
        return ; 
    }
    if(sprite.intersects(P->getHitbox()))
    {
        if(isSushi)
        {
            P->addScore(1000) ;
        }
        else if(isMoney)
        {
            P->addScore(1000) ;
        }
        else if(isGem)
        {
            P->addGems(20) ;
        }
    }
    DirectionSwitcherToMakeitFeelReal() ;
    UpdateY(dt) ;
    sprite.setPosition(x , y) ;
}

//////////////////////////////////////////////////////////
 void draw(sf::RenderWindow& window, bool debug) const override
{
        if (!active) return;
        window.draw(sprite);

        if (debug)
            sprite.drawHitbox(window, sf::Color::Yellow);
}

}; 