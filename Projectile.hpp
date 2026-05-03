#pragma once
#include <SFML/Graphics.hpp>
#include "Hitbox.hpp"
#include "AnimationComponent.hpp"

class Projectile
{
protected:
    HitboxSprite sprite;
    float Vx;
    float Vy;
    bool active;
    static int const GAME_WIDTH = 600;

public:
    Projectile() : Vx(0), Vy(0), active(false) {}

    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window, bool debug) const = 0;
    virtual ~Projectile() {}

    sf::FloatRect getHitbox() const 
    { 
        return sprite.getGlobalHitbox(); 
    }
    sf::Vector2f getPosition() const 
    { 
        return sprite.getPosition(); 
    }
    bool isActive() const 
    {
        return active; 
    }
    void setActive(bool act) 
    {
        active = act; 
    }
};

class Snowball : public Projectile
{
private:
    AnimationComponent anim;
    bool animated;       

    //Snow amount dictates how much snow a single snowball deposits on an enemy
    //By default it is 1 but can be increased by power ups
    float distTraveled;
    int snowAmount;

    float speed;
    float maxDistance;

public:
    Snowball();

    void setTexture(const sf::Texture& texture);

    void loadSpritesheet(const sf::Texture& texture, const sf::IntRect* frames, int count, float duration = 0.05);

    void fire(sf::Vector2f pos, bool facingRight);

    void update(float dt) override;
    void draw(sf::RenderWindow& window, bool debug = false) const override;

    int getSnowAmount() const 
    {
        return snowAmount;
    }

    void setSnowAmount(int amount)
    {
        snowAmount = amount;
    }
    void setMaxDistance(float n)
    {
        maxDistance = n ;
    }
};