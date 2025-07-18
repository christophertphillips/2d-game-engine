#ifndef SCRIPTSYSTEM
#define SCRIPTSYSTEM

#include "../ECS/ECS.h"
#include "../Components/ScriptComponent.h"
#include "../Logger/Logger.h"

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

            lua.set_function("set_entity_position", &SetEntityPosition);                                                    // bind Lua function set_entity_position to C++ function SetEntityPosition
        }

        void Update(double deltaTime, double elapsedTime){
            for(auto entity: GetSystemEntities()){
                const auto scriptComponent = entity.GetComponent<ScriptComponent>();                                        // get entity's script component
                scriptComponent.func(entity, deltaTime, elapsedTime);                                                       // execute script function
            }
        }
};

#endif
