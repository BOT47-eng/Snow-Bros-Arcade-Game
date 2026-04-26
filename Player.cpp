#include "Player.h"
#include <cmath>

const float Player::INVINCIBLE_TIME = 1.5f;

Player::Player(int index, PlayerStats stats) : stats(stats), m_index(index), m_velocityX(0), m_velocityY(0), m_onGround(false), m_wantsShoot(false), m_lives(2), m_gems(0), m_score(0), m_invincible(false), m_invincibleTimer(0), m_currentAnim(&m_animIdle), m_isShooting(false), m_snowballTimer(0), m_cooldown(0), m_snowballCooldown(0.3f)
{
    if (index == 0)
        m_facingRight = true;
    else
        m_facingRight = false;

    if (index == 0)
    {
        playerTexture.loadFromFile("SnowBrosAssets/Images/Player_Blue.png");
        setDirectionRight(true);
        loadSpritesheetSnowball(playerTexture, &snowballFrames, 1);
    }
    else
    {
        playerTexture.loadFromFile("SnowBrosAssets/Images/Player_Red.png");
        snowballFrames.left = 557;
        loadSpritesheetSnowball(playerTexture, &snowballFrames, 1);
    }

    loadSpritesheet(playerTexture, &idlePlayerFrames, 1, walkPlayerFrames, 3, jumpPlayerFrames, 6, &shootPlayerFrames, 1, playerHitbox);
}

void Player::setTexture(const Texture& texture, IntRect rect)
{
    m_sprite.setTexture(texture);
    m_sprite.setTextureRect(rect);
}

void Player::setHitboxRect(FloatRect localRect)
{
    m_sprite.setHitbox(localRect);
    m_sprite.setOrigin(localRect.width / 2.f, localRect.height / 2.f);
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
        m_sprite.setScale(1.f, 1.f);
        if (m_isShooting)
            m_isShooting = false;
    }
    else if (goRight && !goLeft)
    {
        m_velocityX = stats.walkSpeed;
        m_facingRight = true;
        m_sprite.setScale(-1.f, 1.f);
        if (m_isShooting)
            m_isShooting = false;
    }
    else if (goRight && goLeft)
    {
        m_velocityX = 0; 
        if (m_isShooting)
            m_isShooting = false;
    }
    else
    {
        m_velocityX = 0;
    }

    if (m_index == 0)
        jumpPressed = input.p1Jump(); 
    else
        jumpPressed = input.p2Jump();

    if (jumpPressed && m_onGround)
    {
        m_velocityY = stats.jumpHeight;
        m_onGround = false;
        if (m_isShooting)
            m_isShooting = false; 
    }

    
    if (m_index == 0 && m_onGround)
        shotPressed = input.p1Shoot();
    else
        shotPressed = input.p2Shoot();

    if (shotPressed && m_onGround)
    {
        m_wantsShoot = true;
        m_isShooting = true;
        m_snowballTimer = m_snowballCooldown;
    }
}

void Player::setDirectionRight(bool faceRight)
{
    if (faceRight)
    {
        m_facingRight = true;
        m_sprite.setScale(-1.f, 1.f);
    }
    else
    {
        m_facingRight = false;
        m_sprite.setScale(1.f, 1.f);
    }
}

void Player::update(float dt)
{
    if (!isAlive()) 
        return;

    if (m_snowballTimer > 0)
    {
        m_snowballTimer -= dt;

        if (m_snowballTimer <= 0)
        {
            m_snowballTimer = 0;
            m_isShooting = false;
        }
    }

    updateSnowballs(dt);
    updateInvincibility(dt);
    updateAnimation(dt);
}

void Player::draw(RenderWindow& window, bool debug) const
{
    if (!isAlive()) 
        return;

    window.draw(m_sprite);

    for (int i = 0; i < MAX_BALLS; i++)
        m_balls[i].draw(window, debug);

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

void Player::loadSpritesheet(const Texture& texture, const IntRect* idleFrames, int idleCount, const IntRect* walkFrames, int walkCount, const IntRect* jumpFrames, int jumpCount, const IntRect* shootFrames, int shootCount, FloatRect hitboxRect, float frameDuration)
{
    m_sprite.setTexture(texture);
    m_sprite.setHitbox(hitboxRect);
    m_sprite.setOrigin(hitboxRect.width / 2.f, hitboxRect.height / 2.f);

    m_animIdle.loadSprite(idleFrames, idleCount, frameDuration, true);

    if (walkCount > 0)
        m_animWalk.loadSprite(walkFrames, walkCount, frameDuration, true);
    else
        m_animWalk.loadSprite(idleFrames, idleCount, frameDuration, true);

    if (jumpCount > 0)
        m_animJump.loadSprite(jumpFrames, jumpCount, frameDuration, false);
    else
        m_animJump.loadSprite(idleFrames, idleCount, frameDuration, false);

    if (shootCount > 0)
        m_animShoot.loadSprite(shootFrames, shootCount, frameDuration, true);
    else
        m_animShoot.loadSprite(idleFrames, idleCount, frameDuration, true);

    m_currentAnim = &m_animIdle;
    m_sprite.setTextureRect(m_currentAnim->getCurrentFrame());
}

void Player::updateAnimation(float dt)
{
    selectAnimation();
    m_currentAnim->update(dt);
    m_sprite.setTextureRect(m_currentAnim->getCurrentFrame());
}

void Player::selectAnimation()
{
    AnimationComponent* next = nullptr;

    if (!m_onGround && m_velocityY < 0.f)
        next = &m_animJump;
    else if (m_onGround && m_isShooting)
        next = &m_animShoot;
    else if (m_onGround && m_velocityX != 0.f)
        next = &m_animWalk;
    else
        next = &m_animIdle;

    if (next != m_currentAnim)
    {
        m_currentAnim = next;
        m_currentAnim->reset();
    }
}

void Player::setTextureSnowball(const Texture& texture)
{
    for (int i = 0; i < MAX_BALLS; i++)
        m_balls[i].setTexture(texture);
}

void Player::loadSpritesheetSnowball(const Texture& texture, const IntRect* frames, int count, float duration)
{
    for (int i = 0; i < MAX_BALLS; i++)
        m_balls[i].loadSpritesheet(texture, frames, count, duration);
}

void Player::updateSnowballs(float dt)
{
    if (m_cooldown > 0.f)
        m_cooldown -= dt;

    for (int i = 0; i < MAX_BALLS; i++)
        m_balls[i].update(dt);

    if (!consumeShoot() || m_cooldown > 0.f)
        return;

    for (int i = 0; i < MAX_BALLS; i++)
    {
        if (!m_balls[i].isActive())
        {
            FloatRect hitbox = getHitbox();

            float spawnX = 0, spawnY = 0;
            if (isFacingRight())
                spawnX = hitbox.left + hitbox.width + 2.f;
            else
                spawnX = hitbox.left - 18.f;

            spawnY = hitbox.top + hitbox.height * 0.35f;

            m_balls[i].fire(Vector2f(spawnX, spawnY), isFacingRight(), SCREEN_WIDTH);

            m_cooldown = m_snowballCooldown;
            return;
        }
    }
}