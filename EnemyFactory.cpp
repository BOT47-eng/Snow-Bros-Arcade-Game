#include "EnemyFactory.hpp"

void Enemy::sethealth(int h){health = h ; }
void Enemy::setPos(float x  , float y)
{
this->x  = x ;
this->y =  y ;
}
void Enemy::setPos(sf::Vector2f v)
{
   x = v.x; 
   y = v.y ;
}
void Enemy::setVx(float d) 
{
    Vx = d ; 
}
void Enemy::setVy(float d) 
{
    Vy = d ;
} 
void Enemy::setCopyVx(float d)
{
    CopyVx = d ; 
}

void Enemy::setCopyVy(float d)
{
    CopyVy = d ; 
}
void Enemy::setEnemyTexture(const sf::Texture& T) 
{
    EnemySpriteTexture = T ;
}

void Enemy::setEnemyHitBoxSprite() // Just Call it To change the current Set Texture
{
    EnemySpriteTexture.setSmooth(true) ;
    EnemySpriteTexture.setRepeated(true) ; 
    EnemySprite.setTexture(EnemySpriteTexture, true); // true = reset texture rect to full texture
    
    sf::Vector2u texSize = EnemySpriteTexture.getSize();
    EnemySprite.setTextureRect(sf::IntRect(0, 0, texSize.x, texSize.y));
    
    sf::FloatRect bounds = EnemySprite.getLocalBounds();
    EnemySprite.setHitbox(bounds);
    EnemySprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
}

void Enemy::applySnow(float amount, int playerID)
{
    if (!isFullyCoated)
    {
        snowAccumulated += amount;
        if (snowAccumulated >= health)
        {
            snowAccumulated = health;
            isFullyCoated = true;
            snowballCreatorPlayer = playerID;
            if (!isBoss)
            {
                convertToSnowball();
            }
            else
            {
                Vx = 0;
                Vy = 0;
                shakeTimer.restart();
            }
        }
    }
}

void Enemy::updateCoatedState()
{
    if (isSnowball)
    {
        updateSnowballState(0);
        return;
    }

    if (isFullyCoated)
    {
        if (shakeTimer.getElapsedTime().asSeconds() >= 5)
        {
            shakeOffSnow();
        }
    }
    else if (snowAccumulated > 0)
    {
        float slowFactor = 1.0f - (snowAccumulated / health);
        float currentSpeed = originalSpeed * slowFactor;

        if (Vx > 0)
        {
            Vx = currentSpeed;
        }
        else if (Vx < 0)
        {
            Vx = -currentSpeed;
        }
    }
}

void Enemy::shakeOffSnow()
{
    snowAccumulated = 0;
    isFullyCoated = false;
    if (originalSpeed > 0)
        Vx = originalSpeed;
    else
        Vx = -originalSpeed;
}

void Enemy::convertToSnowball()
{
    isSnowball = true;
    snowballStaticTimer = 0;
    snowballKillCount = 0;
    snowballVelocityX = 0;
    snowballVelocityY = 0;
    snowballOnGround = false;
    Vx = 0;
    Vy = 0;

    animSnowballRoll.loadSprite(frames, 4, 0.1f, true);
    animSnowballBreakout.loadSprite(breakoutFrames, 4, 0.1f, false);
    currentSnowballAnim = &animSnowballRoll;

    EnemySprite.setTexture(snowballTexture, true);

    float targetSize = 75.0f;
    float scaleX = targetSize / 230.0f;
    float scaleY = targetSize / 278.0f;
    EnemySprite.setScale(scaleX, scaleY);

    FloatRect hitbox;
    hitbox.width = 230;
    hitbox.height = 278;
    EnemySprite.setOrigin(Vector2f(hitbox.width / 2.0, hitbox.height / 2.0));
    EnemySprite.setHitbox(hitbox);
    EnemySprite.setTextureRect(animSnowballRoll.getCurrentFrame());
}

void Enemy::updateSnowballState(float dt)
{
    if (!isSnowball)
        return;

    if (isSnowballBreakingOut)
    {
        currentSnowballAnim->update(dt);
        EnemySprite.setTextureRect(currentSnowballAnim->getCurrentFrame());

        if (currentSnowballAnim->isFinished())
        {
            breakOutOfSnowball();
        }
        return;
    }

    snowballStaticTimer += dt;
    if (snowballStaticTimer >= 5.0f)
    {
        isSnowballBreakingOut = true;
        currentSnowballAnim = &animSnowballBreakout;
        currentSnowballAnim->reset();
        return;
    }

    if (snowballVelocityX != 0)
    {
        x += snowballVelocityX * dt;
    }

    snowballVelocityY += 980.0f * dt;
    if (snowballVelocityY > 800.0f)
        snowballVelocityY = 800.0f;

    y += snowballVelocityY * dt;
    EnemySprite.setPosition(x, y);

    animSnowballRoll.update(dt);
    EnemySprite.setTextureRect(animSnowballRoll.getCurrentFrame());
}


