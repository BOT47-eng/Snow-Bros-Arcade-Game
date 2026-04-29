#include "Projectile.hpp"
#include <cmath>

using namespace sf;

Snowball::Snowball() : animated(false), distTraveled(0), snowAmount(1), maxDistance(150), speed(250)
{
    FloatRect hitbox = sprite.getGlobalHitbox();
    sprite.setHitbox(FloatRect(1, 1, 22, 33));
    sprite.setOrigin(Vector2f(hitbox.width / 2.f, hitbox.height / 2.f));
}

void Snowball::setTexture(const Texture& texture)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0, 0, 16, 16));
    animated = false;
}

void Snowball::loadSpritesheet(const Texture& texture, const IntRect* frames, int count, float duration)
{
    sprite.setTexture(texture);
    anim.loadSprite(frames, count, duration, true);
    animated = true;
    sprite.setTextureRect(anim.getCurrentFrame());
}

void Snowball::fire(Vector2f pos, bool facingRight)
{
    if (facingRight)
    {
        Vx = speed;
        sprite.setScale(-1, 1);
    }
    else
    {
        Vx = -speed;
        sprite.setScale(1, 1);
    }
    //Currently vertical velocity is zero but can be changed in the future
    Vy = 0;
    distTraveled = 0;
    active = true;
    sprite.setPosition(pos);

    if (animated)
        anim.reset();
}

void Snowball::update(float dt)
{
    if (!active)
        return;

    float dx = Vx * dt;
    float dy = Vy * dt;
    sprite.move(dx, dy);
    distTraveled += abs(dx) + abs(dy);

    FloatRect hitbox = sprite.getGlobalHitbox();
    Vector2f  pos = sprite.getPosition();

    if (hitbox.left + hitbox.width < 0.f)
        sprite.setPosition(Vector2f(GAME_WIDTH, pos.y));
    else if (hitbox.left > GAME_WIDTH)
        sprite.setPosition(Vector2f(0, pos.y));

    if (animated)
    {
        anim.update(dt);
        sprite.setTextureRect(anim.getCurrentFrame());
    }

    if (distTraveled >= maxDistance)
    {
        active = false;
    }
}

void Snowball::draw(RenderWindow& window, bool debug) const
{
    if (!active)
        return;

    window.draw(sprite);

    if (debug)
        sprite.drawHitbox(window, Color::Yellow);
}