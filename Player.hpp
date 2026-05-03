#pragma once
#include <SFML/Graphics.hpp>
#include "Hitbox.hpp"
#include "InputManager.hpp"
#include "AnimationComponent.hpp"
#include "Projectile.hpp"

struct PlayerStats
{
    float walkSpeed = 200.f;
    float jumpHeight = -520.f;
};

//Player 1 is 0 index, Player 2 is 1 index
class Player
{
public:
    static const int MAX_BALLS = 16;
    static const int SCREEN_WIDTH = 600;
private:
    sf::Texture playerTexture;

    void updateInvincibility(float dt);

    Snowball snowballs[MAX_BALLS];
    float cooldown;

    int index;
    int lives;
    int gems;
    int score;

    float velocityX;
    float velocityY;
    float invincibleTimer;
    float snowballTimer;
    float snowballCooldown;
    float speedBoostTimer;
    float balloonTimer;

    bool shopItems[5];
    bool onGround;
    bool facingRight;
    bool wantsShoot;
    bool invincible;
    bool isShooting;
    bool isBalloonMode;
    bool hasSnowballPower;
    bool hasDistanceIncrease;

    const sf::FloatRect playerHitbox = { 0, 0, 60, 72 };
    const sf::IntRect idlePlayerFrames = { sf::IntRect(19, 3, 57, 72) };
    const sf::IntRect walkPlayerFrames[3] = { sf::IntRect(100, 3, 45, 72), sf::IntRect(185 , 3, 52, 73), sf::IntRect(269, 1, 49, 74) };
    const sf::IntRect jumpPlayerFrames[6] = { sf::IntRect(9, 83, 60, 75), sf::IntRect(95, 83, 60, 65), sf::IntRect(180, 83, 60, 65), sf::IntRect(263, 85, 60, 75), sf::IntRect(351, 88, 60, 70), sf::IntRect(433, 86, 68, 68) };
    const sf::IntRect shootPlayerFrames = { sf::IntRect(252, 172, 72, 72) };
    const sf::IntRect balloonFrames[4] = {sf::IntRect(8, 694, 70, 100), sf::IntRect(83, 676, 84, 114), sf::IntRect( 423, 673, 117, 125), sf::IntRect(542, 673, 127, 123)};
    //const sf::IntRect balloonFramesMovement[2] = {sf::IntRect(173, 673, 112, 123), sf::IntRect(293, 674, 120, 125)};
    const sf::IntRect balloonFramesMovement = { sf::IntRect(289, 673, 127, 125) };
    sf::IntRect snowballFrames = { sf::IntRect(514, 1022, 22, 33) };

    HitboxSprite sprite;

    void updateAnimation(float dt);     // tick current anim + apply frame to sprite
    void selectAnimation();

    AnimationComponent animIdle;
    AnimationComponent animWalk;
    AnimationComponent animJump;
    AnimationComponent animShoot;
    AnimationComponent animBalloon;
    AnimationComponent animBalloonMovement;
    AnimationComponent* currentAnim;

    static const float INVINCIBLE_TIME;

public:
    Player();
    Player(int index, PlayerStats stats = PlayerStats());
    void setTexture(const sf::Texture& texture, sf::IntRect rect);
    void setHitboxRect(sf::FloatRect localRect);
    void handleInput(const InputManager& input, float dt);
    void update(float dt);
    void draw(sf::RenderWindow& window, bool debug = false) const;

    void loadSpritesheet(const sf::Texture& texture, const sf::IntRect* idleFrames, int idleCount, const sf::IntRect* walkFrames, int walkCount, const sf::IntRect* jumpFrames, int jumpCount, const sf::IntRect* fallFrames, int fallCount, sf::FloatRect hitboxRect, float frameDuration = 0.1f);

    //These functions are for moving and pushing player out of walls, ceiling and ground
    void applyVelocity(float dt);          
    void landPush(float groundY);              
    void pushOutX(float amount);              
    void pushOutY(float amount);              

    void takeDamage();
    void addScore(int points) 
    { 
        score += points;
    }
    void addGems(int n) 
    { 
        gems += n;
    }
    void addLife() 
    { 
        lives++;
    }

    sf::FloatRect getHitbox() const;
    sf::Vector2f getPosition() const
    { 
        return sprite.getPosition(); 
    }
    float getVelocityX() const 
    { 
        return velocityX; 
    }
    float getVelocityY() const 
    { 
        return velocityY; 
    }
    bool isOnGround() const
    { 
        return onGround; 
    }
    bool isAlive() const 
    { 
        return lives > 0;
    }
    bool isInvincible() const 
    { 
        return invincible;
    }
    bool isFacingRight() const 
    { 
        return facingRight; 
    }
    int getLives() const 
    { 
        return lives; 
    }
    int getGems() const 
    { 
        return gems; 
    }
    int getScore() const 
    { 
        return score;
    }
    int getIndex() const 
    { 
        return index; 
    } 

    //This returns shoot flag and resets it
    bool consumeShoot() 
    { 
        bool temp = wantsShoot; 
        wantsShoot = false; 
        return temp; 
    }

    //For physics engine
    void setPosition(sf::Vector2f pos);
    void setVelocityX(float Vx) 
    { 
        velocityX = Vx; 
    }
    void setVelocityY(float Vy)
    { 
        velocityY = Vy; 
    }
    void setOnGround(bool v) 
    { 
        onGround = v; 
    }
    void setDirectionRight(bool faceRight);
    void setBallonMode(bool v)
    {
        isBalloonMode = v ; 
    }

    //For snowballs
    void setTextureSnowball(const sf::Texture& texture);
    void loadSpritesheetSnowball(const sf::Texture& texture, const sf::IntRect* frames, int count, float duration = 0.05);
    void updateSnowballs(float dt);
    Snowball& getBall(int i)
    {
        return snowballs[i];
    }

    //For power-ups and shop items
    void applyExtraLife();
    void applySnowballPower();
    void applyDistanceIncrease();
    void applySpeedBoost();
    void applyBalloonMode(float time);
    void resetSnowballPower();
    void resetDistanceIncrease();
    void resetSpeedBoost();
    void resetBalloonMode();
    void resetLevelPowerups();
    bool hasSnowballPowerActive() const { return hasSnowballPower; }
    bool hasDistanceIncreaseActive() const { return hasDistanceIncrease; }
    int getShopItem(int index) const
    {
        if (index >= 0 && index <= 4)
            return shopItems[index];
        return 0;
    }
    void setShopItem(int index)
    {
        if (index >= 0 && index <= 4)
        {
            shopItems[index] = true;
        }
    }
    void resetShopItem(int index)
    {
        if (index >= 0 && index <= 4)
        {
            shopItems[index] = false;
        }
    }
    void resetAllShopItems()
    {
        for (int i = 0; i < 5; i++)
            shopItems[i] = false;
    }
    bool getBalloonMode() const
    {
        return isBalloonMode;
    }
    void setLives(int n) { lives = n; };

    PlayerStats stats;
};