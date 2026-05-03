#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.hpp"
#include "Block.hpp"
#include "Projectile.hpp"
#include "PowerupMenu.hpp"

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

void handleStarCollection(Player& player, RenderWindow* window, Font* font)
{
    PowerupMenu starMenu(*font);
    starMenu.setActive(true);
    bool choiceMade = false;
    int selection = -1;
    while (!choiceMade && window->isOpen())
    {
        Event event;
        while (window->pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window->close();
                return;
            }
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
                {
                    starMenu.moveSelection(-1);
                }
                else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
                {
                    starMenu.moveSelection(1);
                }
                else if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)
                {
                    selection = starMenu.getSelectedOption();
                    choiceMade = true;
                }
            }
        }
        window->clear(Color::Cyan);
        starMenu.draw(*window);
        window->display();
    }
    starMenu.setActive(false);
    if (selection == 0)
    {
        player.applySpeedBoost();
    }
    else if (selection == 1)
    {
        player.applySnowballPower();
    }
    else if (selection == 2)
    {
        player.applyBalloonMode(15.0f);
    }
}

public :

~Collectible()
{
    // Don't Delete the player it is not created in heap! bhaii
}
Collectible()
{
    if(!SpriteSheet.loadFromFile("Resources/SnowBrosAssets/Images/Items.png"))
    {
        std::cout << "Error in loading the spritesheet in Collectibles Class\n" ;
        exit(0); 
    }
    if(!GemSpriteSheet.loadFromFile("Resources/SnowBrosAssets/Images/gemSprite.png"))
    {
        std::cout << "Error in loading the spritesheet in Collectibles Class\n" ;
        exit(0); 
    }

    isSushi = false ; 
    isMoney = false ; 
    isGem = false ;

    x = 300;
    y = 300;

    Vx = 0 ;
    Vy = 200 ;
}
void CreateMoney(float x , float y) 
{
    sprite.setTexture(SpriteSheet) ;
    sprite.setTextureRect({54 , 990 , 193 , 258});
    sprite.setScale(0.3 , 0.3) ; 
    sprite.setScale(0.25 , 0.25) ; 
    sprite.setHitbox(sprite.getLocalBounds());
    this->x  = x ;
    this->y = y ;

    isMoney  = true ;
    setActive(true) ;

}
void CreateSushi(float x , float y)
{
    sprite.setTexture(SpriteSheet);
    sprite.setTextureRect({169  , 84 , 129 , 83});
    sprite.setScale(0.25 , 0.25) ; 
    sprite.setPosition(x , y) ;
    sprite.setHitbox(sprite.getLocalBounds());
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
    sprite.setHitbox(sprite.getLocalBounds());
    this->x  = x ;
    this->y = y ;

    isGem  = true ;
    setActive(true) ;

}

//////////////////////////////////////////////////////
//////////////////// All the Functions Related to it 
void DirectionSwitcherToMakeitFeelReal()
{
    FloatRect hitbox = sprite.getGlobalHitbox();
    if(y + hitbox.height > 560 || y < 0)
    {
        Vy = -Vy ; 
    }
}

void UpdateY(float dt)
{
    y += Vy * dt ;
}

void update(float dt) override
{
    if (!active)
    {
        return;
    }

    if (isMoney)
    {
        DirectionSwitcherToMakeitFeelReal();
        UpdateY(dt);
        sprite.setPosition(x, y);
    }
}

bool checkPlayerCollision(Player& player, RenderWindow* window, Font* font)
{
    if (!active) 
        return false;
    if (sprite.getGlobalBounds().intersects(player.getHitbox()))
    {
        if (isSushi)
        {
            handleStarCollection(player, window, font);
            return true;
        }
        else if (isMoney)
        {
            player.addScore(1000);
            return true;
        }
        else if (isGem)
        {
            player.addGems(10);
            return true;
        }
    }
    return false;
}

//////////////////////////////////////////////////////////
 void draw(sf::RenderWindow& window, bool debug) const override
{
        if (!active) 
            return;

        window.draw(sprite);

        if (debug)
            sprite.drawHitbox(window, sf::Color::Yellow);
}

 void deactivate()
 {
     active = false;
     isSushi = false;
     isMoney = false;
     isGem = false;
 }

 bool getIsSushi() const { return isSushi; }
 bool getIsMoney() const { return isMoney; }
 bool getIsGem() const { return isGem; }
 bool isActive() const { return active; }

}; 