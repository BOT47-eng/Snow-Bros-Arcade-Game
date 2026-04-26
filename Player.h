#pragma once
#include <SFML/Graphics.hpp>
#include "Hitbox.h"
#include "InputManager.h"
#include "AnimationComponent.h"
#include "Projectile.h"

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

    Snowball m_balls[MAX_BALLS];
    float m_cooldown;

    int m_index;
    int m_lives;
    int m_gems;
    int m_score;
    float m_velocityX;
    float m_velocityY;
    float m_invincibleTimer;
    float m_snowballTimer;
    float m_snowballCooldown;
    bool m_onGround;
    bool m_facingRight;
    bool m_wantsShoot;
    bool m_invincible;
    bool m_isShooting;

    const FloatRect playerHitbox = { 0, 0, 60, 72 };
    const IntRect idlePlayerFrames = { IntRect(19, 3, 57, 72) };
    const IntRect walkPlayerFrames[3] = { IntRect(100, 3, 45, 72), IntRect(185 , 3, 52, 73), IntRect(269, 1, 49, 74) };
    const IntRect jumpPlayerFrames[6] = { IntRect(9, 83, 60, 75), IntRect(95, 83, 60, 65), IntRect(180, 83, 60, 65), IntRect(263, 85, 60, 75), IntRect(351, 88, 60, 70), IntRect(433, 86, 68, 68) };
    const IntRect shootPlayerFrames = { IntRect(252, 172, 72, 72) };
    IntRect snowballFrames = { IntRect(514, 1022, 22, 33) };

    HitboxSprite m_sprite;

    void updateAnimation(float dt);     // tick current anim + apply frame to sprite
    void selectAnimation();

    AnimationComponent m_animIdle;
    AnimationComponent m_animWalk;
    AnimationComponent m_animJump;
    AnimationComponent m_animShoot;
    AnimationComponent* m_currentAnim;

    static const float INVINCIBLE_TIME;

public:
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
        m_score += points;
    }
    void addGems(int n) 
    { 
        m_gems += n;
    }
    void addLife() 
    { 
        m_lives++;
    }

    FloatRect getHitbox() const;
    Vector2f getPosition() const 
    { 
        return m_sprite.getPosition(); 
    }
    float getVelocityX() const 
    { 
        return m_velocityX; 
    }
    float getVelocityY() const 
    { 
        return m_velocityY; 
    }
    bool isOnGround() const
    { 
        return m_onGround; 
    }
    bool isAlive() const 
    { 
        return m_lives > 0;
    }
    bool isInvincible() const 
    { 
        return m_invincible;
    }
    bool isFacingRight() const 
    { 
        return m_facingRight; 
    }
    int getLives() const 
    { 
        return m_lives; 
    }
    int getGems() const 
    { 
        return m_gems; 
    }
    int getScore() const 
    { 
        return m_score;
    }
    int getIndex() const 
    { 
        return m_index; 
    }
    
    //This returns shoot flag and resets it
    bool consumeShoot() 
    { 
        bool temp = m_wantsShoot; 
        m_wantsShoot = false; 
        return temp; 
    }

    //For physics engine
    void setPosition(Vector2f pos);
    void setVelocityX(float Vx) 
    { 
        m_velocityX = Vx; 
    }
    void setVelocityY(float Vy)
    { 
        m_velocityY = Vy; 
    }
    void setOnGround(bool v) 
    { 
        m_onGround = v; 
    }
    void setDirectionRight(bool faceRight);

    //For snowballs
    void setTextureSnowball(const Texture& texture);
    void loadSpritesheetSnowball(const Texture& texture, const IntRect* frames, int count, float duration = 0.05);
    void updateSnowballs(float dt);
    Snowball& getBall(int i)
    {
        return m_balls[i];
    }

    PlayerStats stats;
};