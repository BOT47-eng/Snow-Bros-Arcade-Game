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
    IntRect getSepcificFrame(int  n) const 
    {
        if(n < frameCount)
            return frames[n] ; 
        
        return {0 , 0  , 0, 0} ;
    }
    int getCurrentFrameIndex() const {return currentFrame ;}
    void setCurrentFrameIndex(int n ) {currentFrame = n ;}
};