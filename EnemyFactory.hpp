#pragma once
#include <iostream>
#include <cstring>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Hitbox.hpp"
#include "Block.hpp"
#include "AnimationComponent.hpp"
#include "Projectile.hpp"
//#include "Snowball.cpp"


//#ifndef ENEMYFACTORY 
//#define ENEMYFACTORY 


///////////////////////
/// Base Abstract Class + All the Derived Classes 

class Enemy
{
protected:
    ///////////////////////
    //// Basic Properties
    int health ; 
    int healthOriginal;
    float x;
    float y; 
    float Vx ;
    float Vy ;
    bool isBoss;
    bool isFlying;

    float CopyVx ;  // To use incase the actual value is 0
    float CopyVy ; 

    ////////////////////////////////
    ///// Different Sprite Animation 
    sf::Texture snowballTexture;
    sf::Texture EnemySpriteTexture ; 
    sf::Texture botomSpriteTexture;
    sf::Texture flyingFroogaSpriteTexture;
    HitboxSprite EnemySprite;

    ///////////////////////////
    ///// All Other Necessary Functions for an Enemy Class 

    void UpateAnimationPerFrameofEnemy_X() ;
    void UpateAnimationPerFrameofEnemy_Y() ;

    float snowAccumulated;
    bool isFullyCoated;
    sf::Clock shakeTimer;
    float originalSpeed;

    bool isSnowball;
    bool isSnowballBreakingOut;
    float snowballVelocityX;
    float snowballVelocityY;
    float snowballStaticTimer;
    int snowballKillCount;
    bool snowballOnGround;
    float snowballPushDirection;
    int snowballCreatorPlayer;
    AnimationComponent animSnowballRoll;
    AnimationComponent animSnowballBreakout;
    AnimationComponent* currentSnowballAnim;

    IntRect frames[4] = { sf::IntRect(92, 3584, 230, 278), sf::IntRect(391, 3588, 238, 278), sf::IntRect(694, 3582, 234, 278), sf::IntRect(1001, 3580, 237, 278) };
    IntRect breakoutFrames[4] = { sf::IntRect(102, 3896, 210, 264), sf::IntRect(379, 3887, 249, 274), sf::IntRect(691, 3889, 249, 274), sf::IntRect(980, 3885, 271, 288) };

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

    float getSnowAccumulated() const { return snowAccumulated; }
    bool getIsFullyCoated() const { return isFullyCoated; }
    bool getIsSnowball() const { return isSnowball; }
    bool getIsSnowballBreakingOut() const { return isSnowballBreakingOut; }
    float getSnowballVelocityX() const { return snowballVelocityX; }
    float getSnowballVelocityY() const { return snowballVelocityY; }
    int getSnowballKillCount() const { return snowballKillCount; }
    bool getSnowballOnGround() const { return snowballOnGround; }
    int getSnowballCreatorPlayer() const { return snowballCreatorPlayer; }
    bool getIsFlying() const { return isFlying; }

    void applySnow(float amount, int playerID = 0);
    void updateCoatedState();
    void shakeOffSnow();
    void convertToSnowball();
    void updateSnowballState(float dt);
    void breakOutOfSnowball();
    void setSnowballVelocityX(float vx) { snowballVelocityX = vx; }
    void setSnowballVelocityY(float vy) { snowballVelocityY = vy; }
    void setSnowballOnGround(bool onGround) { snowballOnGround = onGround; }
    void setSnowballPushDirection(float dir) { snowballPushDirection = dir; }
    void incrementSnowballKillCount() { snowballKillCount++; }

    Enemy() : health(0), x(0), y(0), Vx(0), Vy(0), CopyVx(0), CopyVy(0), isSnowball(false), isSnowballBreakingOut(false), snowballVelocityX(0), snowballVelocityY(0), snowballStaticTimer(0), snowballKillCount(0), snowballOnGround(false), snowballPushDirection(0), snowballCreatorPlayer(0), currentSnowballAnim(nullptr), isBoss(false), isFlying(false)
    {
        if (!snowballTexture.loadFromFile("Resources/SnowBrosAssets/Images/Nick.png"))
        {
            std::cout << "Error loading snowball texture\n";
        }

    }

    Enemy(int h, float x, float y, float dx, float dy) : health(h), x(x), y(y), Vx(dx), Vy(dy), snowAccumulated(0), isFullyCoated(false), originalSpeed(0), isSnowball(false), isSnowballBreakingOut(false), snowballVelocityX(0), snowballVelocityY(0), snowballStaticTimer(0), snowballKillCount(0), snowballOnGround(false), snowballPushDirection(0), snowballCreatorPlayer(0), currentSnowballAnim(nullptr), isFlying(false)
    {
        if (!snowballTexture.loadFromFile("ResourcesSnowBrosAssets/Images/Nick.png"))
        {
            std::cout << "Error loading snowball texture\n";
        }
    }


    virtual ~Enemy()
    {
        //Does not point to heap
        /*if(currentSnowballAnim != nullptr)
            delete [] currentSnowballAnim ;*/
    }


    //////////////////////
    //// Main Functions for Every Enemy 
    virtual void CreateEnemy(float x , float y) = 0 ;
    virtual void update(const float dt, Block* B, const int BLOCKSIZE) = 0;
    virtual void draw(sf::RenderWindow &mywindow, bool debug) = 0 ;
    virtual int getScore() = 0;
}; 
//#endif

///////////////////////////////////////////////////////////////
/////////// Dereiving All the other Necessary Enemy Classes


//#ifndef BOTOM
//#define BOTOM

class Botom : public Enemy
{
protected : 

    bool isLeft ; // For whenever change in x is negative 
    bool isRight; // For whenever change in x is positive 
    bool isJumping ; // For whenever change in y is negative hence true 
    bool isFallingDown ; // For whenever change in y is postive hence true 
    float gravityfactor ;
    sf::Clock timeToChangeDirection ; 
    sf::Clock timeToJump ; 
    sf::Clock  JumpInterval ; // To Keep track of the Jump time and bring it back to land

    //////////////////////////////
    ///// Adding the Different animation sprite 
    sf::Texture *EnemySpriteFallingDownTexture ; 
    sf::Texture *EnemySpriteRightMovementTextures ;
    sf::Texture *EnemySpriteLeftMovementTextures ;
    sf::Texture *EnemySpriteJumpingUpTexture ; 


    int TotalAnimationofJump ;
    int TotalAnimationofFalling ;
    int TotalAnimationofRightMovement ;
    int TotalAnimationofleftMovement ; 

    int currentIndexofJumpAnimation ;
    int currentIndexofFallAnimation ;
    int currentIndexofRightAnimation ;
    int currentIndexofLeftAnimation ;


    sf::Clock animationClock; 
    float animationSpeed; // How long each frame stays on screen (in seconds)



public:
    ///////////////////////
    /////// Constructors

    Botom() : isLeft(false) , isRight(true) , isJumping(false) , isFallingDown(false) , gravityfactor(980)  , Enemy()
    {
        timeToChangeDirection.restart() ; 
        timeToJump.restart() ; 
        JumpInterval.restart() ;
        EnemySpriteFallingDownTexture = nullptr ; 
        EnemySpriteRightMovementTextures = nullptr ;
        EnemySpriteLeftMovementTextures = nullptr ;
        EnemySpriteJumpingUpTexture = nullptr ; 
    
        TotalAnimationofFalling =  0 ;
        TotalAnimationofJump = 0 ; 
        TotalAnimationofleftMovement = 0 ;
        TotalAnimationofRightMovement = 0 ;

        currentIndexofFallAnimation = 0 ;
        currentIndexofJumpAnimation = 0 ;
        currentIndexofLeftAnimation = 0 ;
        currentIndexofRightAnimation = 0 ;
    
        animationSpeed = 0.15f ; 
        animationClock.restart() ; 
        isBoss = false;
        isFlying = false ;
    } 
    ///////////////////////////
    //////// Destructors 
    virtual ~Botom()
    {
        delete [] EnemySpriteFallingDownTexture ;
        delete [] EnemySpriteJumpingUpTexture ;
        delete [] EnemySpriteLeftMovementTextures ; 
        delete [] EnemySpriteRightMovementTextures ; 
    }
    void UpdateDirection_X() // It is just  a random direction setter 
    {
        int RandomTimeToChangeDirection = (rand() % (5 - 3 + 1)) + 3 ; // To make the movement feel more natural
        if(timeToChangeDirection.getElapsedTime().asSeconds() > RandomTimeToChangeDirection)
        {
            setVx(-getVx()) ; 
            timeToChangeDirection.restart() ; 
        }
    }
    ///////////////////////////////////////////////////////////////////////////////////////////
    /////////////// So Extra Functions Required in the update function 
    ///////////////
    // So The Animation of sprites starts from the beginning not the end
    void ResetCurrentIndexofFallAnimation()
    {
        currentIndexofFallAnimation = 0 ;
    }

