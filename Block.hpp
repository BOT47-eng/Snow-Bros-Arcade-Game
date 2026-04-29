#pragma once
#include <SFML/Graphics.hpp>
#include "Hitbox.hpp"

using namespace std;
using namespace sf;

class Block
{
private:
    HitboxSprite sprite;

public:
    Block() {} 

    Block(float x, float y, float width, float height, const Texture& texture)
    {
        sprite.setHitbox(FloatRect{ 0,0,width,height });
        sprite.setPosition(x, y);
        //sprite.setTexture(texture);
    }

    Block(float x, float y, float width, float height)
    {
        sprite.setHitbox(FloatRect{ 0,0,width,height });
        sprite.setPosition(x, y);
    }

    void draw(RenderWindow& window, bool debug = false) const
    {
        window.draw(sprite);

        if (debug)
        {
            RectangleShape hitbox(Vector2f(sprite.getGlobalHitbox().width, sprite.getGlobalHitbox().height));
            hitbox.setPosition(sprite.getGlobalHitbox().left, sprite.getGlobalHitbox().top);
            hitbox.setFillColor(Color::Transparent);
            hitbox.setOutlineColor(Color::Blue); 
            hitbox.setOutlineThickness(1);
            window.draw(hitbox);
        }
        else
        {
            RectangleShape hitbox(Vector2f(sprite.getGlobalHitbox().width, sprite.getGlobalHitbox().height));
            hitbox.setPosition(sprite.getGlobalHitbox().left, sprite.getGlobalHitbox().top);
            hitbox.setFillColor(Color(230, 216, 25, 255));
            window.draw(hitbox);
        }
    }

    FloatRect getHitbox() const 
    { 
        return sprite.getGlobalHitbox();
    }
};