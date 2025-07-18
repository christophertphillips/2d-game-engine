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

        void Update(double deltaTime, double elapsedTime){
            for(auto entity: GetSystemEntities()){
                const auto scriptComponent = entity.GetComponent<ScriptComponent>();                                        // get entity's script component
                scriptComponent.func(entity, deltaTime, elapsedTime);                                                       // execute script function
            }
        }
};

#endif
