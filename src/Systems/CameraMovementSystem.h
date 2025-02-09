#ifndef CAMERAMOVEMENTSYSTEM_H
#define CAMERAMOVEMENTSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/TransformComponent.h"
#include "../Game/Game.h"
#include <SDL2/SDL.h>

class CameraMovementSystem: public System{
    public:
        CameraMovementSystem(){
            RequireComponent<CameraFollowComponent>();                                                                      // entity must have camera follow component
            RequireComponent<TransformComponent>();                                                                         // entity must have transform component
        }

        void Update(SDL_Rect& camera){
            for(auto entity: GetSystemEntities()){
                auto transformComponent = entity.GetComponent<TransformComponent>();                                        // get entity's transform component

                int cameraCalcXPos = static_cast<int>(transformComponent.position.x) - (camera.w / 2);                      // calculate camera's x position (such that entity is centered inside camera)
                int cameraCalcYPos = static_cast<int>(transformComponent.position.y) - (camera.h / 2);                      // calculate camera's y position (such that entity is centered inside camera)

                camera.x = std::min((Game::fieldWidth - camera.w), std::max(0, cameraCalcXPos));                            // clamp camera's new x position (cameraXPos) on (0, cameraXPosMax)
                camera.y = std::min((Game::fieldHeight - camera.h), std::max(0, cameraCalcYPos));                           // clamp camera's new y position (cameraYPos) on (0, cameraYPosMax)
            }
        }
};

#endif
