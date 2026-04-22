#include "Player.h"
#include <cmath>

const float Player::INVINCIBLE_TIME = 1.5f;

Player::Player(int index, PlayerStats stats) : stats(stats), m_index(index), m_velocityX(0.f), m_velocityY(0.f), m_onGround(false), m_wantsShoot(false), m_lives(3), m_gems(0), m_score(0), m_invincible(false), m_invincibleTimer(0.f)
{
    if (index == 0)
        m_facingRight = true;
    else
        m_facingRight = false;
}

void Player::setTexture(const Texture& texture, IntRect rect)
{
    m_sprite.setTexture(texture);
    m_sprite.setTextureRect(rect);
}

void Player::setHitboxRect(FloatRect localRect)
{
    m_sprite.setHitbox(localRect);
}

//This will be called before physics engine update
void Player::handleInput(const InputManager& input, float dt)
{
    if (!isAlive()) 
        return;

    bool goLeft = false, goRight = false;
    bool jumpPressed = false;
    bool shotPressed = false;

    if (m_index == 0)
        goLeft = input.p1Left();
    else
        goLeft = input.p2Left();

    if (m_index == 0)
        goRight = input.p1Right();
    else
        goRight = input.p2Right();

    if (goLeft && !goRight)
    {
        m_velocityX = -stats.walkSpeed;
        m_facingRight = false;
        m_sprite.setScale(-1.f, 1.f);
    }
    else if (goRight && !goLeft)
    {
        m_velocityX = stats.walkSpeed;
        m_facingRight = true;
        m_sprite.setScale(1.f, 1.f);
    }
    else
    {
        m_velocityX = 0.f; 
    }

    if (m_index == 0)
        jumpPressed = input.p1Jump(); 
    else
        jumpPressed = input.p2Jump();

    if (jumpPressed && m_onGround)
    {
        m_velocityY = stats.jumpHeight;
        m_onGround = false;
    }

    
    if (m_index == 0)
        shotPressed = input.p1Shoot();
    else
        shotPressed = input.p2Shoot();

    if (shotPressed)
        m_wantsShoot = true;
}

void Player::update(float dt)
{
    if (!isAlive()) 
        return;

    tickInvincibility(dt);
}

void Player::draw(RenderWindow& window, bool debug) const
{
    if (!isAlive()) 
        return;

    window.draw(m_sprite);

    //For F1 debug later on
    if (debug)
        m_sprite.drawHitbox(window, Color::Green);   
}

//For physics engine to actually move the player
void Player::applyVelocity(float dt)
{
    m_sprite.move(m_velocityX * dt, m_velocityY * dt);
}

void Player::landPush(float groundY)
{
    FloatRect hitbox = getHitbox();
    float overlap = (hitbox.top + hitbox.height) - groundY;
    m_sprite.move(0, -overlap);
    m_velocityY = 0;
    m_onGround = true;
}

//For pushing out player from walls and ceiling
void Player::pushOutX(float amount)
{
    m_sprite.move(amount, 0);
    m_velocityX = 0;
}

void Player::pushOutY(float amount)
{
    m_sprite.move(0, amount);

    //If jumping stop
    if (m_velocityY < 0) 
        m_velocityY = 0;  
}

void Player::takeDamage()
{
    if (m_invincible || !isAlive()) 
        return;

    m_lives--;
    m_invincible = true;
    m_invincibleTimer = INVINCIBLE_TIME;
}

FloatRect Player::getHitbox() const
{
    return m_sprite.getGlobalHitbox();
}

void Player::setPosition(Vector2f pos)
{
    m_sprite.setPosition(pos);
}

void Player::updateInvincibility(float dt)
{
    if (!m_invincible) 
        return;

    m_invincibleTimer -= dt;

    bool showSprite = false;
    
    //This allows for toggling on even/odd frames
    //m_invincibleTime has maximum value 1.5 and only decreases from there
    //so if mult by 10 and check even odd, we would get time based even odd frames
    if (static_cast<int>(m_invincibleTimer * 10) % 2 == 0)
        showSprite = true;

    if (showSprite)
        m_sprite.setColor(Color(255, 255, 255, 255));
    else
        m_sprite.setColor(Color(255, 255, 255, 70));

    if (m_invincibleTimer <= 0)
    {
        m_invincible = false;
        m_sprite.setColor(Color::White);
    }
}