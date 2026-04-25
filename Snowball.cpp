#include "Projectile.h"
#include <cmath>

using namespace sf;

Snowball::Snowball() : m_animated(false), m_distTraveled(0), m_screenWidth(600), m_snowAmount(1), m_maxDistance(150), m_speed(250)
{
    m_sprite.setHitbox(FloatRect(1.f, 1.f, 14.f, 14.f));
}

void Snowball::setTexture(const Texture& texture)
{
    m_sprite.setTexture(texture);
    m_sprite.setTextureRect(IntRect(0, 0, 16, 16));
    m_animated = false;
}

void Snowball::loadSpritesheet(const Texture& texture, const IntRect* frames, int count, float duration)
{
    m_sprite.setTexture(texture);
    m_anim.load(frames, count, duration, true);
    m_animated = true;
    m_sprite.setTextureRect(m_anim.getCurrentFrame());
}

void Snowball::fire(Vector2f pos, bool facingRight, float screenWidth)
{
    if (facingRight)
        m_Vx = m_speed;
    else
        m_Vx = -m_speed;
    m_Vy = 0;
    m_distTraveled = 0;
    m_screenWidth = screenWidth;
    m_active = true;
    m_sprite.setPosition(pos);

    if (m_animated)
        m_anim.reset();
}

void Snowball::update(float dt)
{
    if (!m_active)
        return;

    float dx = m_Vx * dt;
    float dy = m_Vy * dt;
    m_sprite.move(dx, dy);
    m_distTraveled += abs(dx);

    FloatRect hitbox = m_sprite.getGlobalHitbox();
    Vector2f  pos = m_sprite.getPosition();

    if (hitbox.left + hitbox.width < 0.f)
        m_sprite.setPosition(Vector2f(m_screenWidth, pos.y));
    else if (hitbox.left > m_screenWidth)
        m_sprite.setPosition(Vector2f(-hitbox.width, pos.y));

    if (m_animated)
    {
        m_anim.update(dt);
        m_sprite.setTextureRect(m_anim.getCurrentFrame());
    }

    if (m_distTraveled >= m_maxDistance)
        m_active = false;
}

void Snowball::draw(RenderWindow& window, bool debug) const
{
    if (!m_active)
        return;

    window.draw(m_sprite);

    if (debug)
        m_sprite.drawHitbox(window, Color::Yellow);
}