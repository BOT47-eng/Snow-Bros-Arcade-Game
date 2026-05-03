#pragma once
#include <SFML/Graphics.hpp>
#include "Hitbox.hpp"

class Block
{
private:
    HitboxSprite sprite;

public:
    Block() {} 

    Block(float x, float y, float width, float height, const sf::Texture& texture)
    {
        sprite.setHitbox(sf::FloatRect{ 0,0,width,height });
        sprite.setPosition(x, y);
        //sprite.setTexture(texture);
    }

    Block(float x, float y, float width, float height)
    {
        sprite.setHitbox(sf::FloatRect{ 0,0,width,height });
        sprite.setPosition(x, y);
    }

    void draw(sf::RenderWindow& window, bool debug = false) const
    {
        window.draw(sprite);

        if (debug)
        {
            sf::RectangleShape hitbox(sf::Vector2f(sprite.getGlobalHitbox().width, sprite.getGlobalHitbox().height));
            hitbox.setPosition(sprite.getGlobalHitbox().left, sprite.getGlobalHitbox().top);
            hitbox.setFillColor(sf::Color::Transparent);
            hitbox.setOutlineColor(sf::Color::Blue); 
            hitbox.setOutlineThickness(1);
            window.draw(hitbox);
        }
        else
        {
            sf::RectangleShape hitbox(sf::Vector2f(sprite.getGlobalHitbox().width, sprite.getGlobalHitbox().height));
            hitbox.setPosition(sprite.getGlobalHitbox().left, sprite.getGlobalHitbox().top);
            hitbox.setFillColor(sf::Color(230, 216, 25, 255));
            window.draw(hitbox);
        }
    }

    sf::FloatRect getHitbox() const 
    { 
        return sprite.getGlobalHitbox();
    }
};