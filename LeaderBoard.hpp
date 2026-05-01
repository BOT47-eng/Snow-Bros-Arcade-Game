#include <iostream>
#include <cstring>
#include <SFML/Graphics.hpp>
#include <fstream>
using namespace std ;
using namespace sf;


class LEADERBOARD
{
private :  
string *playerNames; 
int *scores;
sf::View *view ;
sf::Texture tex ;
sf::Sprite background ; 
sf::Font font;

public : 

LEADERBOARD()
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
    Vector2f texSize = {float(tex.getSize().x)  , float(tex.getSize().y)} ; 
    Vector2f windowSize = {600 , 600} ; 
    float ScaleX = (float) windowSize.x / texSize.x;
    float ScaleY = (float) windowSize.y / texSize.y; 
    background.setTexture(tex) ;
    background.setScale(ScaleX , ScaleY) ; 
    /////////////////////////////////////
    /////////////////////////////////////
    

    view = new View({ 600 / 2, 600 / 2 }, { 600, 600 }) ;
    playerNames = nullptr ;  
    scores = nullptr ;
}
~LEADERBOARD()
{
    if(playerNames != nullptr)
    {
        delete [] playerNames ;
    }
    if(scores != nullptr)
    {
        delete [] scores ; 
    }
    delete view ;
}

void sortRanking() ;
int countNoOfPlayers() ; 
void saveToFile(string name, int scores) ; 
void loadFromFile() ; 
void draw(sf::RenderWindow &window) ;
};

void LEADERBOARD::saveToFile(string name , int scores)
{
    ofstream file ;
    file.open("Leaderboard.txt" , ios::app)  ;
    if(!file.is_open())
    {
        cout << "Error in Opening the leaderboard.txt file\n" ;
        exit(0) ; 
    }
    file << name << " " << scores << endl  ; 
    file.close() ; 
}

int LEADERBOARD::countNoOfPlayers()
{
    int size = 0; 
    ifstream file ; 
    file.open("Leaderboard.txt" , ios::in) ; 
    if(!file.is_open())
    {
        cout << "Error in Opening the leaderboard.txt file\n" ;
        exit(0) ; 
    }
    string s ;
    int  a  ;
    while(file >> s >> a)
    {
        size++; 
    }
    file.close() ; 
    return size  ;
}
void LEADERBOARD::sortRanking()
{
    const int size = countNoOfPlayers() ;
    for(int st  = 0 ; st <= size - 1 ; st++)
    {
        for(int st2 = 0  ; st2 <= size - st - 1 ; st2++)
        {
            if(st2 != size - 1 && scores[st2 + 1] > scores[st2])
            {

                int temp = scores[st2 + 1] ;
                scores[st2 + 1] = scores[st2] ;
                scores[st2] = temp ; 

                string tempString = playerNames[st2 + 1] ;
                playerNames[st2+  1] = playerNames[st2] ;
                playerNames[st2] = tempString ; 
                
            }
        }
    }
    // for(int st = 0 ; st <= size - 1 ; st++)
    // {
    //     cout << playerNames[st] << " " << scores[st] << endl ;
    // }
}

void LEADERBOARD::loadFromFile()
{
    const int size = countNoOfPlayers() ;
    if(size == 0)
    {
        return  ;
    }
    playerNames = new string[size] ;
    scores = new int[size]; 
    ifstream file ; 
    file.open("Leaderboard.txt" , ios::in) ; 
	//Making sure start from top
    file.clear() ;
	file.seekg(0, ios::beg);
    if(!file.is_open())
    {
        cout << "Error in Opening the leaderboard.txt file\n" ;
        exit(0) ; 
    }
    string s ;
    int  a  ;
    int index = 0 ; 
    while(file >> s >> a)
    {
        playerNames[index] = s ; 
        scores[index] = a  ;
        index++ ;
    }
    sortRanking() ;
    file.close() ;
}

void LEADERBOARD::draw(sf::RenderWindow &window)
{
    sf::Event event;
    const int size = countNoOfPlayers();

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::MouseWheelScrolled)
        {
            view->move({ 0, -event.mouseWheelScroll.delta * 20.f });
        }
    }
    window.setView(window.getDefaultView()) ;
    window.draw(background)  ;

    window.setView(*view);
    // Now i can draw everything under this view 


    sf::Text title("TOP PLAYER RANKING", font, 80);
    title.setFillColor(sf::Color::Red);
    title.setPosition(100, 0);
    window.draw(title);

    sf::Text labels("RANK    NAME            SCORE", font, 60);
    labels.setFillColor(sf::Color::Blue);
    labels.setPosition(50, 45);
    window.draw(labels);


    for (int i = 0; i < size; i++)
    {
        float yPos = 100 + (i * 35);

        sf::Text txtRank(to_string(i + 1) + ".", font, 60);
        txtRank.setPosition(60, yPos);
        txtRank.setFillColor(sf::Color::White) ; 

        sf::Text txtName(playerNames[i], font, 60);
        txtName.setPosition(150, yPos);
        txtName.setFillColor(sf::Color::White) ; 


        sf::Text txtScore(to_string(scores[i]), font, 60);
        txtScore.setPosition(300, yPos);
        txtScore.setFillColor(sf::Color::White) ; 


        if      (i == 0) txtRank.setFillColor(sf::Color(255, 215, 0));
        else if (i == 1) txtRank.setFillColor(sf::Color(192, 192, 192));
        else if (i == 2) txtRank.setFillColor(sf::Color(205, 127, 50));

        window.draw(txtRank);
        window.draw(txtName);
        window.draw(txtScore);
    }


}

