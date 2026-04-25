#pragma once
#include <SFML/Graphics.hpp>
#include "Hitbox.h"
#include "AnimationComponent.h"

using namespace sf;

class Projectile
{
protected:
    HitboxSprite m_sprite;
    float m_Vx;
    float m_Vy;
    bool m_active;

public:
    Projectile() : m_Vx(0), m_Vy(0), m_active(false) {}

    virtual void update(float dt) = 0;
    virtual void draw(RenderWindow& window, bool debug) const = 0;
    virtual ~Projectile() {}

    FloatRect getHitbox() const 
    { 
        return m_sprite.getGlobalHitbox(); 
    }
    Vector2f getPosition() const 
    { 
        return m_sprite.getPosition(); 
    }
    bool isActive() const 
    {
        return m_active; 
    }
    void setActive(bool act) 
    {
        m_active = act; 
    }
};

class Snowball : public Projectile
{
private:
    AnimationComponent m_anim;
    bool m_animated;       

    //Snow amount dictates how much snow a single snowball deposits on an enemy
    //By default it is 1 but can be increased by power ups
    float m_distTraveled;
    float m_screenWidth;
    int m_snowAmount;

    float m_speed;
    float m_maxDistance;

public:
    Snowball();

    void setTexture(const Texture& texture);

    void loadSpritesheet(const Texture& texture, const IntRect* frames, int count, float duration = 0.05);

    void fire(Vector2f pos, bool facingRight, float screenWidth);

    void update(float dt) override;
    void draw(RenderWindow& window, bool debug = false) const override;

    int getSnowAmount() const 
    {
        return m_snowAmount;
    }
};