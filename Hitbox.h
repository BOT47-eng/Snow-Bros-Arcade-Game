#pragma once
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class HitboxSprite : public Sprite {
private:
	FloatRect m_hitbox;

public:
	void setHitbox(const FloatRect& hitbox);

	FloatRect getGlobalHitbox() const;

	bool intersects(const HitboxSprite& other) const;

	bool intersects(const FloatRect& rect) const;

	void drawHitbox(RenderWindow& window, Color color = Color::Green) const;

};