#pragma once
#include <SFML/Graphics.hpp>
#include "Hitbox.hpp"
#include "InputManager.hpp"
#include "AnimationComponent.hpp"
#include "Projectile.hpp"

//These stats can be loaded from config file
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
    Texture playerTexture;

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
    bool onGround;
    bool facingRight;
    bool wantsShoot;
    bool invincible;
    bool isShooting;
    bool isBallonMode ; 

    const FloatRect playerHitbox = { 0, 0, 60, 72 };
    const IntRect idlePlayerFrames = { IntRect(19, 3, 57, 72) };
    const IntRect walkPlayerFrames[3] = { IntRect(100, 3, 45, 72), IntRect(185 , 3, 52, 73), IntRect(269, 1, 49, 74) };
    const IntRect jumpPlayerFrames[6] = { IntRect(9, 83, 60, 75), IntRect(95, 83, 60, 65), IntRect(180, 83, 60, 65), IntRect(263, 85, 60, 75), IntRect(351, 88, 60, 70), IntRect(433, 86, 68, 68) };
    const IntRect shootPlayerFrames = { IntRect(252, 172, 72, 72) };
    IntRect snowballFrames = { IntRect(514, 1022, 22, 33) };

    HitboxSprite sprite;

    void updateAnimation(float dt);     // tick current anim + apply frame to sprite
    void selectAnimation();

    AnimationComponent animIdle;
    AnimationComponent animWalk;
    AnimationComponent animJump;
    AnimationComponent animShoot;
    AnimationComponent* currentAnim;

    static const float INVINCIBLE_TIME;

public:
    Player() ;
    Player(int index, PlayerStats stats = PlayerStats());
    void setTexture(const Texture& texture, IntRect rect);
    void setHitboxRect(FloatRect localRect);
    void handleInput(const InputManager& input, float dt);
    void update(float dt);
    void draw(RenderWindow& window, bool debug = false) const;

    void loadSpritesheet(const Texture& texture, const IntRect* idleFrames, int idleCount, const IntRect* walkFrames, int walkCount, const IntRect* jumpFrames, int jumpCount, const IntRect* fallFrames, int fallCount, FloatRect        hitboxRect, float            frameDuration = 0.1f);

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

    FloatRect getHitbox() const;
    Vector2f getPosition() const 
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
    bool getBallonMode() const {return isBallonMode ; }
    
    //This returns shoot flag and resets it
    bool consumeShoot() 
    { 
        bool temp = wantsShoot; 
        wantsShoot = false; 
        return temp; 
    }

    //For physics engine
    void setPosition(Vector2f pos);
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
        isBallonMode = v ; 
    }

    //For snowballs
    void setTextureSnowball(const Texture& texture);
    void loadSpritesheetSnowball(const Texture& texture, const IntRect* frames, int count, float duration = 0.05);
    void updateSnowballs(float dt);

    Snowball& getBall(int i)
    {
        return snowballs[i];
    }

    PlayerStats stats;
};