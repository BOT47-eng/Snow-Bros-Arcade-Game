#include "Hitbox.h"

void HitboxSprite::setHitbox(const FloatRect& hitbox)
{
	m_hitbox = hitbox;
}

FloatRect HitboxSprite::getGlobalHitbox() const
{
	return getTransform().transformRect(m_hitbox);
}

bool HitboxSprite::intersects(const HitboxSprite& other) const
{
	return getGlobalHitbox().intersects(other.getGlobalHitbox());
}

bool HitboxSprite::intersects(const FloatRect& rect) const
{
	return getGlobalHitbox().intersects(rect);
}

// By Saad :
// Removed the default argument of color,  cannot redefine it if already define .h file 
void HitboxSprite::drawHitbox(RenderWindow& window, Color color) const
{
	FloatRect temp = getGlobalHitbox();
	RectangleShape outline(Vector2f(temp.width, temp.height));
	outline.setPosition(temp.left, temp.top);
	outline.setFillColor(Color::Transparent);
	outline.setOutlineColor(color);
	outline.setOutlineThickness(1.5f);
	window.draw(outline);
}