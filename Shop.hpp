#include <iostream>
#include <cstring>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <cmath>
#include "Player.hpp"
#include "AnimationComponent.hpp"
#include "Projectile.hpp"
#include "InputManager.hpp"
//#include "Player.cpp"
//#include "AnimationComponent.cpp"
//#include "Snowball.cpp"
//#include "InputManager.cpp"

static bool isMouseClicked()
{
    static bool wasPressed = false; 
    bool currentlyPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

    bool justPressed = (currentlyPressed && !wasPressed);

    wasPressed = currentlyPressed;
    return justPressed;
}

#pragma once
#ifndef SHOPCLASS
#define SHOPCLASS

class Shop
{
private : 

    static const int TOTAL_ITEMS = 5 ;
    bool isExtraLifeChosen ;
    bool isSpeedBoostChosen ;
    bool isSnowBallPowerChosen ;
    bool isDistanceIncreaseChosen ;
    bool isBallonModeChosen ; 
    std::string PurchaseState ; //Purchase Successful or Failed(not enough gems)


    /////////////////////////////
    //////// To draw to screen 
    sf::Texture itemsTextures[3] ;
    sf::Sprite itemsSprite[TOTAL_ITEMS] ;
    sf::Font font  ;
    sf::RectangleShape cards[TOTAL_ITEMS] ;
    sf::Text cardstext[TOTAL_ITEMS] ;
    sf::Text Heading ;
    int r , g , b  ;
    int animationtime;
    float speedofColorChanging ; 
    sf::Clock currentime ;
    //background
    sf::Texture backgroundTex ;
    sf::Sprite background ; 

public : 

    Shop();

private : 
    void getExtraLife(Player &P) ; 
    void getSpeedBoost(Player &P) ;
    void getSnowBall(Player &P) ;
    void getDistanceIncrese(Player &P) ;
    void getBallonMode(Player &P) ; 

public: 

    void update(sf::RenderWindow &window , Player& p) ;
    void draw(sf::RenderWindow &window, Player &p) ; 
    std::string getPurchaseState() { return PurchaseState; }
    void resetPurchaseState() { PurchaseState = ""; }

}; 

#endif