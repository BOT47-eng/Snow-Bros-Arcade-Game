#include <iostream>
#include <cstring>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <cmath>
#include "Player.hpp"
#include "Player.cpp"
#include "AnimationComponent.cpp"
#include "Snowball.cpp"
#include "InputManager.cpp"


using namespace std ;
using namespace sf;


#pragma once
#ifndef SHOPCLASS
#define SHOPCLASS

bool isMouseClicked()
{
    bool isPressed =  false ;
    bool isRelesed = false ; 
    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        isPressed = true ; 
    }
    else
    {
        if(!isPressed)
        {
            isRelesed = true ; 
        }
        isPressed = false ;
    }
    static int  c = 0 ;
    return (isPressed && !isRelesed);
}
class SHOP
{
private : 

int totalItems ;
bool isExtraLifeChosen ;
bool isSpeedBoostChosen ;
bool isSnowBallPowerChosen ;
bool isDistanceIncreaseChosen ;
bool isBallonModeChosen ; 
string PurchaseState ; // Purchase Successful or Failed(not enough gems)


/////////////////////////////
//////// To draw to screen 
sf::Texture itemsTextures[5] ;
sf::Sprite itemsSprite[5] ; 
sf::Font font  ;
sf::RectangleShape cards[5] ;
sf::Text cardstext[5] ; 
sf::Text Heading ;
int r , g , b  ;
int animationtime;
float speedofColorChanging ; 
sf::Clock currentime ;
//background
sf::Texture backgroundTex ;
sf::Sprite background ; 


public : 
SHOP()
{
    totalItems = 5 ;
    isExtraLifeChosen =  false ; 
    isSpeedBoostChosen = false ;
    isSnowBallPowerChosen = false ;
    isDistanceIncreaseChosen = false ;
    isBallonModeChosen = false ;
    PurchaseState = "" ; 
    r = g = b = 0 ;
    animationtime = 0.15f; 
    speedofColorChanging = 0 ;
    currentime.restart() ; 

    ///// Loading the items 
    if(!itemsTextures[0].loadFromFile("Resources/SnowBrosAssets/Images/Items.png" , {353 , 28 , 88 , 133}) ||
       !itemsTextures[1].loadFromFile("Resources/SnowBrosAssets/Images/Player_Blue.png" , {0 , 423 , 73 ,  74}) ||
       !itemsTextures[2].loadFromFile("Resources/SnowBrosAssets/Images/Player_Blue.png" , {10 , 1057 , 63 , 76}) ||
       !itemsTextures[3].loadFromFile("Resources/SnowBrosAssets/Images/Player_Red.png" , {507 , 1233 , 43 , 43}) ||
       !itemsTextures[4].loadFromFile("Resources/SnowBrosAssets/Images/Player_Red.png" , {421 , 673 , 119 , 124}))
       {
        cout << "Error in loading the textures in Shop Class\n" ;
        exit(0) ; 
       }
    if(!font.loadFromFile("Resources/SnowBrosAssets/Fonts/normal-font.ttf"))
    {
        cout << "Error in loading the fonts in Shop Class\n"; 
        exit(0) ; 
    }
    if(!backgroundTex.loadFromFile("Resources/SnowBrosAssets/Images/ShopBackground.jpg"))
    {
         cout << "Error in loading the Background tex in Shop Class\n"; 
        exit(0) ; 
    }

    for(int st =  0 ; st <= totalItems - 1 ; st++)
    {
        itemsSprite[st].setTexture(itemsTextures[st]) ; 
        cardstext[st].setFont(font) ; 
        cardstext[st].setFillColor(sf::Color::Black) ; 
        cardstext[st].setScale(1.2 , 1.2) ;
    }

    // Setting Each Box Property 
    itemsSprite[0].setPosition(100 , 100) ; 
    itemsSprite[1].setPosition(240 ,100) ; 
    itemsSprite[2].setPosition(410 , 100) ; 
    itemsSprite[3].setPosition(180 , 300) ; 
    itemsSprite[4].setPosition(300 , 300) ; 

    itemsSprite[0].setScale({0.7 , 0.7}) ; 
    itemsSprite[1].setScale({1.1 , 1.1}) ; 
    itemsSprite[2].setScale({1.1 , 1.1}) ; 
    itemsSprite[3].setScale({1.1 , 1.1}) ; 
    itemsSprite[4].setScale({0.7 , 0.7}) ; 

    cardstext[0].setString("Extra   Life") ; 
    cardstext[1].setString("Speed   Boost") ; 
    cardstext[2].setString("SnowBall Power") ; 
    cardstext[3].setString("Distance +") ; 
    cardstext[4].setString("Ballon   Mode") ; 


    Vector2f size = {120 , 25} ;
    for(int st =  0 ; st <= totalItems - 1 ; st++)
    {
        cards[st].setSize(size); 
        cards[st].setFillColor(sf::Color(100 , 100 , 100)) ;
        cards[st].setPosition({itemsSprite[st].getPosition().x - 13 , itemsSprite[st].getPosition().y + itemsSprite[st].getGlobalBounds().getSize().y + 20}) ;
        cardstext[st].setPosition({cards[st].getPosition().x + 10 ,cards[st].getPosition().y  - cards[st].getSize().y + 5 }) ;
    }

    Heading.setFont(font) ; 
    Heading.setString("SHOP UwU") ;
    Heading.setScale(3 , 3) ; 
    Heading.setPosition(180 , -20) ;

    Vector2f texSize = {float(backgroundTex.getSize().x)  , float(backgroundTex.getSize().y)} ; 
    Vector2f windowSize = {600 , 600} ; 
    float ScaleX = (float) windowSize.x / texSize.x;
    float ScaleY = (float) windowSize.y / texSize.y; 
    background.setTexture(backgroundTex) ;
    background.setScale(ScaleX , ScaleY) ;
}

private : 
void getExtraLife(Player &P) ; 
void getSpeedBoost(Player &P) ;
void getSnowBall(Player &P) ;
void getDistanceIncrese(Player &P) ;
void getBallonMode(Player &P) ; 

public: 

void Update(sf::RenderWindow &window ,  Player &P) ; 
void Draw(sf::RenderWindow &window, Player &P) ; 
}; 


