#include "Player.hpp"
#include <cmath>

const float Player::INVINCIBLE_TIME = 1.5f;

Player::Player(int index, PlayerStats stats) : stats(stats), index(index), velocityX(0), velocityY(0), onGround(false), wantsShoot(false), lives(2), gems(0), score(0), invincible(false), invincibleTimer(0), currentAnim(&animIdle), isShooting(false), snowballTimer(0), cooldown(0), snowballCooldown(0.3f)
{
    if (index == 0)
        facingRight = true;
    else
        facingRight = false;

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
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
}

void Player::setHitboxRect(FloatRect localRect)
{
    sprite.setHitbox(localRect);
    sprite.setOrigin(localRect.width / 2.f, localRect.height / 2.f);
}

//This will be called before physics engine update
void Player::handleInput(const InputManager& input, float dt)
{
    if (!isAlive()) 
        return;

    bool goLeft = false, goRight = false;
    bool jumpPressed = false;
    bool shotPressed = false;

    if (index == 0)
        goLeft = input.p1Left();
    else
        goLeft = input.p2Left();

    if (index == 0)
        goRight = input.p1Right();
    else
        goRight = input.p2Right();

    if (goLeft && !goRight)
    {
        velocityX = -stats.walkSpeed;
        facingRight = false;
        sprite.setScale(1.f, 1.f);
        if (isShooting)
            isShooting = false;
    }
    else if (goRight && !goLeft)
    {
        velocityX = stats.walkSpeed;
        facingRight = true;
        sprite.setScale(-1.f, 1.f);
        if (isShooting)
            isShooting = false;
    }
    else if (goRight && goLeft)
    {
        velocityX = 0; 
        if (isShooting)
            isShooting = false;
    }
    else
    {
        velocityX = 0;
    }

    if (index == 0)
        jumpPressed = input.p1Jump(); 
    else
        jumpPressed = input.p2Jump();

    if (jumpPressed && onGround)
    {
        velocityY = stats.jumpHeight;
        onGround = false;
        if (isShooting)
            isShooting = false; 
    }

    
    if (index == 0 && onGround)
        shotPressed = input.p1Shoot();
    else
        shotPressed = input.p2Shoot();

    if (shotPressed && onGround)
    {
        wantsShoot = true;
        isShooting = true;
        snowballTimer = snowballCooldown;
    }
}

void Player::setDirectionRight(bool faceRight)
{
    if (faceRight)
    {
        facingRight = true;
        sprite.setScale(-1.f, 1.f);
    }
    else
    {
        facingRight = false;
        sprite.setScale(1.f, 1.f);
    }
}

