#ifndef DAMAGESYSTEM_H
#define DAMAGESYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/BoxColliderComponent.h"
#include "../EventBus/EventBus.h"
#include "../Events/CollisionEvent.h"

class DamageSystem: public System{
    public:
        DamageSystem(){
            RequireComponent<BoxColliderComponent>();                                                                       // require box collider component
        }

        void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus){
            eventBus->SubscribeEventCallback<DamageSystem, CollisionEvent>(this, &DamageSystem::onCollision);               // subscribe onCollision callback function pointer to event bus
        }

        void onCollision(CollisionEvent& event){
            Logger::Log("The damage system received a collision event between entities " + std::to_string(event.a.GetId()) + " and " + std::to_string(event.b.GetId()));
            event.a.KillEntity();                                                                                           // kill entity a
            event.b.KillEntity();                                                                                           // kill entity b
        }

        void Update(){

        }
};

#endif
