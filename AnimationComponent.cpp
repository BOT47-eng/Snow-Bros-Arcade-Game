#include "AnimationComponent.hpp"

using namespace sf;

AnimationComponent::AnimationComponent() : frameCount(0), currentFrame(0), frameDuration(0.1f), frameTimer(0.f), looping(true), finished(false)
{
    for (int i = 0; i < MAX_FRAMES; i++)
        frames[i] = IntRect(0, 0, 0, 0);
}

void AnimationComponent::loadSprite(const IntRect* frames, int count, float frameDuration, bool looping)
{
    if (count <= MAX_FRAMES)
        frameCount = count;
    else
        frameCount = MAX_FRAMES;

    for (int i = 0; i < frameCount; i++)
        this->frames[i] = frames[i];

    this->frameDuration = frameDuration;
    this->looping = looping;
    currentFrame = 0;
    frameTimer = 0;
    finished = false;
}

void AnimationComponent::update(float dt)
{
    if (frameCount == 0 || finished)
        return;

    frameTimer += dt;

    if (frameTimer >= frameDuration)
    {
        frameTimer -= frameDuration;
        currentFrame++;

        if (currentFrame >= frameCount)
        {
            if (looping)
            {
                currentFrame = 0;
            }
            else
            {
                currentFrame = frameCount - 1;  
                finished = true;
            }
        }
    }
}

IntRect AnimationComponent::getCurrentFrame() const
{
    if (frameCount == 0)
        return IntRect(0, 0, 0, 0);

    return frames[currentFrame];
}

void AnimationComponent::reset()
{
    currentFrame = 0;
    frameTimer = 0;
    finished = false;
}

bool AnimationComponent::isFinished() const
{
    return finished;
}