    void ResetCurrentIndexofJumpAnimation()
    {
        currentIndexofJumpAnimation =  0 ; 
    }
    void ResetCurrentIndexofLeftAnimation()
    {
        currentIndexofLeftAnimation = 0 ;
    }
    void ResetCurrentIndexofRightAnimation()
    {
        currentIndexofRightAnimation = 0; 
    }

    void UpdateToRightMovementAnimation()
    {
        EnemySprite.setTexture(EnemySpriteRightMovementTextures[currentIndexofRightAnimation] , true) ;
        currentIndexofRightAnimation = (currentIndexofRightAnimation + 1) % TotalAnimationofRightMovement ; 
    }
    void UpdateToLeftMovementAnimation()
    {
        EnemySprite.setTexture(EnemySpriteLeftMovementTextures[currentIndexofLeftAnimation] , true) ;
        currentIndexofLeftAnimation = (currentIndexofLeftAnimation + 1) % TotalAnimationofleftMovement ; 
    }
    void UpdateToJumpMovementAnimation()
    {
        EnemySprite.setTexture(EnemySpriteJumpingUpTexture[currentIndexofJumpAnimation] , true) ;
        currentIndexofJumpAnimation = (currentIndexofJumpAnimation + 1) % TotalAnimationofJump ; 
    }
    void UpdateToFallingMovementAnimation()
    {
        EnemySprite.setTexture(EnemySpriteFallingDownTexture[currentIndexofFallAnimation] ,true) ;
        currentIndexofFallAnimation = (currentIndexofFallAnimation) % TotalAnimationofFalling ; 
    }


