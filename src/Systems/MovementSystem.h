#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"

class MovementSystem: public System{
    public:
        MovementSystem(){
            RequireComponent<TransformComponent>();                                     // require transform component
            RequireComponent<RigidBodyComponent>();                                     // require rigid body component
        }

        void Update(){
            for(auto entity: GetSystemEntities()){
                auto& transformComponent = entity.GetComponent<TransformComponent>();       // get entity's transform component
                const auto rigidBodyComponent = entity.GetComponent<RigidBodyComponent>();  // get entity's rigid body component

                transformComponent.position.x += rigidBodyComponent.velocity.x;         // set entity x position using velocity x offset
                transformComponent.position.y += rigidBodyComponent.velocity.y;         // set entity y position using velocity y offset

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
