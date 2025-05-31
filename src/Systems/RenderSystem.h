#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include <SDL2/SDL.h>
#include "../AssetStore/AssetStore.h"
#include <algorithm>

class RenderSystem: public System {
    public:
        RenderSystem(){
            RequireComponent<TransformComponent>();                                     // require transform component
            RequireComponent<SpriteComponent>();                                        // require sprite component
        }

    void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetStore, SDL_Rect& camera){
        std::vector<Entity> entities = GetSystemEntities();                             // get all entities associated with system
        std::vector<Entity> onscreenEntities;                                                                               // create vector to hold onscreen (non-culled) entities

        std::copy_if(entities.begin(), entities.end(), std::back_inserter(onscreenEntities), [&camera](Entity& entity) {    // cull offscreen entities
            const auto transformComponent = entity.GetComponent<TransformComponent>();                                      // get entity's transform component
            const auto spriteComponent = entity.GetComponent<SpriteComponent>();                                            // get entity's sprite component
            return spriteComponent.isFixed || !(                                                                            // return true if fixed or inside screen bounds
                transformComponent.position.x + (spriteComponent.width * transformComponent.scale.x) < camera.x ||          // determine if entity is beyond field boundary (west)
                transformComponent.position.x > camera.x + camera.w ||                                                      // determine if entity is beyond field boundary (east)
                transformComponent.position.y + (spriteComponent.height * transformComponent.scale.y) < camera.y ||         // determine if entity is beyond field boundary (north)
                transformComponent.position.y > camera.y + camera.h                                                         // determine if entity is beyond field boundary (south)
            );
        });

        std::sort(onscreenEntities.begin(), onscreenEntities.end(), [](Entity& entity0, Entity& entity1){                   // sort (onscreen) entities by ascending z-index
            return entity0.GetComponent<SpriteComponent>().zIndex < entity1.GetComponent<SpriteComponent>().zIndex;
        });

        for(auto entity: onscreenEntities){                                             // iterate through all (sorted, onscreen) entities associated with system
            const auto transformComponent = entity.GetComponent<TransformComponent>();  // get entity's transform component
            const auto spriteComponent = entity.GetComponent<SpriteComponent>();        // get entity's sprite component

            SDL_Rect srcRect = spriteComponent.srcRect;                                 // get source rectangle for sprite

            SDL_Rect dstRect = {                                                        // create destination rectangle for sprite
                static_cast<int>(transformComponent.position.x - (spriteComponent.isFixed ? 0 : camera.x)), // set destination rectangle x position, adjusting relative to camera x position
                static_cast<int>(transformComponent.position.y - (spriteComponent.isFixed ? 0 : camera.y)), // set destination rectangle y position, adjusting relative to camera y position
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
                spriteComponent.flip                                                    // sprite flipping
            );
        }
    }
};

#endif
