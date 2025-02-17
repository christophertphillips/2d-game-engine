#ifndef PROJECTILEEMITSYSTEM_H
#define PROJECTILEEMITSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/BoxColliderComponent.h"
#include <SDL2/SDL.h>

class ProjectileEmitSystem: public System{
    public:
        ProjectileEmitSystem(){
            RequireComponent<ProjectileEmitterComponent>();                                                                 // entity must have projectile emitter component
            RequireComponent<TransformComponent>();                                                                         // entity must have transform component
        }

        void Update(std::unique_ptr<Registry>& registry){
            for(auto entity: GetSystemEntities()){
                auto& projectileEmitterComponent = entity.GetComponent<ProjectileEmitterComponent>();                       // get entity's projectile emitter component
                const auto transformComponent = entity.GetComponent<TransformComponent>();                                  // get entity's transform component

                if((SDL_GetTicks() - projectileEmitterComponent.lastEmissionTime) > projectileEmitterComponent.repeatFrequency){    // if the time elapsed since the last emission is greater than the repeat frequency...
                    Entity projectile = registry->CreateEntity();                                                           // add projectile entity

                    glm::vec2 projectilePosition = transformComponent.position;                                             // set projectile position to entity's position (via its transform component)
                    if(entity.HasComponent<SpriteComponent>()){                                                             // if entity has a sprite component...
                        const auto spriteComponent = entity.GetComponent<SpriteComponent>();                                // get entity's sprite component
                        projectilePosition.x += (spriteComponent.width / 2);                                                // offset projectile x position to sprite x-midpoint
                        projectilePosition.y += (spriteComponent.height / 2) + 16;                                          // offset projectile y position to sprite y-midpoint (NOTE: remove + 16 later)
                    }

                    projectile.AddComponent<TransformComponent>(projectilePosition, glm::vec2(1.0, 1.0), 0.0);              // add transform component to projectile entity
                    projectile.AddComponent<RigidBodyComponent>(projectileEmitterComponent.projectileVelocity);             // add rigid body component to projectile entity
                    projectile.AddComponent<SpriteComponent>("bullet-image", 4, 4, 4);                                      // add sprite component to projectile entity
                    projectile.AddComponent<BoxColliderComponent>(4, 4);                                                    // add box collider component to projectile entity

                    projectileEmitterComponent.lastEmissionTime = SDL_GetTicks();                                           // reset projectile component's last emission time to the current time
                }
            }
        }
};

#endif
