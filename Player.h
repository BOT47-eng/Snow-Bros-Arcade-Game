#pragma once
#include <SFML/Graphics.hpp>
#include "Hitbox.h"
#include "InputManager.h"
#include "AnimationComponent.h"

//These stats can be loaded from config file
struct PlayerStats
{
    float walkSpeed = 200.f;
    float jumpHeight = -520.f;  
};

//Player 1 is 0 index, Player 2 is 1 index
class Player
{
private:
    void updateInvincibility(float dt);

    int m_index;
    int m_lives;
    int m_gems;
    int m_score;
    float m_velocityX;
    float m_velocityY;
    float m_invincibleTimer;
    float m_snowballTimer;
    bool m_onGround;
    bool m_facingRight;
    bool m_wantsShoot;
    bool m_invincible;
    bool m_isShooting;

    HitboxSprite m_sprite;

    void updateAnimation(float dt);     // tick current anim + apply frame to sprite
    void selectAnimation();

    AnimationComponent m_animIdle;
    AnimationComponent m_animWalk;
    AnimationComponent m_animJump;
    AnimationComponent m_animShoot;
    AnimationComponent* m_currentAnim;

    static const float INVINCIBLE_TIME;
    static const float SNOWBALL_COOLDOWN;

public:
    Player(int index, PlayerStats stats = PlayerStats());
    void setTexture(const Texture& texture, IntRect rect);
    void setHitboxRect(FloatRect localRect);
    void handleInput(const InputManager& input, float dt);
    void update(float dt);
    void draw(RenderWindow& window, bool debug = false) const;

    void loadSpritesheet(const Texture& tex, const IntRect* idleFrames, int idleCount, const IntRect* walkFrames, int walkCount, const IntRect* jumpFrames, int jumpCount, const IntRect* fallFrames, int fallCount, FloatRect        hitboxRect, float            frameDuration = 0.1f);

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

    PlayerStats stats;
};