void Player::update(float dt)
{
    if (!isAlive()) 
        return;

    if (snowballTimer > 0)
    {
        snowballTimer -= dt;

        if (snowballTimer <= 0)
        {
            snowballTimer = 0;
            isShooting = false;
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

    window.draw(sprite);

    for (int i = 0; i < MAX_BALLS; i++)
        snowballs[i].draw(window, debug);

    //For F1 debug later on
    if (debug)
        sprite.drawHitbox(window, Color::Green);   
}

//For physics engine to actually move the player
void Player::applyVelocity(float dt)
{
    sprite.move(velocityX * dt, velocityY * dt);
}

void Player::landPush(float groundY)
{
    FloatRect hitbox = getHitbox();
    float overlap = (hitbox.top + hitbox.height) - groundY;
    sprite.move(0, -overlap);
    velocityY = 0;
    onGround = true;
}

//For pushing out player from walls and ceiling
void Player::pushOutX(float amount)
{
    sprite.move(amount, 0);
    velocityX = 0;
}

void Player::pushOutY(float amount)
{
    sprite.move(0, amount);

    //If jumping stop
    if (velocityY < 0) 
        velocityY = 0;  
}

void Player::takeDamage()
{
    if (invincible || !isAlive()) 
        return;

    lives--;
    invincible = true;
    invincibleTimer = INVINCIBLE_TIME;
}

FloatRect Player::getHitbox() const
{
    return sprite.getGlobalHitbox();
}

void Player::setPosition(Vector2f pos)
{
    sprite.setPosition(pos);
}

void Player::updateInvincibility(float dt)
{
    if (!invincible) 
        return;

    invincibleTimer -= dt;

    bool showSprite = false;
    
    //This allows for toggling on even/odd frames
    //m_invincibleTime has maximum value 1.5 and only decreases from there
    //so if mult by 10 and check even odd, we would get time based even odd frames
    if (static_cast<int>(invincibleTimer * 10) % 2 == 0)
        showSprite = true;

    if (showSprite)
        sprite.setColor(Color(255, 255, 255, 255));
    else
        sprite.setColor(Color(255, 255, 255, 70));

    if (invincibleTimer <= 0)
    {
        invincible = false;
        sprite.setColor(Color::White);
    }
}

void Player::loadSpritesheet(const Texture& texture, const IntRect* idleFrames, int idleCount, const IntRect* walkFrames, int walkCount, const IntRect* jumpFrames, int jumpCount, const IntRect* shootFrames, int shootCount, FloatRect hitboxRect, float frameDuration)
{
    sprite.setTexture(texture);
    sprite.setHitbox(hitboxRect);
    sprite.setOrigin(hitboxRect.width / 2.f, hitboxRect.height / 2.f);

    animIdle.loadSprite(idleFrames, idleCount, frameDuration, true);

    if (walkCount > 0)
        animWalk.loadSprite(walkFrames, walkCount, frameDuration, true);
    else
        animWalk.loadSprite(idleFrames, idleCount, frameDuration, true);

    if (jumpCount > 0)
        animJump.loadSprite(jumpFrames, jumpCount, frameDuration, false);
    else
        animJump.loadSprite(idleFrames, idleCount, frameDuration, false);

    if (shootCount > 0)
        animShoot.loadSprite(shootFrames, shootCount, frameDuration, true);
    else
        animShoot.loadSprite(idleFrames, idleCount, frameDuration, true);

    currentAnim = &animIdle;
    sprite.setTextureRect(currentAnim->getCurrentFrame());
}

void Player::updateAnimation(float dt)
{
    selectAnimation();
    currentAnim->update(dt);
    sprite.setTextureRect(currentAnim->getCurrentFrame());
}

void Player::selectAnimation()
{
    AnimationComponent* next = nullptr;

    if (!onGround && velocityY < 0.f)
        next = &animJump;
    else if (onGround && isShooting)
        next = &animShoot;
    else if (onGround && velocityX != 0.f)
        next = &animWalk;
    else
        next = &animIdle;

    if (next != currentAnim)
    {
        currentAnim = next;
        currentAnim->reset();
    }
}

void Player::setTextureSnowball(const Texture& texture)
{
    for (int i = 0; i < MAX_BALLS; i++)
        snowballs[i].setTexture(texture);
}

void Player::loadSpritesheetSnowball(const Texture& texture, const IntRect* frames, int count, float duration)
{
    for (int i = 0; i < MAX_BALLS; i++)
        snowballs[i].loadSpritesheet(texture, frames, count, duration);
}

void Player::updateSnowballs(float dt)
{
    if (cooldown > 0.f)
        cooldown -= dt;

    for (int i = 0; i < MAX_BALLS; i++)
        snowballs[i].update(dt);

    if (!consumeShoot() || cooldown > 0.f)
        return;

    for (int i = 0; i < MAX_BALLS; i++)
    {
        if (!snowballs[i].isActive())
        {
            FloatRect hitbox = getHitbox();

            float spawnX = 0, spawnY = 0;
            if (isFacingRight())
                spawnX = hitbox.left + hitbox.width + 2.f;
            else
                spawnX = hitbox.left - 18.f;

            spawnY = hitbox.top + hitbox.height * 0.35f;

            snowballs[i].fire(Vector2f(spawnX, spawnY), isFacingRight());

            cooldown = snowballCooldown;
            return;
        }
    }
}