#include "AnimationComponent.h"

AnimationComponent::AnimationComponent() : m_frameCount(0), m_currentFrame(0), m_frameDuration(0.1f), m_frameTimer(0.f), m_looping(true), m_finished(false)
{
    for (int i = 0; i < MAX_FRAMES; i++)
        m_frames[i] = IntRect(0, 0, 0, 0);
}

void AnimationComponent::loadSprite(const IntRect* frames, int count, float frameDuration, bool looping)
{
    if (count <= MAX_FRAMES)
        m_frameCount = count;
    else
        m_frameCount = MAX_FRAMES;

    for (int i = 0; i < m_frameCount; i++)
        m_frames[i] = frames[i];

    m_frameDuration = frameDuration;
    m_looping = looping;
    m_currentFrame = 0;
    m_frameTimer = 0;
    m_finished = false;
}

void AnimationComponent::update(float dt)
{
    if (m_frameCount == 0 || m_finished)
        return;

    m_frameTimer += dt;

    if (m_frameTimer >= m_frameDuration)
    {
        m_frameTimer -= m_frameDuration;
        m_currentFrame++;

        if (m_currentFrame >= m_frameCount)
        {
            if (m_looping)
            {
                m_currentFrame = 0;
            }
            else
            {
                m_currentFrame = m_frameCount - 1;  
                m_finished = true;
            }
        }
    }
}

IntRect AnimationComponent::getCurrentFrame() const
{
    if (m_frameCount == 0)
        return IntRect(0, 0, 0, 0);

    return m_frames[m_currentFrame];
}

void AnimationComponent::reset()
{
    m_currentFrame = 0;
    m_frameTimer = 0;
    m_finished = false;
}

bool AnimationComponent::isFinished() const
{
    return m_finished;
}