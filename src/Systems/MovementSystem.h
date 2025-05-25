#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../EventBus/EventBus.h"
#include "../Events/CollisionEvent.h"

class MovementSystem: public System{
    public:
        MovementSystem(){
            RequireComponent<TransformComponent>();                                     // require transform component
            RequireComponent<RigidBodyComponent>();                                     // require rigid body component
        }

        void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus){
            eventBus->SubscribeEventCallback<MovementSystem, CollisionEvent>(this, &MovementSystem::onCollision);           // subscribe onCollision callback function pointer to event bus
        }

        void onCollision(CollisionEvent& event){
            Entity aEntity = event.a;                                                                                       // get entity a from event
            Entity bEntity = event.b;                                                                                       // get entity b from event

            if(aEntity.BelongsToGroup("obstacles") && bEntity.BelongsToGroup("enemies")){                                   // did an enemy collide with an obstacle?
                onEnemyHitsObstacle(aEntity, bEntity);                                                                      // if yes, call onEnemyHitsObstacle()
            }
            else if(bEntity.BelongsToGroup("obstacles") && aEntity.BelongsToGroup("enemies")){                              // (same as above)
                onEnemyHitsObstacle(bEntity, aEntity);                                                                      // (same as above)
            }
        }

        void onEnemyHitsObstacle(Entity obstacle, Entity enemy){
            if(enemy.HasComponent<RigidBodyComponent>() && enemy.HasComponent<SpriteComponent>()){                          // if enemy has a rigid body component and sprite component...

                auto& rigidBodyComponent = enemy.GetComponent<RigidBodyComponent>();                                        // get enemy's rigid body component
                auto& spriteComponent = enemy.GetComponent<SpriteComponent>();                                              // get enemy's sprite component

                if(rigidBodyComponent.velocity.x != 0){                                                                     // if enemy's x velocity is nonzero...
                    rigidBodyComponent.velocity.x *= -1;                                                                    // ... reverse x velocity
                    spriteComponent.flip = (spriteComponent.flip == SDL_FLIP_NONE ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);   // ... flip sprite horizontally
                }

                if(rigidBodyComponent.velocity.y != 0){                                                                     // if enemy's y velocity is nonzero...
                    rigidBodyComponent.velocity.y *= -1;                                                                    // ... reverse y velocity
                    spriteComponent.flip = (spriteComponent.flip == SDL_FLIP_NONE ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE);     // ... flip sprite horizontally
                }
            }
        }

        void Update(double deltaTime){
            for(auto entity: GetSystemEntities()){
                auto& transformComponent = entity.GetComponent<TransformComponent>();       // get entity's transform component
                const auto rigidBodyComponent = entity.GetComponent<RigidBodyComponent>();  // get entity's rigid body component

                transformComponent.position.x += rigidBodyComponent.velocity.x * deltaTime; // set entity x position using velocity x offset
                transformComponent.position.y += rigidBodyComponent.velocity.y * deltaTime; // set entity y position using velocity y offset

                int xOffset = (entity.HasComponent<SpriteComponent>() ? entity.GetComponent<SpriteComponent>().width  : 0); // calculate horizontal sprite offset
                int yOffset = (entity.HasComponent<SpriteComponent>() ? entity.GetComponent<SpriteComponent>().height : 0); // calculate vertical sprite offset

                bool isOutsideMapW = transformComponent.position.x < 0;                                                     // determine if entity is beyond field boundary (west)
                bool isOutsideMapE = transformComponent.position.x > Game::fieldWidth - xOffset;                            // determine if entity is beyond field boundary (east)
                bool isOutsideMapN = transformComponent.position.y < 0;                                                     // determine if entity is beyond field boundary (north)
                bool isOutsideMapS = transformComponent.position.y > Game::fieldHeight - yOffset;                           // determine if entity is beyond field boundary (south)
                bool isOutsideMap = ( isOutsideMapW || isOutsideMapE || isOutsideMapN | isOutsideMapS );                    // determine if entity is beyond field boundary (any)

                if(isOutsideMap && !entity.HasTag("player")){                                                               // if entity is outside map bounds and is not the player...
                    entity.KillEntity();                                                                                    // ... kill the entity
                }

                // Logger::Log(
                //     "Entity id = " +
                //     std::to_string(entity.GetId()) +
                //     " position is now (" +
                //     std::to_string(transformComponent.position.x) +
                //     ", " +
                //     std::to_string(transformComponent.position.y) +
                //     ")"
                // );
            }
        }
};

#endif
