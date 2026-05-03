#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class HitboxSprite : public sf::Sprite {
private:
	sf::FloatRect hitbox;

public:
	void setHitbox(const sf::FloatRect& hitbox);

	sf::FloatRect getGlobalHitbox() const;

	bool intersects(const HitboxSprite& other) const;

	bool intersects(const sf::FloatRect& rect) const;

	void drawHitbox(sf::RenderWindow& window, sf::Color color = sf::Color::Green) const;

};