void Enemy::breakOutOfSnowball()
{
    isSnowball = false;
    isSnowballBreakingOut = false;
    snowAccumulated = 0;
    isFullyCoated = false;
    snowballStaticTimer = 0;
    snowballVelocityX = 0;
    snowballVelocityY = 0;
  
    setEnemyHitBoxSprite();

    if (snowballPushDirection != 0)
        sethealth(-1);
    else
    {
        sethealth(healthOriginal);
        if ((rand() % 2) % 2)
            Vx = originalSpeed;
        else
            Vx = -originalSpeed;
    }

    snowballPushDirection = 0;

    animSnowballRoll.reset();
    animSnowballBreakout.reset();
}

void Mogera::CreateEnemy(float x, float y, int index)
{
    ////////////////////////////////////////
    // Loading and setting all the textures

    if (!SpriteSheetofBoss.loadFromFile("Resources/SnowBrosAssets/Images/Mogera.png"))
    {
        std::cout << "Error in loading the SpriteSheet of MoeMoe Boss lol\n";
        exit(0);
    }
     if (!roarBuffer.loadFromFile("Resources/SnowBrosAssets/Sounds/MogeraRoar.mp3")) 
    {
        std::cout << "Error loading Roar.mp3" << std::endl;
        exit(0) ; 
    } 
    roarSound.setBuffer(roarBuffer);




    /////////////////////
    // For Test 
    IntRect area(44, 9, 539, 460);
    EnemySprite.setScale({ 0.25 ,  0.25 });
    EnemySprite.setTextureRect(area);
    EnemySprite.setTexture(SpriteSheetofBoss);
    EnemySprite.setPosition(x, y);
    EnemySprite.setHitbox(FloatRect(area));

    ///////////////////////
    // setting Up the legs
    const int framesOfLegs = 3;
    sf::IntRect  areaOfLegs[3] = {
                    {1924 , 3 , 539 , 107},
                    {1924 , 207 ,539 , 233},
                    {1924  , 443 , 539 , 329}
    };
    bigJumpAnimation = new AnimationComponent;
    bigJumpAnimation->loadSprite(areaOfLegs, framesOfLegs, 0.75);

    sf::IntRect areaofTop[3] = {{44, 9, 539, 460} , 
                                {588, 9, 539, 460} ,
                                {1165, 9, 539, 460}} ; 

    roarAnimation = new AnimationComponent ; 
    roarAnimation->loadSprite(areaofTop , 3  , 0.55) ; 


    EnemyLegsSprite.setScale({ 0.25 , 0.25 });
    EnemyLegsSprite.setTexture(SpriteSheetofBoss);
    EnemyLegsSprite.setTextureRect(areaOfLegs[0]);
    sf::FloatRect legBounds = EnemyLegsSprite.getLocalBounds();

    float shrinkX = 100.0f;
    float shrinkY = 0.f;

    legBounds.left += shrinkX;
    legBounds.top += shrinkY;
    legBounds.width -= shrinkX * 2;
    legBounds.height -= shrinkY * 2;

    EnemyLegsSprite.setHitbox(legBounds);
    EnemyLegsSprite.setHitbox(legBounds);

    xFactorShiftForSpriteToAlignWithEachOther = 10;
    Enemyheight = EnemySprite.getGlobalBounds().height - 8;
    EnemyLegsSprite.setPosition(x - xFactorShiftForSpriteToAlignWithEachOther, y + Enemyheight);

    minions = new Minions[totalCountOfMinionsBossCanSpawnAtaTime]; 
    totalMinionsSpawn = 0;
    
    // Set the first random spawn time (e.g., between 2 and 5 seconds)
    totalTimeAfterWhichToSpawnTheMinions = 2 + (rand() % 4); 
    minionsSpawnTimer.restart();

    setPos(x, y);
    setVx(0);
    setVy(400);
    setCopyVx(0);
    setCopyVy(400);
}

