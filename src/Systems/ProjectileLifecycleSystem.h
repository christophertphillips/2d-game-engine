#ifndef PROJECTILELIFECYCLESYSTEM_H
#define PROJECTILELIFECYCLESYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/ProjectileComponent.h"

class ProjectileLifecycleSystem: public System{
    public:
        ProjectileLifecycleSystem(){
            RequireComponent<ProjectileComponent>();                                                                        // entity must have projectile component
        }

        void Update(){
            for(auto entity: GetSystemEntities()){
                auto projectileComponent = entity.GetComponent<ProjectileComponent>();                                      // get entity's projectile component

                if((SDL_GetTicks() - projectileComponent.startTime) > projectileComponent.duration){                        // if the time elapsed since the projectile's start time is greater than its duration...
                    entity.KillEntity();                                                                                    // kill the (projectile) entity
                }
            }
        }
};

#endif
