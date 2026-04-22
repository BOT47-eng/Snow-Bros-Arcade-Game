#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class HitboxSprite : public Sprite {
private:
	FloatRect m_hitbox;

public:
	void setHitbox(const FloatRect& hitbox) 
	{
		m_hitbox = hitbox;
	}

	FloatRect getGlobalHitbox() const 
	{
		return getTransform().transformRect(m_hitbox);
	}

	bool intersects(const HitboxSprite& other) const
	{
		return getGlobalHitbox().intersects(other.getGlobalHitbox());
	}

	bool intersects(const FloatRect& rect) const
	{
		return getGlobalHitbox().intersects(rect);
	}

	void drawHitbox(sf::RenderWindow& window, Color color = Color::Green) const
	{
		FloatRect temp = getGlobalHitbox();
		RectangleShape outline(Vector2f(temp.width, temp.height));
		outline.setPosition(temp.left, temp.top);
		outline.setFillColor(Color::Transparent);
		outline.setOutlineColor(color);
		outline.setOutlineThickness(1.5f);
		window.draw(outline);
	}

};