void Mogera::update(const float dt, Block* B, const int BLOCKSIZE)
{
    if (snowAccumulated >= health)
    {
        sethealth(-1);
        if (minions != nullptr)
        {
            delete[] minions;
            minions = nullptr;
            totalMinionsSpawn = 0;
        }
    }

    //Adding the Minions Spawn feature here Damn it aaaaa
    if(health > 0 && minionsSpawnTimer.getElapsedTime().asSeconds() >= totalTimeAfterWhichToSpawnTheMinions)
    {
        if (totalMinionsSpawn < totalCountOfMinionsBossCanSpawnAtaTime)
        {
            minions[totalMinionsSpawn].CreateEnemy(x + 30, y, 0); // pos change factor  a little bit 
            totalMinionsSpawn++;
        }

        totalTimeAfterWhichToSpawnTheMinions = 3 + (rand() % 4);
        minionsSpawnTimer.restart();
    }

    if (health > 0)
        for (int st = 0; st <= totalMinionsSpawn -  1; st++)
        {
            minions[st].update(dt, B, BLOCKSIZE);
        }
    ///////////

    CheckWeatherBossWantsToJumpOrNot() ;

   if(isLongJump)
   {
    UpdateY(dt) ; 
   }
   else if(isFalling == true)
   {
    UpdateY(dt); 
    if(TOTALTIMEAFTERWHICHTOSTOPCHECKINGTHECOLLOSION >= STOPCHECKINGCOLLOSIONTIMER.getElapsedTime().asSeconds())
        {   if(CheckCollosionsWithPlatforms(B , BLOCKSIZE) == true )
            {
                isFalling = false ;
                setVy(-abs(CopyVy)) ;
            }
        }
    else 
    {
        if(STOPCHECKINGCOLLOSIONTIMER.getElapsedTime().asSeconds() >= 10)
        {
            STOPCHECKINGCOLLOSIONTIMER.restart() ; 
        }
    }
    // After Platform it has go up sooo
   }

    ////////////////////
    /// Checking all the collosion here 
    bool TouchestheUpScreen = CheckCollosionWithScreenYUP(600 , 560) ; 
    isOnLand =   CheckCollionsWithScreenYDOWN(600, 560);
    if(isOnLand == true)
    {
        isLongJump = false ; 
        setVy(-abs(CopyVy)) ; 
        animationTimeofBigJump.restart() ; 
    }
    else if(TouchestheUpScreen)
    {
        isFalling = true ; 
        setVy(abs(CopyVy)) ;
        animationTimeofBigJump.restart() ; 
    }

    if(isLongJump == true)
    {
        EnemyLegsSprite.setTextureRect(bigJumpAnimation->getCurrentFrame()) ;
        bigJumpAnimation->update(dt) ;
    }
    else
    {
        EnemyLegsSprite.setTextureRect(bigJumpAnimation->getSepcificFrame(0)) ;
    }


    ////////////
    // Adding the Roar thing 
    if(animationTimeofRoar.getElapsedTime().asSeconds() <= totalTimeofRoarAnimation)
    {
        EnemySprite.setTextureRect(roarAnimation->getCurrentFrame()) ;
        roarAnimation->update(dt) ; 

        if(roarAnimation->getCurrentFrameIndex() == 2)
        {
            roarSound.play()  ;
        }
    }
    if(isOnLand)
    {
        animationTimeofRoar.restart() ; 
    }

    EnemySprite.setPosition({ x, y });
    EnemyLegsSprite.setPosition({ x - xFactorShiftForSpriteToAlignWithEachOther, y + Enemyheight });

    if (snowAccumulated >= health - 1)
    {
        if (minions != nullptr)
        {
            delete[] minions;
            minions = nullptr;
            totalMinionsSpawn = 0;
        }
    }

    if(totalMinionsSpawn >= totalCountOfMinionsBossCanSpawnAtaTime)
    {
        if(minions != nullptr)
        {
            delete [] minions; 
            minions = nullptr ;
            minions = new Minions[totalCountOfMinionsBossCanSpawnAtaTime]  ; 
            totalMinionsSpawn = 0 ; 
        }
    }
}

void Mogera::draw(sf::RenderWindow& mywindow, bool debug)
{
    mywindow.draw(EnemySprite);
    mywindow.draw(EnemyLegsSprite);

    for(int i = 0; i < totalMinionsSpawn; i++)
    {
        minions[i].draw(mywindow, debug);
    }

     if (debug)
    {
        EnemySprite.drawHitbox(mywindow, Color::Red);
        EnemyLegsSprite.drawHitbox(mywindow, Color::Red);
    }


}