void SHOP::getExtraLife(Player &P)
{
    if(P.getGems() >= 50)
    {
        P.addGems(-50) ; // deducts 
        P.addLife() ; 
        PurchaseState = "Successful" ; 
    }
    else 
    {
        PurchaseState = "Failed Not Enough Gems" ; 
    }
    return ;
}
void SHOP::getSpeedBoost(Player &P)
{
  if(P.getGems() >= 20)
    {
        P.addGems(-20) ; // deducts 
        // Doubling the velocity  of x only 
        P.setVelocityX(P.getVelocityX() * 2) ;    
        PurchaseState = "Successful" ; 
    }
    else 
    {
        PurchaseState = "Failed Not Enough Gems" ; 
    }  
}
void SHOP::getSnowBall(Player &P) 
{
    if(P.getGems() >= 25)
    {
        P.addGems(-25) ; // deducts 
        // TODO THE CHANGE TO PLAYER SNOWBALL

        PurchaseState = "Successful" ; 
    }
    else 
    {
        PurchaseState = "Failed Not Enough Gems" ; 
    }
}
void SHOP::getDistanceIncrese(Player &P) 
{
    if(P.getGems() >= 25)
    {
        P.addGems(-25) ; // deducts 
        for(int st = 0 ;  st <= P.MAX_BALLS - 1 ; st++)
        {
            P.getBall(st).setMaxDistance(600) ; 
        }   
        PurchaseState = "Successful" ; 
    }
    else 
    {
        PurchaseState = "Failed Not Enough Gems" ; 
    }
    
}
void SHOP::getBallonMode(Player &P) 
{
    if(P.getGems() >= 35)
    {
        P.addGems(-35) ; // deducts 
        P.setBallonMode(true) ;
   
        PurchaseState = "Successful" ; 
    }
    else 
    {
        PurchaseState = "Failed Not Enough Gems" ; 
    }
} 

// INSIDE UPDATE AFTER PLAYER CHOSES THE VALUE GETVALUE AND CHANGE THE PLAYER ATTRIBUTES  AND SET CHOSEN TO FALSE
void SHOP::Update(sf::RenderWindow &window , Player &P)
{
    Vector2i pos = sf::Mouse::getPosition(window) ; 
    if(itemsSprite[0].getGlobalBounds().contains(float(pos.x) , float(pos.y)) && isMouseClicked())
    {
        getExtraLife(P) ; 
    }
    else if(itemsSprite[1].getGlobalBounds().contains(float(pos.x) , float(pos.y)) && isMouseClicked())
    {
        getSpeedBoost(P) ;
    }
    else if(itemsSprite[2].getGlobalBounds().contains(float(pos.x) , float(pos.y)) && isMouseClicked())
    {
        getSnowBall(P) ;
    }
    else if(itemsSprite[3].getGlobalBounds().contains(float(pos.x) , float(pos.y)) && isMouseClicked())
    {
        getDistanceIncrese(P) ; 
    }
    else if(itemsSprite[4].getGlobalBounds().contains(float(pos.x) , float(pos.y)) && isMouseClicked())
    {
        getBallonMode(P) ; 
    }
}


void SHOP::Draw(sf::RenderWindow &window , Player &P) 
{
    Update(window , P) ;
    window.draw(background) ;
    for(int st = 0 ; st <= totalItems -  1 ; st++)
    {
        Vector2i pos = sf::Mouse::getPosition(window) ; 
        if(itemsSprite[st].getGlobalBounds().contains(float(pos.x) , float(pos.y)))
        {
            cards[st].setFillColor(sf::Color(r  , g , b)) ;
        }
        else 
        {
            cards[st].setFillColor(sf::Color(100 , 100 , 100)) ;
        }
    }
    for(int st =  0 ; st <= totalItems -  1 ; st++)
    {
        window.draw(itemsSprite[st]) ;
        window.draw(cards[st]) ; 
    }
    for(int st = 0 ;  st <= totalItems - 1 ; st++)
    {
        window.draw(cardstext[st]) ; 
    }
    if(float(currentime.getElapsedTime().asSeconds()) >= animationtime)
    {
       r = (int)(std::sin(speedofColorChanging * 1.0f + 0.0f) * 127 + 128);
       g = (int)(std::sin(speedofColorChanging * 1.0f + 2.094f) * 127 + 128); 
       b = (int)(std::sin(speedofColorChanging * 1.0f + 4.189f) * 127 + 128); 
       speedofColorChanging += 0.05f;
       r %= 255 ;
       g %= 255 ;
       b %= 255 ; 
        Heading.setFillColor(sf::Color(r , g , b)) ; 

    }



    window.draw(Heading)  ;
}

#endif