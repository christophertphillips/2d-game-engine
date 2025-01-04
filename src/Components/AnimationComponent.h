#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include <SDL2/SDL.h>

struct AnimationComponent {
    int numFrames;
    int currentFrame;
    int frameSpeedRate;
    bool isLoop;
    int startTime;

    AnimationComponent(int numFrames = 1, int frameSpeedRate = 1, bool isLoop = true){
        this->numFrames = numFrames;
        this->currentFrame = 0;                                                         // set initial current frame to frame 0
        this->frameSpeedRate = frameSpeedRate;
        this->isLoop = isLoop;
        this->startTime = SDL_GetTicks();                                               // set start time to current SDL ticks
    }
};

#endif
