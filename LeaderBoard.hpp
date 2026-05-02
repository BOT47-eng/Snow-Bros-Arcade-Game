#pragma once

#include <iostream>
#include <cstring>
#include <SFML/Graphics.hpp>
#include <fstream>
using namespace std ;
using namespace sf;

class Leaderboard
{
private :  
    string *playerNames; 
    int *scores;
    int* levels;
    string* dates;

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
            cout << "Error in loading the tex for leaderboard background\n" ; 
            exit(0) ;
        }
        if(!font.loadFromFile("Resources/SnowBrosAssets/Fonts/normal-font.ttf"))
        {
            cout << "Error in loading the font for leaderboard background\n" ; 
            exit(0) ;
        }
        if(!GoBackTexture.loadFromFile("Resources/SnowBrosAssets/Images/ReturnButtonforLeaderboard.jpg" , {668 ,  792 , 110 ,114}))
        {
            cout << "Error in loadingt the return button sprite in Leaderboard.hpp\n" ;
            exit(0) ;
        }
        Vector2f texSize = {float(tex.getSize().x)  , float(tex.getSize().y)} ; 
        Vector2f windowSize = {600 , 600} ; 
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
        view = new View({ 600 / 2, 600 / 2 }, { 600, 600 }) ;
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
    void saveToFile(string name, int scores, int levelReached, string date) ;
    void loadFromFile() ; 
    void draw(sf::RenderWindow &window) ;
};



