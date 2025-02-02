#ifndef EVENTBUS_H
#define EVENTBUS_H

#include "../Logger/Logger.h"
#include <map>
#include <typeindex>
#include <list>
#include "./Event.h"

class IEventCallback{
    private:
        virtual void Call(Event& e) = 0;

    public:
        virtual ~IEventCallback() = default;
        void Execute(Event& e){
            Call(e);                                                                                                        // invoke callback function via Call() in event-specific derived class
        };
};

template <typename TOwner, typename TEvent>
class EventCallback: public IEventCallback{
    private:
        typedef void (TOwner::*CallbackFunction)(TEvent&);                                                                  // type defintion for CallbackFunction (function pointer)
        TOwner* ownerInstance;                                                                                              // owner instance for callback function pointer
        CallbackFunction callbackFunction;                                                                                  // callback function pointer

        void Call(Event& e) override{
            std::invoke(callbackFunction, ownerInstance, static_cast<TEvent&>(e));                                          // invoke callback function using callback function pointer + owner instance and pass event reference as a parameter
        }

    public:
        EventCallback(TOwner* ownerInstance, CallbackFunction callbackFunction){
            this->ownerInstance = ownerInstance;
            this->callbackFunction = callbackFunction;
        }
        ~EventCallback() override = default;
};

typedef std::list<std::unique_ptr<IEventCallback>> EventCallbackList;                                                       // type definition for EventCallbackList (list of pointers to IEventCallback instances)

class EventBus {
    private:
        std::map<std::type_index, std::unique_ptr<EventCallbackList>> subscribers;                                          // map containing EventCallbackLists containing EventCallbacks wrapping callback funtion pointers (which are subscribed for the current frame)

    public:
        EventBus(){
            Logger::Log("EventBus constructor called!");
        }

        ~EventBus(){
            Logger::Log("EventBus destructor called!");
        }

        void Reset(){
            subscribers.clear();                                                                                            // refresh and clear subscribers map (before subscribing new callbacks)
        }

        template <typename TOwner, typename TEvent>
        void SubscribeEventCallback(TOwner* ownerInstance, void (TOwner::*callbackFunction)(TEvent&)){
            if(!subscribers[typeid(TEvent)].get()){                                                                         // if an EventCallbackList doesn't already exist for the event type TEvent in the subscribers map...
                subscribers[typeid(TEvent)] = std::make_unique<EventCallbackList>();                                        // ... then create a new EventCallbackList for TEvent
            }

            auto callbackToSubscribe = std::make_unique<EventCallback<TOwner, TEvent>>(ownerInstance, callbackFunction);    // wrap callback function pointer in an EventCallback
            subscribers[typeid(TEvent)]->push_back(std::move(callbackToSubscribe));                                         // add EventCallback to EventCallbackList associated with event type TEvent (using move to change unique_ptr owner)
        }

        template <typename TEvent, typename ...TArgs>
        void EmitEvent(TArgs&& ...args){
            auto eventCallbackPtrs = subscribers[typeid(TEvent)].get();                                                     // get EventCallbackList pointer associated with event type TEvent (EventCallbackList*)

            if(eventCallbackPtrs){                                                                                          // if there are event callbacks for the event type TEvent...
                for(auto itr = eventCallbackPtrs->begin(); itr != eventCallbackPtrs->end(); itr++){                         // ... then execute them all, one by one
                    auto eventCallbackPtr = itr->get();                                                                     // get EventCallback pointer (IEventCallback*)

                    TEvent event(std::forward<TArgs>(args)...);                                                             // create event of type TEvent, passing all necessary arguments
                    eventCallbackPtr->Execute(event);                                                                       // pass event to callback and execute the callback
                }
            }
        }
};

#endif
