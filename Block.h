#pragma once
#include <SFML/Graphics.hpp>
#include "Hitbox.h"

using namespace std;
using namespace sf;

class Block
{
private:
    HitboxSprite m_sprite;

public:
    Block() {} 

    Block(float x, float y, float width, float height, const Texture& texture)
    {
        m_sprite.setHitbox(FloatRect{ 0,0,width,height });
        m_sprite.setPosition(x, y);
        // m_sprite.setTexture(texture);
    }

    void draw(RenderWindow& window, bool debug = false) const
    {
        window.draw(m_sprite);
        if (debug)
        {
            RectangleShape hitbox(Vector2f(m_sprite.getGlobalHitbox().width, m_sprite.getGlobalHitbox().height));
            hitbox.setPosition(m_sprite.getGlobalHitbox().left, m_sprite.getGlobalHitbox().top);
            hitbox.setFillColor(Color::Transparent);
            hitbox.setOutlineColor(Color::Blue); 
            hitbox.setOutlineThickness(1.f);
            window.draw(hitbox);
        }
    }

    FloatRect getHitbox() const 
    { 
        return m_sprite.getGlobalHitbox();
    }
    HitboxSprite getHitboxSprite() const {return m_sprite;}
};