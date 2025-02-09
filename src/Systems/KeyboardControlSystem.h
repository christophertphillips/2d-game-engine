#ifndef KEYBOARDCONTROLSYSTEM_H
#define KEYBOARDCONTROLSYSTEM_H

#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Events/KeyPressedEvent.h"
#include "../Components/KeyboardControlledComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/RigidBodyComponent.h"

class KeyboardControlSystem: public System{
    public:
        KeyboardControlSystem(){
            RequireComponent<KeyboardControlledComponent>();                                                                // entity must have keyboard controlled component
            RequireComponent<SpriteComponent>();                                                                            // entity must have sprite component
            RequireComponent<RigidBodyComponent>();                                                                         // entity must have rigid body component
        }

        void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus){
            eventBus->SubscribeEventCallback<KeyboardControlSystem, KeyPressedEvent>(this, &KeyboardControlSystem::onKeyPressed); // subscribe onKeyPressed callback function pointer to event bus
        }

        void onKeyPressed(KeyPressedEvent& event){
            for(auto entity: GetSystemEntities()){
                const auto keyboardControlledComponent = entity.GetComponent<KeyboardControlledComponent>();                // get entity's keyboard controlled component
                auto& spriteComponent = entity.GetComponent<SpriteComponent>();                                             // get entity's sprite component
                auto& rigidBodyComponent = entity.GetComponent<RigidBodyComponent>();                                       // get entity's rigid body component

                switch(event.symbol){
                    case SDLK_UP:                                                                                           // UP key presed
                        rigidBodyComponent.velocity = keyboardControlledComponent.upVelocity;                               // set entity's rigid body component velocity to upVelocity
                        spriteComponent.srcRect.y = spriteComponent.height * 0;                                             // set entity's sprite component source rectangle to first row
                        break;
                    case SDLK_RIGHT:                                                                                        // DOWN key pressed
                        rigidBodyComponent.velocity = keyboardControlledComponent.rightVelocity;                            // set entity's rigid body component velocity to rightVelocity
                        spriteComponent.srcRect.y = spriteComponent.height * 1;                                             // set entity's sprite component source rectangle to second row
                        break;
                    case SDLK_DOWN:                                                                                         // RIGHT key pressed
                        rigidBodyComponent.velocity = keyboardControlledComponent.downVelocity;                             // set entity's rigid body component velocity to downVelocity
                        spriteComponent.srcRect.y = spriteComponent.height * 2;                                             // set entity's sprite component source rectangle to third row
                        break;
                    case SDLK_LEFT:                                                                                         // LEFT key pressed
                        rigidBodyComponent.velocity = keyboardControlledComponent.leftVelocity;                             // set entity's rigid body component velocity to leftVelocity
                        spriteComponent.srcRect.y = spriteComponent.height * 3;                                             // set entity's sprite component source rectangle to fourth row
                        break;
                }
            }
        }

        void Update() {

        }
};

#endif
