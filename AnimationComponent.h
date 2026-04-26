#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class AnimationComponent
{
public:
    static const int MAX_FRAMES = 24;

private:
    IntRect m_frames[MAX_FRAMES];
    int m_frameCount;
    int m_currentFrame;
    float m_frameDuration;
    float m_frameTimer;
    bool m_looping;
    bool m_finished;

public:
    AnimationComponent();
    void loadSprite(const IntRect* frames, int count, float frameDuration, bool looping = true);
    void update(float dt);
    IntRect getCurrentFrame() const;
    void reset();
    bool isFinished() const;
};