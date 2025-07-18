#ifndef SCRIPTSYSTEM
#define SCRIPTSYSTEM

#include "../ECS/ECS.h"
#include "../Components/ScriptComponent.h"
#include "../Logger/Logger.h"

std::tuple<double, double> GetEntityPosition(Entity entity){
    if(entity.HasComponent<TransformComponent>()){                                                                          // if entity has a transform component....
        const auto transformComponent = entity.GetComponent<TransformComponent>();                                          // get entity's transform component
        return std::make_tuple(transformComponent.position.x, transformComponent.position.y);                               // return tuple containing transform component x, y position
    }
    else{
        Logger::Err("Trying to get the position of an entity via Lua that has no transform component.");                    // ... else, log error message
        return std::make_tuple(0.0, 0.0);                                                                                   // return (0.0, 0.0) tuple
    }
}

std::tuple<double, double> GetEntityVelocity(Entity entity){
    if(entity.HasComponent<RigidBodyComponent>()){                                                                          // if entity has a rigid body component....
        const auto rigidBodyComponent = entity.GetComponent<RigidBodyComponent>();                                          // get entity's rigid body component
        return std::make_tuple(rigidBodyComponent.velocity.x, rigidBodyComponent.velocity.y);                               // return tuple containing rigid body component x, y position
    }
    else{
        Logger::Err("Trying to get the velocity of an entity via Lua that has no rigid body component.");                   // ... else, log error message
        return std::make_tuple(0.0, 0.0);                                                                                   // return (0.0, 0.0) tuple
    }
}

void SetEntityPosition(Entity entity, double x, double y){
    if(entity.HasComponent<TransformComponent>()){                                                                          // if entity has a transform component....
        auto& transformComponent = entity.GetComponent<TransformComponent>();                                               // get entity's transform component
        transformComponent.position.x = x;                                                                                  // set entity's x position
        transformComponent.position.y = y;                                                                                  // set entity's y position
    }
    else{
        Logger::Err("Trying to set the position of an entity via Lua that has no transform component.");                    // ... else, log errror message
    }
}

void SetEntityVelocity(Entity entity, double x, double y){
    if(entity.HasComponent<RigidBodyComponent>()){                                                                          // if entity has a rigid body component....
        auto& rigidBodyComponent = entity.GetComponent<RigidBodyComponent>();                                               // get entity's rigid body component
        rigidBodyComponent.velocity.x = x;                                                                                  // set entity's x velocity
        rigidBodyComponent.velocity.y = y;                                                                                  // set entity's x velocity
    }
    else{
        Logger::Err("Trying to set the velocity of an entity via Lua that has no rigid body component.");                   // .. else, log error message
    }
}

void SetEntityRotation(Entity entity, double angle){
    if(entity.HasComponent<TransformComponent>()){                                                                          // if entity has a transform component....
        auto& transformComponent = entity.GetComponent<TransformComponent>();                                               // get entity's transform component
        transformComponent.rotation = angle;                                                                                // set entity's rotation angle
    }
    else{
        Logger::Err("Trying to set the rotation of an entity via Lua that has no transform component.");                    // ... else, log error message
    }
}

void SetEntityAnimationFrame(Entity entity, int frame){
    if(entity.HasComponent<AnimationComponent>()){                                                                          // if entity has an animation component...
        auto& animationComponent = entity.GetComponent<AnimationComponent>();                                               // get entity's animation component
        animationComponent.currentFrame = frame;                                                                            // set entity's animation frame
    }
    else{
        Logger::Err("Trying to set the frame of an entity via Lua that has no animation component.");                       // ... else, log error messsage
    }
}

void SetEntityProjectileEmitterVelocity(Entity entity, double x, double y){
    if(entity.HasComponent<ProjectileEmitterComponent>()){                                                                  // if entity has a projectile emittter component...
        auto& projectileEmitterComponent = entity.GetComponent<ProjectileEmitterComponent>();                               // get entity's projectile emitter component
        projectileEmitterComponent.projectileVelocity.x = x;                                                                // set entity's x projectile velocity
        projectileEmitterComponent.projectileVelocity.y = y;                                                                // set entity's y projectile velocity
    }
    else{
        Logger::Err("Trying to set the projectile emitter velocity of an entity via Lua that has no projectile emitter component.");    // else, log error message
    }
}


class ScriptSystem: public System {
    public:
        ScriptSystem(){
            RequireComponent<ScriptComponent>();                                                                            // entity must have script component
        }

        void CreateLuaBindings(sol::state& lua){
            lua.new_usertype<Entity>(                                                                                       // inform Lua about Entity (the C++ tpye)
                "entity",                                                                                                   // name Lua usertime entity
                "get_id", &Entity::GetId,                                                                                   // make Entity::GetId available to use in Lua
                "kill_entity", &Entity::KillEntity,                                                                         // make Entity::KillEntity available to use in Lua
                "has_tag", &Entity::HasTag,                                                                                 // make Entity::HasTag available to use in Lua
                "belongs_to_group", &Entity::BelongsToGroup                                                                 // make Entity::Belongs available to use in Lua
            );

            lua.set_function("get_entity_position", &GetEntityPosition);                                                    // bind Lua function get_entity_position to C++ function GetEntityPosition
            lua.set_function("get_entity_velocity", &GetEntityVelocity);                                                    // bind Lua function get_entity_velocity to C++ function GetEntityVelocity
            lua.set_function("set_entity_position", &SetEntityPosition);                                                    // bind Lua function set_entity_position to C++ function SetEntityPosition
            lua.set_function("set_entity_velocity", &SetEntityVelocity);                                                    // bind Lua function set_entity_velocity to C++ function SetEntityVelocity
            lua.set_function("set_entity_rotation", &SetEntityRotation);                                                    // bind Lua function set_entity_rotation to C++ function SetEntityRotation
            lua.set_function("set_entity_animation_framet", &SetEntityAnimationFrame);                                      // bind Lua function set_entity_animation_framet to C++ function SetEntityAnimationFrame
            lua.set_function("set_entity_projectile_emitter_velocity", &SetEntityProjectileEmitterVelocity);                // bind Lua function set_entity_projectile_emitter_velocity to C++ function SetEntityProjectileEmitterVelocity
        }

        void Update(double deltaTime, double elapsedTime){
            for(auto entity: GetSystemEntities()){
                const auto scriptComponent = entity.GetComponent<ScriptComponent>();                                        // get entity's script component
                scriptComponent.func(entity, deltaTime, elapsedTime);                                                       // execute script function
            }
        }
};

#endif
