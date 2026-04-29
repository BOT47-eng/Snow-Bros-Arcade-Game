#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class AnimationComponent
{
public:
    static const int MAX_FRAMES = 24;

private:
    IntRect frames[MAX_FRAMES];
    int frameCount;
    int currentFrame;
    float frameDuration;
    float frameTimer;
    bool looping;
    bool finished;

public:
    AnimationComponent();
    void loadSprite(const IntRect* frames, int count, float frameDuration, bool looping = true);
    void update(float dt);
    IntRect getCurrentFrame() const;
    void reset();
    bool isFinished() const;
};