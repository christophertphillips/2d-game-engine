#include "ECS.h"
#include "../Logger/Logger.h"

int IComponent::nextId = 0;

int Entity::GetId() const {                                                             // (const indicates method doesn't change members)
    return id;                                                                          // return entity's id
}

void System::AddEntityToSystem(Entity entity){
    entities.push_back(entity);                                                         // add entity to system's entities vector
};

void System::RemoveEntityFromSystem(Entity entity){
    // my original implementation
    // for(int index = 0; index < entities.size(); index++){
    //     if(entities.at(index).GetId() == entity.GetId()){
    //         entities.erase(entities.begin()+index);
    //         return;
    //     }
    // }
    entities.erase(                                                                     // removes entity using returned iterator and iterator of last element
        std::remove_if(                                                                 // returns iterator to first matching elmenet (in this case, only one is possible)
            entities.begin(),
            entities.end(),
            [&entity](Entity other) { return entity == other; }                         // lambda function that matches 'other' entity to 'entity' entity
        ),
        entities.end()                                                                  // iterator of last element
    );
};

std::vector<Entity> System::GetSystemEntities() const{
    return entities;                                                                    // return vector of entities associated with system
};

const Signature& System::GetComponentSignature() const{
    return componentSignature;                                                          // return signature indicating which components are required by the system
};

Entity Registry::createEntity(){
    int entityId = numEntities++;                                                       // generate entity id
    Entity entity(entityId);                                                            // create entity (on stack)
    entitiesToBeAdded.insert(entity);                                                   // add entity to entitiesToBeAdded set
    Logger::Log("Entity created with id = " + std::to_string(entityId));                // log entity creation message
    return entity;                                                                      // return (copy of) entity
};

void Registry::AddEntityToSystems(Entity entity){                                       // add entity to *all* systems that are interested in that entity
    const auto entityId = entity.GetId();                                               // get entity id of specified entity
    const auto& entityComponentSignature = entityComponentSignatures[entityId];         // get component signature associated with specified entity

    for (auto& systemsRef: systems){                                                    // loop through each system
        const auto& systemComponentSignature = systemsRef.second->GetComponentSignature();  // get the component signature associated with systemsRef

        bool isInterested = (entityComponentSignature & systemComponentSignature) == systemComponentSignature; // return bool result indicating whether systemRef is interested in specified entity

        if (isInterested){                                                              // if system is intereted in entity...
            systemsRef.second->AddEntityToSystem(entity);                               // ... then add entity to system
        }
    }
}
