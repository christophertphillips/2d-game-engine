#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/AnimationComponent.h"
#include "../Components/SpriteComponent.h"
#include <SDL2/SDL.h>

class AnimationSystem: public System {
    public:
        AnimationSystem(){
            RequireComponent<AnimationComponent>();                                     // require animation component
            RequireComponent<SpriteComponent>();                                        // require sprite component
        }

        void Update(){
            for(auto entity: GetSystemEntities()){
                auto& animationComponent = entity.GetComponent<AnimationComponent>();   // get entity's animation component (ref)
                auto& spriteComponent = entity.GetComponent<SpriteComponent>();         // get ref to entity's sprite component (ref)

                // animationComponent.currentFrame = (((SDL_GetTicks() - animationComponent.startTime) * animationComponent.frameSpeedRate) / 1000) % animationComponent.numFrames;
                animationComponent.currentFrame = static_cast<int>(                                                 // cast frame calcuation to int (since frames must be discrete, whole numbers)
                    (SDL_GetTicks() - animationComponent.startTime) * (animationComponent.frameSpeedRate / 1000.0)  // calculate elapsed time and multiply by frame speed rate to determine current frame
                ) % animationComponent.numFrames;                                                                   // perform modulo to bound frame within [0, numFrames - 1]
                spriteComponent.srcRect.x = animationComponent.currentFrame * spriteComponent.width;                // offset source rectangle using current frame and sprite width
            }
        }
};

#endif
