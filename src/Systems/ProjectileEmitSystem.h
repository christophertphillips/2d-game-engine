#ifndef PROJECTILEEMITSYSTEM_H
#define PROJECTILEEMITSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/ProjectileComponent.h"
#include "../EventBus/EventBus.h"
#include "../Events/KeyPressedEvent.h"
#include "../Components/CameraFollowComponent.h"
#include <SDL2/SDL.h>

class ProjectileEmitSystem: public System{
    public:
        ProjectileEmitSystem(){
            RequireComponent<ProjectileEmitterComponent>();                                                                 // entity must have projectile emitter component
            RequireComponent<TransformComponent>();                                                                         // entity must have transform component
        }

        void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus){
            eventBus->SubscribeEventCallback<ProjectileEmitSystem, KeyPressedEvent>(this, &ProjectileEmitSystem::OnKeyPressed);
        }

        void OnKeyPressed(KeyPressedEvent& event){
            if(event.symbol == SDLK_SPACE){                                                                                 // if space was pressed...
                for(auto entity: GetSystemEntities()){
                    if(entity.HasComponent<CameraFollowComponent>()){                                                       // if the entity is the chopper...

                        const auto projectileEmitterComponent = entity.GetComponent<ProjectileEmitterComponent>();          // get entity's projectile emitter component
                        const auto transformComponent = entity.GetComponent<TransformComponent>();                          // get entity's transform component
                        const auto rigidBodyComponent = entity.GetComponent<RigidBodyComponent>();                          // get entity's rigid body component

                        Entity projectile = entity.registry->CreateEntity();                                                // add projectile entity (NOTE: all entities have a pointer to the registry object)

                        glm::vec2 projectilePosition = transformComponent.position;                                         // set projectile position to entity's position (via its transform component)
                        if(entity.HasComponent<SpriteComponent>()){                                                         // if entity has a sprite component...
                            const auto spriteComponent = entity.GetComponent<SpriteComponent>();                            // get entity's sprite component
                            projectilePosition.x += (spriteComponent.width / 2);                                            // offset projectile x position to sprite x-midpoint
                            projectilePosition.y += (spriteComponent.height / 2);                                           // offset projectile y position to sprite y-midpoint
                        }

                        glm::vec2 projectileVelocity = projectileEmitterComponent.projectileVelocity;                       // set projectile velocity (via projectile emitter component)
                        int xMult = 0;                                                                                      // create multipliers for x, y directions
                        int yMult = 0;
                        if(rigidBodyComponent.velocity.x > 0) xMult = 1;                                                    // set multiplier according to the direction of the entity's velocity (via its rigid body component)
                        if(rigidBodyComponent.velocity.x < 0) xMult = -1;
                        if(rigidBodyComponent.velocity.y > 0) yMult = 1;
                        if(rigidBodyComponent.velocity.y < 0) yMult = -1;
                        projectileVelocity.x *= xMult;                                                                      // apply multipliers to projectile velocity
                        projectileVelocity.y *= yMult;

                        projectile.AddComponent<TransformComponent>(projectilePosition, glm::vec2(1.0, 1.0), 0.0);          // add transform component to projectile entity
                        projectile.AddComponent<RigidBodyComponent>(projectileVelocity);                                    // add rigid body component to projectile entity
                        projectile.AddComponent<SpriteComponent>("bullet-image", 4, 4, 4);                                  // add sprite component to projectile entity
                        projectile.AddComponent<BoxColliderComponent>(4, 4);                                                // add box collider component to projectile entity
                        projectile.AddComponent<ProjectileComponent>(projectileEmitterComponent.isFriendly, projectileEmitterComponent.hitPercentDamage, projectileEmitterComponent.projectileDuration);    // add projectile component to projectile entity
                    }
                }
            }
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
                    projectile.AddComponent<ProjectileComponent>(projectileEmitterComponent.isFriendly, projectileEmitterComponent.hitPercentDamage, projectileEmitterComponent.projectileDuration);    // add projectile component to projectile entity

                    projectileEmitterComponent.lastEmissionTime = SDL_GetTicks();                                           // reset projectile component's last emission time to the current time
                }
            }
        }
};

#endif
