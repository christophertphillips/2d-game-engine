#ifndef RENDERCOLLISIONSYSTEM_H
#define RENDERCOLLISIONSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/TransformComponent.h"
#include <SDL2/SDL.h>

class RenderCollisionSystem: public System{
    public:
        RenderCollisionSystem(){
            RequireComponent<TransformComponent>();                                                                             // entity must have transform component
            RequireComponent<BoxColliderComponent>();                                                                           // entity must have box collider component
        }

        void Update(SDL_Renderer* renderer){
            for(auto entity: GetSystemEntities()){                                                                              // iterate through all entities associated with system
                auto transformComponent = entity.GetComponent<TransformComponent>();                                            // get entity's transform component
                auto boxColliderComponent = entity.GetComponent<BoxColliderComponent>();                                        // get entity's box collider component

                SDL_Rect rect = {                                                                                               // create rectangle for entity's box collider
                    static_cast<int>(transformComponent.position.x + boxColliderComponent.offset.x),
                    static_cast<int>(transformComponent.position.y + boxColliderComponent.offset.y),
                    boxColliderComponent.width,
                    boxColliderComponent.height,
                };

                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);                                                               // set rectangle color to red
                SDL_RenderDrawRect(renderer, &rect);                                                                            // draw rectangle for entity's box collider
            }
        }
};

#endif
