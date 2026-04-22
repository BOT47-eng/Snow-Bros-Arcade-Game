#include <iostream>
#include <cstring>
#include <SFML/Graphics.hpp>





void CheckEvents(sf::RenderWindow  &mywindow)
{
    sf::Event e  ;
    while(mywindow.pollEvent(e))
    {
        switch (e.type)
        {
        case sf::Event::Closed :
            {
            mywindow.close() ; 
            break;
            }
        
        case sf::Event::KeyPressed: 
            {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                mywindow.close() ;
            }
            break;
            }
        }// Switch Ends 
    }
    return ; 
}






////////////////////////////
///// Base Class for Levels
///// 

class Level // Abstract Class
{
private: 

sf::Texture MapTex ;
sf::Sprite Map  ;
sf::Sprite *Blocks ;
int TotalNumberofBlocks ; 

//////////////////// TODO
// Class PauseButton Obj Here ;
bool isPauseButtonClicked ; 

/////////////////// TODO
/// Class Shop Obj Here ; 
sf::Sprite  GemsImage ; 


int Playerlives ; 
sf::Sprite PlayerlivesHeartImage ; 

////////////////////// TODO
/// Class Player Obj1 and Obj2 

int Player1Score ;
int Player2Score ; 
bool isPlayer2Active ;

///////////////////// TODO
/// Class Enemy Pointers Array


public : 
/////////////////////
/// Constructors
Level()
{
    Blocks = nullptr ;
    TotalNumberofBlocks = 0 ; 
}
Level(const sf::Texture mapTex,  const sf::Sprite Map ,const  sf::Sprite *Blocks, const  int TotalNumberofBlocks)
{
  this->MapTex = mapTex ;
  this->Blocks = new sf::Sprite[TotalNumberofBlocks] ; 
  this->Map = Map ;
  this->TotalNumberofBlocks = TotalNumberofBlocks ; 
  for(int st = 0 ; st <= TotalNumberofBlocks -  1; st++)
  {
    this->Blocks[st] =  Blocks[st]; 
  }
}

/////////////////////
/// Destructors
virtual ~Level()
{
    delete [] Blocks ;
}


/////////////////////
// Setters 
void setMapTexture(sf::Texture tex)
{
    MapTex = tex ; 
}
void setMap(sf::Sprite M)
{
    /// Scaling Map 
    const  unsigned int WINDOWHEIGHT = 600 ;
    const  unsigned int WINDOWWIDTH = 600 ;
    
    float ScaleY = WINDOWHEIGHT / float(MapTex.getSize().y) ;
    float ScaleX = WINDOWWIDTH /  float(MapTex.getSize().x); 
    Map = M ; 
    Map.setScale(ScaleX  , ScaleY) ;
}
void setBlocks(sf::Sprite *Blocks , const int Size) // Allocates Memory aswell for the Blocks don't allocate it seperately
{
    this->Blocks = new sf::Sprite[Size] ; 
    for(int st = 0 ; st <= Size - 1 ; st++)
    {
        this->Blocks[st] = Blocks[st] ; 
    }
}

//////////////////////
////// Getters






/////////////////////////////
////// Create Function
virtual void CreateLevel() = 0 ; // Simply Creates the whole level for specific level class 






//////////////////////////////
/// Update Function 


virtual void Update(sf::RenderWindow &mywindow) = 0 ;


////////////////////////////
///// Draw Function


virtual void Draw(sf::RenderWindow &mywindow) = 0 ;
// {
//     mywindow.clear() ; // Don't touch 
//     /*------------------Drawing is Gonna Start from here , Be mindful of the order you draw------------*/
//     ///////////////// 
//     //// Map Draw 
//     mywindow.draw(Map) ;




//     /*------------------------------- */
//     mywindow.display() ;  // Don't touch 
// }


}; 