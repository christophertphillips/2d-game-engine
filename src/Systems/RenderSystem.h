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

    void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetStore, SDL_Rect& camera){
        std::vector<Entity> entities = GetSystemEntities();                             // get all entities associated with system
        std::sort(entities.begin(), entities.end(), [](Entity& entity0, Entity& entity1){   // sort entities by ascending z-index
            return entity0.GetComponent<SpriteComponent>().zIndex < entity1.GetComponent<SpriteComponent>().zIndex;
        });

        for(auto entity: entities){                                                     // iterate through all (sorted) entities associated with system
            const auto transformComponent = entity.GetComponent<TransformComponent>();  // get entity's transform component
            const auto spriteComponent = entity.GetComponent<SpriteComponent>();        // get entity's sprite component

            SDL_Rect srcRect = spriteComponent.srcRect;                                 // get source rectangle for sprite

            SDL_Rect dstRect = {                                                        // create destination rectangle for sprite
                static_cast<int>(transformComponent.position.x - camera.x),             // set destination rectangle x position, adjusting relative to camera x position
                static_cast<int>(transformComponent.position.y - camera.y),             // set destination rectangle y position, adjusting relative to camera y position
                static_cast<int>(spriteComponent.width * transformComponent.scale.x),
                static_cast<int>(spriteComponent.height * transformComponent.scale.y)
            };

            SDL_RenderCopyEx(
                renderer,                                                               // renderer (SDL renderer pointer)
                assetStore->GetTexture(spriteComponent.assetId),                        // id for asset to display as sprite (string)
                &srcRect,                                                               // source rectangle (SDL rectangle pointer)
                &dstRect,                                                               // destination rectangle (SDL rectangle pointer)
                transformComponent.rotation,                                            // angle of rotation (double)
                NULL,                                                                   // center of rotation (NULL == cetroid of sprite)
                SDL_FLIP_NONE                                                           // sprite flipping (none specified)
            );
        }
    }
};

#endif
