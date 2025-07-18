#ifndef SCRIPTSYSTEM
#define SCRIPTSYSTEM

#include "../ECS/ECS.h"
#include "../Components/ScriptComponent.h"

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