    virtual void CreateEnemy(float x , float y) override
    {
        ///////////////////////////////////////
        ////// Creating the Enemy first 
        sf::Texture EnemyTexture;
        sf::IntRect area(2 , 934 , 88 , 93) ; // Default idle/start state
    
        std::string imagePath = "Resources/SnowBrosAssets/Images/Botom_Pink.png";
    
        if(!EnemyTexture.loadFromFile(imagePath , area))
        {
            std::cout << "Error in Loading the file\n" ;
            exit(0) ;
        }
        setEnemyTexture(EnemyTexture) ; // Default Standing 
        setEnemyHitBoxSprite() ; 
        ////////////////////////////////////////
        ///// SCALING THE SPRITE
        EnemySprite.setScale(0.5f, 0.5f); 

        ////////////////////////////////////////
        ///// Loading Different Animation texture in the arrays 

        TotalAnimationofRightMovement = 3;
        TotalAnimationofleftMovement = 3;
        TotalAnimationofJump = 1;
        TotalAnimationofFalling = 1;

        EnemySpriteRightMovementTextures = new sf::Texture[TotalAnimationofRightMovement];
        EnemySpriteLeftMovementTextures = new sf::Texture[TotalAnimationofleftMovement];
        EnemySpriteJumpingUpTexture = new sf::Texture[TotalAnimationofJump];
        EnemySpriteFallingDownTexture = new sf::Texture[TotalAnimationofFalling];


        // --- Right Movement Textures ---
        EnemySpriteRightMovementTextures[0].loadFromFile("Resources/SnowBrosAssets/Images/BotomPinkRight1.png");
        EnemySpriteRightMovementTextures[1].loadFromFile("Resources/SnowBrosAssets/Images/BotomPinkRight2.png");
        EnemySpriteRightMovementTextures[2].loadFromFile("Resources/SnowBrosAssets/Images/BotomPinkRight3.png");

        // --- Left Movement Textures ---
        EnemySpriteLeftMovementTextures[0].loadFromFile(imagePath, sf::IntRect(2, 367, 92, 82));
        EnemySpriteLeftMovementTextures[1].loadFromFile(imagePath, sf::IntRect(96, 367, 92, 82));
        EnemySpriteLeftMovementTextures[2].loadFromFile(imagePath, sf::IntRect(188, 367, 92, 82));

        // --- Jumping Up Textures ---
        EnemySpriteJumpingUpTexture[0].loadFromFile(imagePath, sf::IntRect(7, 477, 87, 95));

        // --- Falling Down Textures ---
        EnemySpriteFallingDownTexture[0].loadFromFile(imagePath, sf::IntRect(5, 597, 84, 91));

    
        /////////////////////////////////////////////
        ///// Now Setting the Properties of the Enemy
        sethealth(2);
        healthOriginal = 2;
        setPos(x , y) ;
        setVx(200) ;  /// TEST TO CHANGE LATER
        setVy(200) ;  // TEST TO CHANGE LATER 
        originalSpeed = 200;
        setCopyVx(200) ;
        setCopyVy(200) ;
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
    bool CheckCollionsWithScreenX(const float width, const float height)
    {
        bool flag = false;
        float halfW = EnemySprite.getGlobalBounds().width / 2.f;

        if (x + halfW > width)
        {
            x = width - halfW;
            setVx(-getVx());
            flag = true;
        }
        else if (x - halfW < 0)
        {
            x = halfW;  
            setVx(-getVx());
            flag = true;
        }

        EnemySprite.setPosition(x, y);
        return flag;
    }

    bool CheckCollionsWithScreenY(const float width, const float height)
    {
        bool flag = false;
        float halfH = EnemySprite.getGlobalBounds().height / 2.f;

        if (y + halfH > height)
        {
            y = height - halfH;
            setVy(0);
            flag = true;
        }
        else if (y - halfH < 0)
        {
            y = halfH;  
            setVy(abs(getVy()));
            flag = true;
        }

        EnemySprite.setPosition(x, y);
        return flag;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    //// Return True if It is on land else it return false in which case we have add the gravity factor
    bool CheckCollosionsWithPlatforms(Block* b, const int SIZE)
    {
        bool OnLand = false;
        float halfHeight = EnemySprite.getGlobalBounds().height / 2.0f;
        float floorY = 560.0f;

        for (int st = 0; st < SIZE; st++)
        {
            sf::FloatRect enemyBox = EnemySprite.getGlobalHitbox();
            sf::FloatRect blockBox = b[st].getHitbox();
            sf::FloatRect overlap;

            if (enemyBox.intersects(blockBox, overlap))
            {
                if (overlap.width < overlap.height)
                {
                    if (enemyBox.left < blockBox.left)
                    {
                        x = blockBox.left - enemyBox.width / 2.0;
                        setVx(-abs(getVx()));
                    }
                    else
                    {
                        x = blockBox.left + blockBox.width + enemyBox.width / 2.0;
                        setVx(abs(getVx()));
                    }
                }
                else
                {
                    if (enemyBox.top < blockBox.top)
                    {
                        y = blockBox.top - enemyBox.height / 2.0f;
                        setVy(0);
                        OnLand = true;
                        
                    }
                    else
                    {
                        y = blockBox.top + blockBox.height + enemyBox.height / 2.0f;
                        setVy(0);
                    }
                }

                EnemySprite.setPosition(x, y);
            }
        }

        if (y + halfHeight >= floorY)
        {
            y = floorY - halfHeight;
            setVy(0);
            OnLand = true;
        }

        EnemySprite.setPosition(x, y);
        return OnLand;
    }

    void EnemyWantsToJumporNot()
    {
        if(timeToJump.getElapsedTime().asSeconds() > 5 && Vx != 0)
        {
            if(rand() % 2)
            {
                isJumping = true ;
                JumpInterval.restart() ;
            }
            timeToJump.restart() ; 
        }
    }

    virtual void update(const float dt, Block* B, const int BLOCKSIZE) override
    {
        //////////////////////////////////////////
        /// update the Position  of the sprite 
        UpdateX(dt) ; // it will always be moving in x-direction
        UpdateY(dt);


        EnemySprite.setPosition(x , y) ;

        UpdateDirection_X() ;
        if(getVx() > 0)
        {
            isRight = true ; 
            isLeft = false ; 
        }
        else 
        {
            isLeft = true ;
            isRight = false ;
        }

        CheckCollionsWithScreenX(600  , 600) ; 
        CheckCollionsWithScreenY(600  , 600) ; 
        /// If the enemy Jumps Ignore  the platform collosions and go up till the box it is currently colliding with is not below it.
        if(!isJumping) 
        {
            bool CheckCollosionAndAlsoTellIfEnemyisOnLand = CheckCollosionsWithPlatforms(B , BLOCKSIZE);
            if(!CheckCollosionAndAlsoTellIfEnemyisOnLand)
            {
                // Add the gravity factor because if it was on land then Vy is 0 
                isFallingDown = true ;
                setVy(gravityfactor) ; 
                }
            else
            {
                // Else enemy is on land set it's Vx 
                isFallingDown = false ;
                setVx(getVx()) ; 
                setVy(0) ;
            }
        }
        EnemyWantsToJumporNot() ; 

        if(isJumping && float(JumpInterval.getElapsedTime().asSeconds()) < 0.3)
        {
            const int JumpFactorToSpeed = 1000 ;
            setVy(-getVy() - JumpFactorToSpeed) ;
        }
        else
        {
            isJumping = false ; 
            setVy(gravityfactor) ; 
        }


        ///////////////////////////////////////////////////////////////////////
        ////////////////////  Updating all the Animations of Enemy in Specific movements
    
        if(float(animationClock.getElapsedTime().asSeconds()) >= animationSpeed)
        {
            if(isLeft)
            {
                UpdateToLeftMovementAnimation() ; 
            }
            else if (isRight)
            {
                UpdateToRightMovementAnimation() ;
            }   
            else if(isJumping)
            {
                UpdateToJumpMovementAnimation() ;
            }
            else if(isFallingDown)
            {
                UpdateToFallingMovementAnimation() ; 
            }
            animationClock.restart() ;
        }



        //// If User Presses the F1/F2 button then we draw the hitbox 
        /*checkforShowHitBoxDetection(B , BLOCKSIZE) ; */
    }
    virtual void draw(sf::RenderWindow &mywindow, bool debug)  override
    {
        /// ONLY DRAW DON'T CLEAR OR DISPLAY
        mywindow.draw(Enemy::getEnemySprite()) ; 

        if (debug)
        {
            EnemySprite.drawHitbox(mywindow, Color::Red);
        }
    }

    virtual int getScore()
    {
        return 100 + rand() % 401;
    }
}; 
//#endif
//
//
//#ifndef FLYINGFOOGAFOOG
//#define FLYINGFOOGAFOOG

class FlyingFoogaFoog : public virtual Botom 
{
protected : 
    //////////////////////////
    /////// Brid Properties
    float isOnRestModeTime ; 
    sf::Clock CurrentTimeofIsOnRestMode ;

    float TotalTimeToChangeToRestMode ; 
    sf::Clock CurrentTimeToChangeToRestMode ; 

    float  Areialtime;
    sf::Clock CurrentAreialTime ;


    bool ChangedToRestMode ;
    bool isInAeialMode ;
    bool isOnRestMode; 


    /////////////////////////
    /// Bird Sprites Texture 
    /// I have my sprite inhereited from botom no need to add extra
    sf::Texture  DefaultOnLandTexture ; 
    sf::Texture *FlyingTexture ; 


    int TotalAnimationofFlying ;
   
    int CurrentIndexofAnimationofFlying;


public : 
    FlyingFoogaFoog() : Botom()
    {
        isOnRestModeTime = 2.0f ;
        Areialtime  = 8.0f ;
        CurrentAreialTime.restart() ;
        TotalTimeToChangeToRestMode =  5 ; 
        CurrentTimeToChangeToRestMode.restart() ; 

        isInAeialMode = false ;
        isOnRestMode = false ;
        ChangedToRestMode = false  ; 

        TotalAnimationofFlying  = 0 ;
        CurrentIndexofAnimationofFlying = 0; 
        FlyingTexture = nullptr ;

        sethealth(2);
        healthOriginal = 2;
        originalSpeed = 200;
        isBoss = false;
    }
    ~FlyingFoogaFoog() 
    {
        delete [] FlyingTexture ;
    }


    void setAreialtime(float f) {Areialtime = f;} 
    float getAreialtime() const {return Areialtime;} 


    protected : 
    ///////////////////////////////////////////////////////////////
    ///////// All the animation helpers for FlyingFoog
    void UpdateToRestMovementAnimation()
    {
        EnemySprite.setTexture(DefaultOnLandTexture) ; 
    }

    void UpdateToFlyingAnimation()
    {
        EnemySprite.setTexture(FlyingTexture[CurrentIndexofAnimationofFlying] , true) ;
        CurrentIndexofAnimationofFlying = (CurrentIndexofAnimationofFlying + 1) % TotalAnimationofFlying ;
    }

    ///////////////////////////////////////////////////////////////
    ///////// FIX: Clock only restarts after the threshold fires.
    ///////// Previously the else branch restarted on every non-triggering
    ///////// frame, so elapsed time could never reach TotalTimeToChangeToRestMode.
    bool ChangeToRestModeOrNot()
    {
        if(CurrentTimeToChangeToRestMode.getElapsedTime().asSeconds() >= TotalTimeToChangeToRestMode)
        {
            CurrentTimeToChangeToRestMode.restart() ; // restart only after threshold reached
            return (rand() % 2) == 1 ;
        }
        return false ;
    }

    bool CheckIfItIsOnLand(Block* b, const int SIZE)
    {
        bool onLand = false;
        float halfHeight = EnemySprite.getGlobalBounds().height / 2.0f;
        float floorY = 560.0f;
        bool timeToLand = ChangeToRestModeOrNot();

        for (int st = 0; st < SIZE; st++)
        {
            sf::FloatRect enemyBox = EnemySprite.getGlobalHitbox();
            sf::FloatRect blockBox = b[st].getHitbox();
            sf::FloatRect overlap;

            if (enemyBox.intersects(blockBox, overlap))
            {
                if (overlap.width > overlap.height)
                {
                    float enemyCenterY = enemyBox.top + enemyBox.height / 2.0f;
                    float blockCenterY = blockBox.top + blockBox.height / 2.0f;

                    if (enemyCenterY < blockCenterY) 
                    {
                        y = blockBox.top - enemyBox.height / 2.0f;
                        setVy(0);
                        onLand = true;
                        
                    }
                    EnemySprite.setPosition(x, y);
                }
            }
        }

        if (y + halfHeight >= floorY)
        {
            y = floorY - halfHeight;
            setVy(0);
            onLand = true;
        }

        EnemySprite.setPosition(x, y);
        return onLand;
    }


public : 

    virtual void CreateEnemy(float x , float y) 
    {
        sf::Texture EnemyTex ; 
        sf::IntRect area(50 , 30 , 97 ,162) ;
        if(!EnemyTex.loadFromFile("Resources/SnowBrosAssets/Images/FlyingFoogaFoog_Red.png" , area))
        {
            std::cout << "Error in Loading the FlyingFoogaRed\n" ; 
            exit(0) ; 
        }
        setEnemyTexture(EnemyTex) ;
        EnemySprite.setScale(0.3 , 0.3) ;
        setEnemyHitBoxSprite() ;

        ////////////////////////////////////////
        ///// Loading Different Animation texture in the arrays 
        TotalAnimationofRightMovement = 2;
        TotalAnimationofleftMovement = 2;
        TotalAnimationofJump = 2;
        TotalAnimationofFalling = 2;
        TotalAnimationofFlying = 2 ;

        EnemySpriteRightMovementTextures = new sf::Texture[TotalAnimationofRightMovement];
        EnemySpriteLeftMovementTextures = new sf::Texture[TotalAnimationofleftMovement];
        EnemySpriteJumpingUpTexture = new sf::Texture[TotalAnimationofJump];
        EnemySpriteFallingDownTexture = new sf::Texture[TotalAnimationofFalling];
        FlyingTexture = new sf::Texture[TotalAnimationofFlying];


        // Right Movement Textures _ areas
        sf::IntRect area1(18 , 440 , 160 ,133) ;
        sf::IntRect area2(215 , 436 , 166 , 126) ;

        EnemySpriteRightMovementTextures[0].loadFromFile("Resources/SnowBrosAssets/Images/FlyingFoogaFoog_Red.png" , area1);
        EnemySpriteRightMovementTextures[1].loadFromFile("Resources/SnowBrosAssets/Images/FlyingFoogaFoog_Red.png" , area2);

        //  Left Movement Textures
        EnemySpriteLeftMovementTextures[0].loadFromFile("Resources/SnowBrosAssets/Images/FlyingFoogaFoog_Red.png", area1);
        EnemySpriteLeftMovementTextures[1].loadFromFile("Resources/SnowBrosAssets/Images/FlyingFoogaFoog_Red.png", area2);

        // Jumping Up Textures arers
        sf::IntRect jumpArea1(41 , 242 , 131 , 137) ;
        sf::IntRect jumpArea2(230, 260 , 140  , 121) ; 

        EnemySpriteJumpingUpTexture[0].loadFromFile("Resources/SnowBrosAssets/Images/FlyingFoogaFoog_Red.png", jumpArea1);
        EnemySpriteJumpingUpTexture[1].loadFromFile("Resources/SnowBrosAssets/Images/FlyingFoogaFoog_Red.png", jumpArea2);

        // Falling Down Textures
        EnemySpriteFallingDownTexture[0].loadFromFile("Resources/SnowBrosAssets/Images/FlyingFoogaFoog_Red.png", jumpArea1);
        EnemySpriteFallingDownTexture[1].loadFromFile("Resources/SnowBrosAssets/Images/FlyingFoogaFoog_Red.png", jumpArea2);


        //// Default on Land / Rest Texture 
        sf::IntRect areaLand(49,  31 ,97 , 160) ;
        DefaultOnLandTexture.loadFromFile("Resources/SnowBrosAssets/Images/FlyingFoogaFoog_Red.png" , areaLand) ;


        // Flying Texture set
        sf::IntRect flyarea1(216 , 22 , 167 , 166) ; 
        sf::IntRect flyarea2(430 , 23 , 143 , 156)  ;
    
        FlyingTexture[0].loadFromFile("Resources/SnowBrosAssets/Images/FlyingFoogaFoog_Red.png" , flyarea1) ; 
        FlyingTexture[1].loadFromFile("Resources/SnowBrosAssets/Images/FlyingFoogaFoog_Red.png" , flyarea2) ; 



        /////////////////////////////////////////////
        ///// Now Setting the Properties of the Enemy
        setPos(x , y) ;
        setVx(200) ;
        setVy(200) ;
        originalSpeed = 200;
        setCopyVx(200) ;
        setCopyVy(200) ;
    }

    ///////////////////////////////////////////////////////////////
    /////// update for FlyingFoog — three mutually exclusive phases:
    /////// REST -> AERIAL -> NORMAL (with gravity/platforms)

    virtual void update(const float dt , Block *B , const int BLOCKSIZE) override
    {
        ///////////////////////////////////////////////////////////
        /////// PHASE 1 — REST MODE
        /////// Enemy is stationary. Gravity and platforms are skipped
        /////// entirely so nothing can push or pull it while resting.
        if(isOnRestMode)
        {
            // Hold position — no movement whatsoever
            setVx(0) ;
            setVy(0) ;
            EnemySprite.setPosition(x , y) ;

            // After rest duration expires → switch to aerial mode
            if(CurrentTimeofIsOnRestMode.getElapsedTime().asSeconds() >= isOnRestModeTime)
            {
                isFlying = true;
                isOnRestMode    = false ;
                ChangedToRestMode = false ;
                isInAeialMode   = true ;
                // Restore horizontal speed and launch upward to start aerial phase
                setVx(CopyVx) ;
                setVy(-CopyVy) ;
                CurrentAreialTime.restart() ;
            }

            // Animation
            if(animationClock.getElapsedTime().asSeconds() >= animationSpeed)
            {
                UpdateToRestMovementAnimation() ;
                animationClock.restart() ;
            }

            /*checkforShowHitBoxDetection(mywindow , B , BLOCKSIZE) ;*/
            return ; // Skip the rest of update — rest is its own complete state
        }

        ///////////////////////////////////////////////////////////
        /////// PHASE 2 — AERIAL MODE
        /////// Enemy flies freely. Gravity and platform checks are
        /////// skipped so it moves through the air unaffected.
        /////// Screen boundaries still apply so it can't leave the window.
        if(isInAeialMode)
        {
            UpdateX(dt) ;
            UpdateY(dt) ;
            EnemySprite.setPosition(x , y) ;

            UpdateDirection_X() ;
            if(getVx() > 0) { isRight = true  ; isLeft = false ; }
            else             { isLeft  = true  ; isRight = false ; }

            // Screen boundaries bounce the enemy so it stays visible
            CheckCollionsWithScreenX(600 , 600) ;
            // For aerial Y: bounce off top/bottom instead of stopping
            if(y + EnemySprite.getGlobalBounds().height > 600)
            {
                y = 600 - EnemySprite.getGlobalBounds().height ;
                setVy(-abs(getVy())) ; // bounce up
            }
            else if(y < 0)
            {
                y = 0 ;
                setVy(abs(getVy())) ; // bounce down
            }
            EnemySprite.setPosition(x , y) ;

            // After aerial duration expires → fall back to normal mode
            if(CurrentAreialTime.getElapsedTime().asSeconds() >= Areialtime && CheckIfItIsOnLand(B , BLOCKSIZE))
            {
                isFlying = false;
                isInAeialMode = false ;
                isFallingDown = true  ;
                setVy(gravityfactor)  ;
            }

            // Animation
            if(animationClock.getElapsedTime().asSeconds() >= animationSpeed)
            {
                UpdateToFlyingAnimation() ;
                animationClock.restart() ;
            }
            
            /*checkforShowHitBoxDetection(mywindow , B , BLOCKSIZE) ;*/
            return ; // Skip the rest of update — aerial is its own complete state
        }

        ///////////////////////////////////////////////////////////
        /////// PHASE 3 — NORMAL MODE (walking / jumping on platforms)
        /////// Identical to Botom logic, plus a check at the end
        /////// to decide whether to enter rest mode.

        UpdateX(dt) ;
        UpdateY(dt) ;
        EnemySprite.setPosition(x , y) ;

        UpdateDirection_X() ;
        if(getVx() > 0) { isRight = true  ; isLeft = false ; }
        else             { isLeft  = true  ; isRight = false ; }

        CheckCollionsWithScreenX(600, 600) ;
        CheckCollionsWithScreenY(600, 600) ;

        if(!isJumping)
        {
            bool onLand = CheckCollosionsWithPlatforms(B , BLOCKSIZE) ;
            if(!onLand)
            {
                isFallingDown = true ;
                setVy(gravityfactor) ;
            }
            else
            {
                isFallingDown = false ;
                setVy(0) ;
            }
        }

        EnemyWantsToJumporNot() ;

        if(isJumping && float(JumpInterval.getElapsedTime().asSeconds()) < 0.3f)
        {
            const int JumpFactorToSpeed = 1000 ;
            setVy(-getVy() - JumpFactorToSpeed) ;
        }
        else
        {
            isJumping = false ;
            setVy(gravityfactor) ;
        }

        ///////////////////////////////////////////////////////////
        /////// Check whether to enter rest mode only while
        /////// in normal mode. ChangeToRestModeOrNot() now only
        /////// restarts its clock after the threshold fires, so
        /////// this check will actually trigger every ~10 seconds.
        if(ChangeToRestModeOrNot())
        {
            isOnRestMode = true ;
            ChangedToRestMode = true ;
            CurrentTimeofIsOnRestMode.restart() ;
        }

        ///////////////////////////////////////////////////////////
        /////// Simple animation change like botom
        if(animationClock.getElapsedTime().asSeconds() >= animationSpeed)
        {
            if(isLeft)          
                UpdateToLeftMovementAnimation() ;
            else if(isRight)    
                UpdateToRightMovementAnimation() ;
            else if(isJumping)  
                UpdateToJumpMovementAnimation() ;
            else if(isFallingDown) 
                UpdateToFallingMovementAnimation() ;

            animationClock.restart() ;
        }
    }

    virtual void draw(sf::RenderWindow &mywindow, bool debug) override
    {
        mywindow.draw(Enemy::getEnemySprite()) ; 

        if (debug)
            EnemySprite.drawHitbox(mywindow, Color::Red);

    }

    virtual int getScore()
    {
        return 200 + rand() % 601;
    }
    
}; 

//#endif
//
//
//#ifndef TORNADO
//#define TORNADO

class Tornado :  public virtual FlyingFoogaFoog 
{
protected: 
    ////////////////////
    // Just adding the feature of knife throwing
    sf::Clock TimerForThrowKnifeOrNot ; 
    float TotalTimeForThrowKnife  ;


    //// If Time is true to throw knife now then 
    sf::Clock TimeToThrowKnife ;
    float TimeTakenToThrowKnife ; 

    bool isThrowingTheKnife ;

    int currentIndexOfKnifethrowingAnimation; 
    sf::Texture *EnemyKnifeThrowingTexture ;
    int TotalAnimationofKnifeThrowingTexture ;

    sf::Clock knifeTimer ;
    sf::Texture KnifeTex ;
    Snowball *Knife ; 
    bool isKnifeFired ;

public : 
    Tornado()
    {
        isKnifeFired = false; 
        knifeTimer.restart() ;
        Knife = new Snowball ; 

        TimerForThrowKnifeOrNot.restart() ;
        TimeToThrowKnife.restart() ; 

        currentIndexOfKnifethrowingAnimation =  0; 
        isThrowingTheKnife = false; 
        TotalAnimationofKnifeThrowingTexture = 1 ; 
        TimeTakenToThrowKnife = 1 ;

        TotalTimeForThrowKnife = 5 ; 
        EnemyKnifeThrowingTexture  = nullptr ; 
        isBoss = false;
    }

    virtual ~Tornado()
    {
        delete Knife ;
        delete [] EnemyKnifeThrowingTexture ;
    }


    virtual  void CreateEnemy(float x , float y) 
    {
        sf::Texture EnemyTex ; 
        sf::IntRect area(9 , 41 , 122 ,122) ;
        if(!EnemyTex.loadFromFile("Resources/SnowBrosAssets/Images/Tornado_Red.png" , area))
        {
            std::cout << "Error in Loading the TornadoRed Texture\n" ; 
            exit(0) ; 
        }
        setEnemyTexture(EnemyTex) ;
        EnemySprite.setScale(0.3 , 0.3) ;
        setEnemyHitBoxSprite() ;




        ////////////////////////////////////////
        ///// Loading Different Animation texture in the arrays 
        TotalAnimationofRightMovement = 3 ;
        TotalAnimationofleftMovement = 3 ;
        TotalAnimationofJump = 1 ;
        TotalAnimationofFalling = 1 ;
        TotalAnimationofFlying = 8 ;
        TotalAnimationofKnifeThrowingTexture = 2 ; 


        EnemySpriteRightMovementTextures = new sf::Texture[TotalAnimationofRightMovement];
        EnemySpriteLeftMovementTextures = new sf::Texture[TotalAnimationofleftMovement];
        EnemySpriteJumpingUpTexture = new sf::Texture[TotalAnimationofJump];
        EnemySpriteFallingDownTexture = new sf::Texture[TotalAnimationofFalling];
        FlyingTexture = new sf::Texture[TotalAnimationofFlying];
        EnemyKnifeThrowingTexture = new sf::Texture[TotalAnimationofKnifeThrowingTexture] ; 


        // Right Movement Textures _ areas

        EnemySpriteRightMovementTextures[0].loadFromFile("Resources/SnowBrosAssets/Images/TornadoRed_01.png");
        EnemySpriteRightMovementTextures[1].loadFromFile("Resources/SnowBrosAssets/Images/TornadoRed_02.png");
        EnemySpriteRightMovementTextures[2].loadFromFile("Resources/SnowBrosAssets/Images/TornadoRed_03.png");

        //  Left Movement Textures
        sf::IntRect area1(146 , 36 , 122 , 121) ;
        sf::IntRect area2(283 , 36 , 122 , 122) ;
        sf::IntRect area3(428 , 36 , 122 , 122) ;

        EnemySpriteLeftMovementTextures[0].loadFromFile("Resources/SnowBrosAssets/Images/Tornado_Red.png", area1);
        EnemySpriteLeftMovementTextures[1].loadFromFile("Resources/SnowBrosAssets/Images/Tornado_Red.png", area2);
        EnemySpriteLeftMovementTextures[2].loadFromFile("Resources/SnowBrosAssets/Images/Tornado_Red.png", area3);

        // Jumping Up Textures arers
        sf::IntRect jumpArea1(14 , 205 , 122 , 122) ;

        EnemySpriteJumpingUpTexture[0].loadFromFile("Resources/SnowBrosAssets/Images/Tornado_Red.png", jumpArea1);

        // Falling Down Textures
        sf::IntRect FallArea1(8 ,  541 , 122 , 122) ;
        EnemySpriteFallingDownTexture[0].loadFromFile("Resources/SnowBrosAssets/Images/Tornado_Red.png", FallArea1);


        //// Default on Land / Rest Texture 
        sf::IntRect areaLand(9 , 41 , 122 ,122)  ;
        DefaultOnLandTexture.loadFromFile("Resources/SnowBrosAssets/Images/Tornado_Red.png" , areaLand) ;


        // Flying Texture set
        sf::IntRect flyarea1(8 , 1045 , 122 , 122) ; 
        sf::IntRect flyarea2(150 , 1048 , 122 , 122)  ;
        sf::IntRect flyarea3(288 , 1044 , 122 , 122)  ;
        sf::IntRect flyarea4(423 , 1042 , 122 , 122)  ;
        sf::IntRect flyarea5(552 , 1047 , 122 , 122)  ;
        sf::IntRect flyarea6(700 , 1058 , 122 , 122)  ;
        sf::IntRect flyarea7(856 , 1048 , 122 , 122)  ;
        sf::IntRect flyarea8(980 , 1041 , 122 , 122)  ;

    
        FlyingTexture[0].loadFromFile("Resources/SnowBrosAssets/Images/Tornado_Red.png" , flyarea1) ; 
        FlyingTexture[1].loadFromFile("Resources/SnowBrosAssets/Images/Tornado_Red.png" , flyarea2) ; 
        FlyingTexture[2].loadFromFile("Resources/SnowBrosAssets/Images/Tornado_Red.png" , flyarea3) ; 
        FlyingTexture[3].loadFromFile("Resources/SnowBrosAssets/Images/Tornado_Red.png" , flyarea4) ; 
        FlyingTexture[4].loadFromFile("Resources/SnowBrosAssets/Images/Tornado_Red.png" , flyarea5) ; 
        FlyingTexture[5].loadFromFile("Resources/SnowBrosAssets/Images/Tornado_Red.png" , flyarea6) ; 
        FlyingTexture[6].loadFromFile("Resources/SnowBrosAssets/Images/Tornado_Red.png" , flyarea7) ; 
        FlyingTexture[7].loadFromFile("Resources/SnowBrosAssets/Images/Tornado_Red.png" , flyarea8) ; 


        EnemyKnifeThrowingTexture[0].loadFromFile("Resources/SnowBrosAssets/Images/Tornado_Red.png" , {30 , 882  , 110 , 111}); 
        EnemyKnifeThrowingTexture[1].loadFromFile("Resources/SnowBrosAssets/Images/Tornado_Red.png" , {146 , 887 , 116 , 111}) ; 

    
        sf::IntRect knifearea =  {496,  891 , 66 , 27}  ; 
        KnifeTex.loadFromFile("Resources/SnowBrosAssets/Images/Tornado_Red.png" , knifearea) ;  
        Knife->setTexture(KnifeTex) ;
        Knife->setActive(false) ;

        /////////////////////////////////////////////
        ///// Now Setting the Properties of the Enemy
        setPos(x , y) ;
        setVx(200) ;
        setVy(200) ;
        setCopyVx(200) ;
        setCopyVy(200) ;
    }

    void ThrowKnife()
    {
        if(getVx() > 0)
        {
            isRight = true ;
            isLeft = false ;
        }
        else 
        {
            isRight  = false ;
            isLeft = true ;
        }
        Knife->fire(EnemySprite.getPosition(), isRight) ; 
        Knife->setActive(true) ; 
        knifeTimer.restart() ;
    }

    /// IF I CHANGE ANIMATION THIS WAY I ONLY NEED ONE VALUE TO STORE THE STORE OR ACTUALLY NONE AT ALL JUST A SIMPLESPIRITSHEET
    void ChangeToThrowKnifeAnimation()
    {
        currentIndexOfKnifethrowingAnimation = (currentIndexOfKnifethrowingAnimation + 1) % TotalAnimationofKnifeThrowingTexture  ; 
        sf::IntRect area ;
        EnemySprite.setTexture(EnemyKnifeThrowingTexture[currentIndexOfKnifethrowingAnimation])  ;
        if(getVx() > 0) // Enemy Pos Condition actually here 
        {
            EnemySprite.setScale(-0.3 , 0.3) ; 
            isRight = true ; 
            isLeft = false ;
        }
        else
        {
            EnemySprite.setScale(0.3 , 0.3) ; 
            isLeft = true ;
            isRight =  false ;
        }
    }


    virtual int getScore()
    {
        return 300 + rand() % 901;
    }

     virtual void update(const float dt , Block *B , const int BLOCKSIZE) override
    {
        // //////
        // // PHASE 0 
        // ////////////////////////////////////////////////////////////////////
        // /////// ALL RELATED TO KNIFE THROW DONE  BY MEEEE
        if(TimerForThrowKnifeOrNot.getElapsedTime().asSeconds() >= TotalTimeForThrowKnife) 
        {
            isKnifeFired = false ;
            isThrowingTheKnife = true ;
            TimerForThrowKnifeOrNot.restart() ; // Reset the time back so i can start the timer for next knife throw 
            TimeToThrowKnife.restart();  // Reset to Initial time so i can throw the knife 
            
        }
        if(Knife->isActive() && isKnifeFired)
        {
            Knife->update(dt) ;
        }
        if (isThrowingTheKnife && 
        TimeToThrowKnife.getElapsedTime().asSeconds() <= TimeTakenToThrowKnife &&
        !isJumping && !isFallingDown && !isInAeialMode && !isOnRestMode)
        {
            setVx(0);
            setVy(0);
            if(!isKnifeFired)
            {
                ThrowKnife() ; 
                isKnifeFired = true ;
            }

            if (animationClock.getElapsedTime().asSeconds() >= 0.5f)
            {
                animationClock.restart();
                ChangeToThrowKnifeAnimation();
            }
            EnemySprite.setPosition(x, y);
            return; // skip all other phases
        }
        else if (isThrowingTheKnife)  // THIS CONDITION EXECUTES ONLY WHEN THE ABOVE CONDITION TIMER IS FALSE AND THIS CONDITION IS NECESSARY SO  WE DON'T UPDATE EVEN IF THE ENEMY DID'NT Throw the KNIFE
        {
            isKnifeFired = false ;
            Knife->setActive(false) ;
            isThrowingTheKnife = false;
            setVx(isLeft ? -abs(CopyVx) : abs(CopyVx)); // preserve facing direction
            setVy(CopyVy);
            animationClock.restart(); // flush throw animation so walk resumes cleanly
        }   

        
       
            ////////////////////////////////////
            ///////////////////////////////////

        ///////////////////////////////////////////////////////////
        /////// PHASE 1 — REST MODE
        /////// Enemy is stationary. Gravity and platforms are skipped
        /////// entirely so nothing can push or pull it while resting.
        if(isOnRestMode && !isFallingDown)
        {
            // Hold position — no movement whatsoever
            setVx(0) ;
            setVy(0) ;
            EnemySprite.setPosition(x , y) ;

            // After rest duration expires → switch to aerial mode
            if(CurrentTimeofIsOnRestMode.getElapsedTime().asSeconds() >= isOnRestModeTime)
            {
                isFlying = true;
                isOnRestMode    = false ;
                ChangedToRestMode = false ;
                isInAeialMode   = true ;
                // Restore horizontal speed and launch upward to start aerial phase
                setVx(CopyVx) ;
                setVy(-CopyVy) ;
                CurrentAreialTime.restart() ;
            }

            // Animation
            if(animationClock.getElapsedTime().asSeconds() >= animationSpeed)
            {
                UpdateToRestMovementAnimation() ;
                animationClock.restart() ;
            }

            /*checkforShowHitBoxDetection(mywindow , B , BLOCKSIZE) ;*/
            return ; // Skip the rest of update — rest is its own complete state
        }

        ///////////////////////////////////////////////////////////
        /////// PHASE 2 — AERIAL MODE
        /////// Enemy flies freely. Gravity and platform checks are
        /////// skipped so it moves through the air unaffected.
        /////// Screen boundaries still apply so it can't leave the window.
        if(isInAeialMode)
        {
            UpdateX(dt) ;
            UpdateY(dt) ;
            EnemySprite.setPosition(x , y) ;

            UpdateDirection_X() ;
            if(getVx() > 0) { isRight = true  ; isLeft = false ; }
            else             { isLeft  = true  ; isRight = false ; }

            // Screen boundaries bounce the enemy so it stays visible
            CheckCollionsWithScreenX(600 , 600) ;
            // For aerial Y: bounce off top/bottom instead of stopping
            if(y + EnemySprite.getGlobalBounds().height > 600)
            {
                y = 600 - EnemySprite.getGlobalBounds().height ;
                setVy(-abs(getVy())) ; // bounce up
            }
            else if(y < 0)
            {
                y = 0 ;
                setVy(abs(getVy())) ; // bounce down
            }
            EnemySprite.setPosition(x , y) ;

            // After aerial duration expires → fall back to normal mode
            if(CurrentAreialTime.getElapsedTime().asSeconds() >= Areialtime && CheckIfItIsOnLand(B , BLOCKSIZE))
            {
                isFlying = false;
                isInAeialMode = false ;
                isFallingDown = true  ;
                setVy(gravityfactor)  ;
            }

            // Animation
            if(animationClock.getElapsedTime().asSeconds() >= animationSpeed)
            {
                UpdateToFlyingAnimation() ;
                animationClock.restart() ;
            }
            
            /*checkforShowHitBoxDetection(mywindow , B , BLOCKSIZE) ;*/
            return ; // Skip the rest of update — aerial is its own complete state
        }

        ///////////////////////////////////////////////////////////
        /////// PHASE 3 — NORMAL MODE (walking / jumping on platforms)
        /////// Identical to Botom logic, plus a check at the end
        /////// to decide whether to enter rest mode.
        

        UpdateX(dt) ;
        UpdateY(dt) ;
        EnemySprite.setPosition(x , y) ;

        
        UpdateDirection_X() ;
        if(getVx() > 0) { isRight = true  ; isLeft = false ; }
        else             { isLeft  = true  ; isRight = false ; }

        CheckCollionsWithScreenX(600, 600) ;
        CheckCollionsWithScreenY(600, 600) ;

        if(!isJumping)
        {
            bool onLand = CheckCollosionsWithPlatforms(B , BLOCKSIZE) ;
            if(!onLand)
            {
                isFallingDown = true ;
                setVy(gravityfactor) ;
            }
            else
            {
                isFallingDown = false ;
                setVy(0) ;
            }
        }

        EnemyWantsToJumporNot() ;

        if(isJumping && float(JumpInterval.getElapsedTime().asSeconds()) < 0.3f)
        {
            const int JumpFactorToSpeed = 1000 ;
            setVy(-getVy() - JumpFactorToSpeed) ;
        }
        else
        {
            isJumping = false ;
            setVy(gravityfactor) ;
        }
        
        ///////////////////////////////////////////////////////////
        /////// Check whether to enter rest mode only while
        /////// in normal mode. ChangeToRestModeOrNot() now only
        /////// restarts its clock after the threshold fires, so
        /////// this check will actually trigger every ~10 seconds.
        if(ChangeToRestModeOrNot())
        {
            isOnRestMode = true ;
            ChangedToRestMode = true ;
            CurrentTimeofIsOnRestMode.restart() ;
        }

        ///////////////////////////////////////////////////////////
        /////// Simple animation change like botom
        if(animationClock.getElapsedTime().asSeconds() >= animationSpeed)
        {
            if(isLeft)          
                UpdateToLeftMovementAnimation() ;
            else if(isRight)    
                UpdateToRightMovementAnimation() ;
            else if(isJumping)  
                UpdateToJumpMovementAnimation() ;
            else if(isFallingDown) 
                UpdateToFallingMovementAnimation() ;

            animationClock.restart() ;
        }
    }
    virtual void draw(sf::RenderWindow &mywindow, bool debug) override
    {
        mywindow.draw(Enemy::getEnemySprite()) ; 
        Knife->draw(mywindow , debug) ; 

        if (debug)
            EnemySprite.drawHitbox(mywindow, Color::Red);

    }
};
//#endif

// Everything it inherits from botom my work would be to just throw 
class Minions : public Botom
{
protected:
    bool isInAir;
    bool isOnLand;
    bool hasStoodUp; // New flag to track if the stand-up animation is finished

    sf::Clock inAirTime;
    float totalInAirTime;

    AnimationComponent* standUpAnim;
    AnimationComponent* moveAnim;
    sf::Texture MinionSpriteSheet;

    sf::IntRect standUpFrames[3];
    int totalStandUpFrames;
    
    sf::IntRect moveFrames[3];
    int totalMoveFrames;

public:
    Minions() : Botom()
    {
        totalInAirTime      = 5.0f;
        standUpAnim         = nullptr;
        moveAnim            = nullptr;
        totalStandUpFrames  = 3;
        totalMoveFrames     = 3;
        isBoss              = false;
        hasStoodUp          = false; // Initialize to false
    }

    ~Minions()
    {
        if (standUpAnim != nullptr)
        {
            delete standUpAnim;
            standUpAnim = nullptr;
        }
        if (moveAnim != nullptr)
        {
            delete moveAnim;
            moveAnim = nullptr;
        }
    }
bool CheckVerticalOnlyCollision(Block* B, const int BLOCKSIZE)
    {
    bool onLand = false;
    float floorY = 560.0f;

    for (int i = 0; i < BLOCKSIZE; i++)
    {
        sf::FloatRect enemyBox = EnemySprite.getGlobalHitbox();
        sf::FloatRect blockBox = B[i].getHitbox();
        sf::FloatRect overlap;

        if (enemyBox.intersects(blockBox, overlap))
        {
            // Only resolve if it's clearly a vertical collision
            if (overlap.width > overlap.height)
            {
                float enemyCenterY = enemyBox.top + enemyBox.height / 2.0f;
                float blockCenterY = blockBox.top + blockBox.height / 2.0f;

                if (enemyCenterY < blockCenterY) // Minion is above block
                {
                    y = blockBox.top - enemyBox.height / 2.0f;
                    setVy(0);
                    onLand = true;
                }
            }
            // ← Horizontal overlaps are intentionally IGNORED
            //   so minion walks off edges instead of getting pushed back
        }
        EnemySprite.setPosition(x, y);
    }

    // Hard floor
    float halfH = EnemySprite.getGlobalBounds().height / 2.0f;
    if (y + halfH >= floorY)
    {
        y = floorY - halfH;
        setVy(0);
        onLand = true;
        EnemySprite.setPosition(x, y);
    }

    return onLand;
}

    virtual void CreateEnemy(float x, float y) override
    {
        // 1. Texture Fix: Load directly into the class member
        if (!MinionSpriteSheet.loadFromFile("Resources/SnowBrosAssets/Images/Mogera.png"))
        {
            std::cout << "Error loading Minion spritesheet\n";
            exit(0);

        }
        sf::IntRect defaultArea(1796, 806, 167 , 161);
        EnemySprite.setTexture(MinionSpriteSheet) ;
        EnemySprite.setTextureRect(defaultArea) ;
        EnemySprite.setScale(0.2 , 0.2) ;
        EnemySprite.setHitbox(EnemySprite.getLocalBounds()) ; 


        // Stand up frames
        standUpFrames[0] = sf::IntRect(1986, 984, 141, 162);
        standUpFrames[1] = sf::IntRect(1791, 979, 141, 162);
        standUpFrames[2] = sf::IntRect(2318, 811, 147, 162);

        standUpAnim = new AnimationComponent;
        standUpAnim->loadSprite(standUpFrames, totalStandUpFrames, 0.12f); 

        // Move frames
        moveFrames[0] = sf::IntRect(1799, 810, 161, 162);
        moveFrames[1] = sf::IntRect(1973, 806, 161, 162);
        moveFrames[2] = sf::IntRect(2145, 765, 161, 177);

        moveAnim = new AnimationComponent;
        moveAnim->loadSprite(moveFrames, totalMoveFrames, 0.15f); 

        // Physics Setup
        sethealth(1);
        healthOriginal = 1;
        setPos(x, y);
        setVx(-200.0f); // Thrown to the left initially
        setVy(200.0f);
        originalSpeed = -200.0f;
        setCopyVx(-200.0f);
        setCopyVy(200.0f);

        // State Flags
        isFlying = true; 
        isInAir = true;
        isOnLand = false;
        hasStoodUp = false;
        inAirTime.restart();
    }

    virtual void update(const float dt, Block* B, const int BLOCKSIZE) override
    {
        if (isInAir)
        {
            // Apply gravity (standardized for smoother arcs)
            setVy(getVy() + 980.0f * dt); 
            UpdateY(dt);
            UpdateX(dt); // Keeps moving horizontally while being thrown

            EnemySprite.setPosition(x, y); 

            // Check if it hit the ground
            if (CheckVerticalOnlyCollision(B, BLOCKSIZE))
            {
                isInAir  = false;
                isFlying = false;
                isOnLand = true;    
                setVx(0); // Stop moving forward while doing the stand-up animation
                setVy(0);
            }
        }
        else if (isOnLand)
        {
            if (!hasStoodUp)
            {
                // Phase 1: Standing up (Not moving X)
                EnemySprite.setTextureRect(standUpAnim->getCurrentFrame());
                standUpAnim->update(dt); 
                
                // If it reaches the final frame of the stand up animation, lock it and start moving
                if (standUpAnim->getCurrentFrameIndex() == totalStandUpFrames - 1)
                {
                    hasStoodUp = true;
                    setVx(-200.0f); // Start moving left only
                }
            }
            else 
            {
                // Phase 2: Moving in one direction
                UpdateX(dt); // Actually apply the X velocity so the sprite moves
                
                EnemySprite.setTextureRect(moveAnim->getCurrentFrame());
                moveAnim->update(dt);
                
                // Optional: Ensure it doesn't fall through the floor if it walks off a ledge
                if (!CheckVerticalOnlyCollision(B, BLOCKSIZE)) 
                {
                    setVy(getVy() + 980.0f * dt); // Re-apply gravity if falling
                    UpdateY(dt);
                }
            }
            
            EnemySprite.setPosition(x, y); 
        }
    }

    virtual void draw(sf::RenderWindow& mywindow, bool debug) override
    {
        mywindow.draw(EnemySprite);

        if (debug)
            EnemySprite.drawHitbox(mywindow, sf::Color::Yellow);
    }

    virtual int getScore() override
    {
        return 50 + rand() % 51; 
    }
};


class Mogera :  public  Botom
{
private: 

    float xFactorShiftForSpriteToAlignWithEachOther ;
    float Enemyheight ;

    int totalMinionsSpawn ;

    sf::Texture SpriteSheetofBoss ;
    AnimationComponent *smallJumpAnimation ;
    AnimationComponent *bigJumpAnimation ;
    AnimationComponent *roarAnimation ;
    AnimationComponent *deathAnimation ;
    HitboxSprite EnemyLegsSprite ; 


    sf::Clock animationTimeofSmallJump ;
    sf::Clock animationTimeofBigJump ; 
    sf::Clock animationTimeofRoar ;
    sf::Clock animationTimeofDeath ;

    sf::Clock CheckCollosionWithPlatformsOrNot ;
    int TotalTimeofCheckingCollosionWithPaltformsOrNot ;

    float totalTimeofSmallJumpAnimation ;
    float totalTimeofBigJumpAnimation ;
    float totalTimeofRoarAnimation ;
    float totalTimeofDeathAnimation ;

    sf::Clock timeToJumpTimer ;
    float totalTimeOfWeatherBossWantsToJumpOrNot ;


    sf::Clock STOPCHECKINGCOLLOSIONTIMER ;
    float TOTALTIMEAFTERWHICHTOSTOPCHECKINGTHECOLLOSION ; 
    
    sf::SoundBuffer roarBuffer ; 
    sf::Sound roarSound;


    sf::Clock  minionsSpawnTimer ; 
    int totalTimeAfterWhichToSpawnTheMinions ;
    Minions  *minions ;

    // It it just the size of array where all the created minions are stored
    const int totalCountOfMinionsBossCanSpawnAtaTime =  3 ; 


    int smallJumpCount;
    bool isSmallJump  ;
    bool isLongJump  ;

    bool isOnLand ; 
    bool isFalling ;
    bool isJumping ;
    bool isRoaring ;
    bool isDying ; // Lol


public : 

    Mogera() : Botom()
    {
        Enemyheight = 0 ;
        xFactorShiftForSpriteToAlignWithEachOther  = 0; 

        health = 10 ;
        totalMinionsSpawn = 0 ;
        smallJumpAnimation = nullptr;
        bigJumpAnimation = nullptr ;
        roarAnimation = nullptr ;
        deathAnimation = nullptr ;

        animationTimeofBigJump.restart(); 
        animationTimeofSmallJump.restart() ;
        animationTimeofRoar.restart() ;
        animationTimeofDeath.restart() ;
        timeToJumpTimer.restart() ;
        CheckCollosionWithPlatformsOrNot.restart() ;
        STOPCHECKINGCOLLOSIONTIMER.restart() ; 
        minionsSpawnTimer.restart()  ;

        totalTimeOfWeatherBossWantsToJumpOrNot = 2.0f ;
        TotalTimeofCheckingCollosionWithPaltformsOrNot = 5 ; 

        totalTimeofSmallJumpAnimation  = 5 ;
        totalTimeofBigJumpAnimation = 3 ;
        totalTimeofRoarAnimation = 3 ;
        totalTimeofDeathAnimation = 5 ;
        TOTALTIMEAFTERWHICHTOSTOPCHECKINGTHECOLLOSION = 5 ;
        totalTimeAfterWhichToSpawnTheMinions = 5 ; 

        


        isBoss = true;
        isOnLand = false ; 
        isFalling  = false ;
        isJumping = false;
        isRoaring = false ; 
        isDying = false ;

        isSmallJump = false ;
        isLongJump = false ; 
        smallJumpCount  =  0 ;
    }
    ~Mogera()
    {
        if(bigJumpAnimation != nullptr)
        {
            delete  bigJumpAnimation ; 
        }
        if(roarAnimation != nullptr)
        {
            delete  roarAnimation ;
        }
        if(deathAnimation != nullptr)
        {
            delete[] deathAnimation ;
        }
        if(minions  != nullptr)
        {
            delete [] minions ;
        }
    }
    /////////////////////////////////
    /////////////////////////////////
    ////////////////////////////////
    /// Required Functions by the boss

    void CheckWeatherBossWantsToJumpOrNot()
    {
        if(animationTimeofBigJump.getElapsedTime().asSeconds() >= totalTimeofBigJumpAnimation)
        {
            isLongJump = true ; 
        } 
    }

    void UpdateY(const float dt)
    {
        y += Vy * dt ;
    }
    bool CheckCollosionWithScreenYUP(const float width, const float height)
    {

        bool flag = false;
        if (y < 60)
        {
            y = 60;
            isJumping  = false; // ← cancel jump so update loop falls into gravity
            isLongJump  = false;
            isSmallJump = false;
            isFalling  = true;
            setVy(abs(CopyVy)); // ← fall down immediately
            flag = true;
            EnemySprite.setPosition(x, y);
            EnemyLegsSprite.setPosition(x - xFactorShiftForSpriteToAlignWithEachOther, y + Enemyheight);
        }
        return flag ; 
    }
    bool CheckCollionsWithScreenYDOWN(const float width, const float height)
    {
        bool flag = false;
        if (y + Enemyheight + EnemyLegsSprite.getGlobalBounds().height > height)
        {
            y = height - Enemyheight - EnemyLegsSprite.getGlobalBounds().height;
            setVy(0);
            flag = true;
        }

        EnemySprite.setPosition(x, y);
        EnemyLegsSprite.setPosition(x - xFactorShiftForSpriteToAlignWithEachOther, y + Enemyheight);
        return flag;
    }

    bool CheckCollosionsWithPlatforms(Block* b, const int SIZE)
    {
        bool OnLand = false;
        float floorY = 560.0f;
    
        float totalHeight = Enemyheight + EnemyLegsSprite.getGlobalBounds().height;

        for (int st = 0; st < SIZE; st++)
        {
            sf::FloatRect legBox = EnemyLegsSprite.getGlobalHitbox() ;
            sf::FloatRect blockBox = b[st].getHitbox();
            sf::FloatRect overlap;

            if (legBox.intersects(blockBox, overlap))
            {
                if (overlap.width < overlap.height)
                {
                    if (legBox.left < blockBox.left)
                    {
                        x -= overlap.width; 
                        setVx(-abs(CopyVx));
                    }
                    else
                    {
                        x += overlap.width; 
                        setVx(abs(CopyVx));
                    }
                }
                else
                {
                    if (legBox.top < blockBox.top) 
                    {
                        y = blockBox.top - totalHeight ;
                        setVy(0);
                        OnLand = true;
                    }
                    else
                    {
                        y += overlap.height; // Push down
                        setVy(abs(CopyVy));
                        isJumping = false ; 
                        isFalling = true ;
                    }
                }

                EnemySprite.setPosition(x, y);
                EnemyLegsSprite.setPosition(x - xFactorShiftForSpriteToAlignWithEachOther, y + Enemyheight); 
            }
        }

        // Main floor bounds check
        if (y + totalHeight >= floorY)
        {
            y = floorY - totalHeight;
            setVy(0);
            OnLand = true;
        }

        EnemySprite.setPosition(x, y);
        EnemyLegsSprite.setPosition(x - xFactorShiftForSpriteToAlignWithEachOther, y + Enemyheight) ; 

        return OnLand;
    }





    /////////////////////////////////
    /////////////////////////////////
    /////////////////////////////////

    virtual void CreateEnemy(float x , float y)  ;
    virtual void update(sf::RenderWindow &mywindow , float dt, Block* B, const int BLOCKSIZE)  ;
    virtual void draw(sf::RenderWindow &mywindow, bool debug) ;
    virtual int getScore()
    {
        return 5000;
    }

};



//////////////////////////////////////////////



class Gamakichi : public  Botom
{
private:

    float xFactorShiftForSpriteToAlignWithEachOther;
    float Enemyheight;

    int totalMinionsSpawn;

    sf::Texture SpriteSheetofBoss;
    AnimationComponent* bigJumpAnimation;
    AnimationComponent* roarAnimation;
    AnimationComponent* deathAnimation;
    HitboxSprite EnemyLegsSprite;


    sf::Clock animationTimeofBigJump;
    sf::Clock animationTimeofRoar;
    sf::Clock animationTimeofDeath;

    sf::Clock CheckCollosionWithPlatformsOrNot;
    int TotalTimeofCheckingCollosionWithPaltformsOrNot;

    float totalTimeofSmallJumpAnimation;
    float totalTimeofBigJumpAnimation;
    float totalTimeofRoarAnimation;
    float totalTimeofDeathAnimation;


    sf::Clock timeToJumpTimer;

    

    float totalTimeOfWeatherBossWantsToJumpOrNot;

    int smallJumpCount;
    bool isSmallJump;
    bool isLongJump;

    bool isOnLand;
    bool isFalling;
    bool isJumping;
    bool isRoaring;
    bool isDying; // Lol


public:

    Gamakichi() : Botom()
    {
        Enemyheight = 0;
        xFactorShiftForSpriteToAlignWithEachOther = 0;

        health = 10;
        totalMinionsSpawn = 0;
        bigJumpAnimation = nullptr;
        roarAnimation = nullptr;
        deathAnimation = nullptr;

        animationTimeofBigJump.restart();
        animationTimeofRoar.restart();
        animationTimeofDeath.restart();
        timeToJumpTimer.restart();
        CheckCollosionWithPlatformsOrNot.restart();

        totalTimeOfWeatherBossWantsToJumpOrNot = 2.0f;
        TotalTimeofCheckingCollosionWithPaltformsOrNot = 5;

        totalTimeofSmallJumpAnimation = 5;
        totalTimeofBigJumpAnimation = 2;
        totalTimeofRoarAnimation = 3;
        totalTimeofDeathAnimation = 5;


        isBoss = true;
        isOnLand = false;
        isFalling = false;
        isJumping = false;
        isRoaring = false;
        isDying = false;

        isSmallJump = false;
        isLongJump = false;
        smallJumpCount = 0;
    }
    ~Gamakichi()
    {
        if (bigJumpAnimation != nullptr)
        {
            delete[] bigJumpAnimation;
        }
        if (roarAnimation != nullptr)
        {
            delete[] roarAnimation;
        }
        if (deathAnimation != nullptr)
        {
            delete[] deathAnimation;
        }
    }
    /////////////////////////////////
    /////////////////////////////////
    ////////////////////////////////
    /// Required Functions by the boss

    void CheckWeatherBossWantsToJumpOrNot()
    {
        
    }

    void UpdateY(const float dt)
    {
        y += Vy * dt;
    }
    bool CheckCollionsWithScreenY(const float width, const float height)
    {
        bool flag = false;

        // // Ceiling hit — stop jump, start falling, don't lock velocity
        // if (y < 60)
        // {
        //     y = 60;
        //     isJumping  = false; // ← cancel jump so update loop falls into gravity
        //     isLongJump  = false;
        //     isSmallJump = false;
        //     isFalling  = true;
        //     setVy(abs(CopyVy)); // ← fall down immediately
        //     flag = true;
        //     EnemySprite.setPosition(x, y);
        //     EnemyLegsSprite.setPosition(x - xFactorShiftForSpriteToAlignWithEachOther, y + Enemyheight);
        //     return flag;
        // }

        if (y + Enemyheight + EnemyLegsSprite.getGlobalBounds().height > height)
        {
            y = height - Enemyheight - EnemyLegsSprite.getGlobalBounds().height;
            setVy(0);
            flag = true;
        }

        EnemySprite.setPosition(x, y);
        EnemyLegsSprite.setPosition(x - xFactorShiftForSpriteToAlignWithEachOther, y + Enemyheight);
        return flag;
    }

    bool CheckCollosionsWithPlatforms(Block* b, const int SIZE)
    {
        bool OnLand = false;
        float floorY = 560.0f;

        float totalHeight = Enemyheight + EnemyLegsSprite.getGlobalBounds().height;

        for (int st = 0; st < SIZE; st++)
        {
            sf::FloatRect legBox = EnemyLegsSprite.getGlobalHitbox();
            sf::FloatRect blockBox = b[st].getHitbox();
            sf::FloatRect overlap;

            if (legBox.intersects(blockBox, overlap))
            {
                if (overlap.width < overlap.height)
                {
                    if (legBox.left < blockBox.left)
                    {
                        x -= overlap.width;
                        setVx(-abs(CopyVx));
                    }
                    else
                    {
                        x += overlap.width;
                        setVx(abs(CopyVx));
                    }
                }
                else
                {
                    if (legBox.top < blockBox.top)
                    {
                        y = blockBox.top - totalHeight;
                        setVy(0);
                        OnLand = true;
                    }
                    else
                    {
                        y += overlap.height; // Push down
                        setVy(0);
                        isJumping = false;
                        isFalling = true;
                    }
                }

                EnemySprite.setPosition(x, y);
                EnemyLegsSprite.setPosition(x - xFactorShiftForSpriteToAlignWithEachOther, y + Enemyheight);
            }
        }

        // Main floor bounds check
        if (y + totalHeight >= floorY)
        {
            y = floorY - totalHeight;
            setVy(0);
            OnLand = true;
        }

        EnemySprite.setPosition(x, y);
        EnemyLegsSprite.setPosition(x - xFactorShiftForSpriteToAlignWithEachOther, y + Enemyheight);

        return OnLand;
    }





    /////////////////////////////////
    /////////////////////////////////
    /////////////////////////////////

    virtual void CreateEnemy(float x, float y);
    virtual void update(sf::RenderWindow& mywindow, float dt, Block* B, const int BLOCKSIZE);
    virtual void draw(sf::RenderWindow& mywindow, bool debug) ;
    virtual int getScore()
    {
        return 10000;
    }

};

