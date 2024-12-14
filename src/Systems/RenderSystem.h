#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include <SDL2/SDL.h>
#include "../AssetStore/AssetStore.h"

class RenderSystem: public System {
    public:
        RenderSystem(){
            RequireComponent<TransformComponent>();                                     // require transform component
            RequireComponent<SpriteComponent>();                                        // require sprite component
        }

    void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetStore){
        for(auto entity: GetSystemEntities()){
            const auto transformComponent = entity.GetComponent<TransformComponent>();  // get entity's transform component
            const auto spriteComponent = entity.GetComponent<SpriteComponent>();        // get entity's sprite component

            SDL_Rect srcRect = spriteComponent.srcRect;                                 // get source rectangle for sprite

            SDL_Rect dstRect = {                                                        // create destination rectangle for sprite
                static_cast<int>(transformComponent.position.x),
                static_cast<int>(transformComponent.position.y),
                static_cast<int>(spriteComponent.width * transformComponent.scale.x),
                static_cast<int>(spriteComponent.height * transformComponent.scale.y)
            };

            SDL_Rect rect = {                                                           // set position, size of SDL rectangle
                static_cast<int>(transformComponent.position.x),
                static_cast<int>(transformComponent.position.y),
                spriteComponent.width,
                spriteComponent.height,
            };

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);                       // set color of SDL rectangle
            SDL_RenderFillRect(renderer, &rect);                                        // render SDL rectangle
        }
    }
};

#endif
