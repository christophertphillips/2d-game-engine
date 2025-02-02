#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/TransformComponent.h"
#include <iostream>
#include "../EventBus/EventBus.h"
#include "../Events/CollisionEvent.h"

class CollisionSystem: public System{
    public:
        CollisionSystem(){
            RequireComponent<BoxColliderComponent>();
            RequireComponent<TransformComponent>();
        }

        void Update(std::unique_ptr<EventBus>& eventBus){
            std::vector<Entity> entities = GetSystemEntities();                                                             // get all entities associated with system

            for(auto aEntityPointer = entities.begin(); aEntityPointer != entities.end(); aEntityPointer++){                // iterate pointer A across all entities
                auto aEntity = *aEntityPointer;                                                                             // get entity A

                auto aTransformComponent = aEntity.GetComponent<TransformComponent>();                                      // get entity A's transform component
                auto aColliderComponent = aEntity.GetComponent<BoxColliderComponent>();                                     // get entity A's box collider component

                for(auto bEntityPointer = aEntityPointer + 1; bEntityPointer != entities.end(); bEntityPointer++){          // iterate pointer B across all entities to the right of pointer A
                    auto bEntity = *bEntityPointer;                                                                         // get entity B

                    auto bTransformComponent = bEntity.GetComponent<TransformComponent>();                                  // get entity B's transform component
                    auto bColliderComponent = bEntity.GetComponent<BoxColliderComponent>();                                 // get entity B's box collider component

                    bool result = checkAABBCollision(                                                                       // check collision between entity A and entity B
                        aTransformComponent.position.x + aColliderComponent.offset.x,
                        aTransformComponent.position.y + aColliderComponent.offset.y,
                        aColliderComponent.width,
                        aColliderComponent.height,
                        bTransformComponent.position.x + bColliderComponent.offset.x,
                        bTransformComponent.position.y + bColliderComponent.offset.y,
                        bColliderComponent.width,
                        bColliderComponent.height
                    );

                    if(result){
                        Logger::Log("Collision occurred between entity " + std::to_string(aEntity.GetId()) + " and entity " + std::to_string(bEntity.GetId()));

                        eventBus->EmitEvent<CollisionEvent>(aEntity, bEntity);                                              // emit collision event between entity A and entity B
                    }
                }
            }

            // while(not entities.empty()){                                                                                 // original implementation
            //     auto aEntity = entities[0];
            //     entities.erase(entities.begin());

            //     auto aTransformComponent = aEntity.GetComponent<TransformComponent>();
            //     auto aColliderComponent = aEntity.GetComponent<BoxColliderComponent>();

            //     for(auto bEntity: entities){
            //         auto bTransformComponent = bEntity.GetComponent<TransformComponent>();
            //         auto bColliderComponent = bEntity.GetComponent<BoxColliderComponent>();

            //         ...
            //     }
            // }
        }

        bool checkAABBCollision(
            double aX,
            double aY,
            double aWidth,
            double aHeight,
            double bX,
            double bY,
            double bWidth,
            double bHeight
        ){
            return (                                                                    // perform AABB collision check
                (aX           < bX + bWidth ) &&
                (aX + aWidth  > bX          ) &&
                (aY           < bY + bHeight) &&
                (aY + aHeight > bY          )
            );
        }
};

#endif
