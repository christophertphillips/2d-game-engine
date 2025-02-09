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
            std::string keyCode = std::to_string(event.symbol);                                                             // extract key code from KeyPressed event (SDL Keycode)
            std::string keySymbol(1, event.symbol);                                                                         // extract key symbol from KeyPressed event (SDL Keycode)
            Logger::Log("Key pressed event emitted: [" + keyCode + "] " + keySymbol);                                         // log key code + key symbol to logger
        }

        void Update() {

        }
};

#endif
