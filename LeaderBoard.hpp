#pragma once

#include <iostream>
#include <cstring>
#include <SFML/Graphics.hpp>
#include <fstream>

class Leaderboard
{
private :  
    std::string *playerNames; 
    int *scores;
    int* levels;
    std::string* dates;

    sf::View *view ;
    sf::Texture tex ;
    sf::Sprite background ; 
    sf::Font font;

public : 

    bool drawLeaderboard;
    sf::Texture GoBackTexture;
    sf::Sprite GobackSprite;

    Leaderboard()
    {
        /////////////////////////////////////
        /// Just Loading the background Image
        if(!tex.loadFromFile("Resources/SnowBrosAssets/Images/LeaderBoard_Background.jpg"))
        {
            std::cout << "Error in loading the tex for leaderboard background\n" ; 
            exit(0) ;
        }
        if(!font.loadFromFile("Resources/SnowBrosAssets/Fonts/normal-font.ttf"))
        {
            std::cout << "Error in loading the font for leaderboard background\n" ; 
            exit(0) ;
        }
        if(!GoBackTexture.loadFromFile("Resources/SnowBrosAssets/Images/ReturnButtonforLeaderboard.jpg" , {668 ,  792 , 110 ,114}))
        {
            std::cout << "Error in loadingt the return button sprite in Leaderboard.hpp\n" ;
            exit(0) ;
        }
        sf::Vector2f texSize = {float(tex.getSize().x)  , float(tex.getSize().y)} ; 
        sf::Vector2f windowSize = {600 , 600} ; 
        float ScaleX = (float) windowSize.x / texSize.x;
        float ScaleY = (float) windowSize.y / texSize.y; 
        background.setTexture(tex) ;
        background.setScale(ScaleX , ScaleY) ; 
        GobackSprite.setTexture(GoBackTexture) ;
        GobackSprite.setScale(0.4 , 0.4); 
        GobackSprite.setPosition(0, 0) ; 
        /////////////////////////////////////
        /////////////////////////////////////
    
        playerNames = nullptr;
        scores = nullptr;
        levels = nullptr;
        dates = nullptr;
        view = new sf::View({ 600 / 2, 600 / 2 }, { 600, 600 }) ;
        drawLeaderboard = false ;
    }
    ~Leaderboard()
    {
        if (playerNames)
            delete[] playerNames;
        if (scores)
            delete[] scores;
        if (levels)
            delete[] levels;
        if (dates)
            delete[] dates;

        delete view ;
    }

    void sortRanking() ;
    int countNoOfPlayers() ; 
    void saveToFile(std::string name, int scores, int levelReached, std::string date) ;
    void loadFromFile() ; 
    void draw(sf::RenderWindow &window) ;
};



