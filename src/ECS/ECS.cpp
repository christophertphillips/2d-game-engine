#include "ECS.h"
#include "../Logger/Logger.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Component

int IComponent::nextId = 0;

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Entity

int Entity::GetId() const {                                                             // (const indicates method doesn't change members)
    return id;                                                                          // return entity's id
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// System

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

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Registry

Entity Registry::CreateEntity(){
    int entityId = numEntities++;                                                       // generate entity id
    Entity entity(entityId);                                                            // create entity (on stack)
    entity.registry = this;                                                             // set Entity's registry member to point to registry object
    entitiesToBeAdded.insert(entity);                                                   // add entity to entitiesToBeAdded set

    if(entityId >= entityComponentSignatures.size()){                                   // if entity's component signature can't fit in entityComponentSignatures...
        entityComponentSignatures.resize(entityId + 1);                                 // ... increase entityComponentSignatures size by 1
    }

    Logger::Log("Entity created with id = " + std::to_string(entityId));                // log entity creation message
    return entity;                                                                      // return (copy of) entity
};

void Registry::KillEntity(Entity entity){                                               // remove entity from registry
    entitiesToBeKilled.insert(entity);                                                  // add entity to entitiesToBeKilled set
}

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

void Registry::RemoveEntityFromSystems(Entity entity){                                  // remove entity from all systems
    for(auto system: systems){                                                          // iterate through systems
        system.second->RemoveEntityFromSystem(entity);                                  // remove entity from system
    }
}

void Registry::Update(){                                                                // add/remove entities waiting to be added/removed
    for (auto entity: entitiesToBeAdded){                                               // iterate through all entities to be added
        AddEntityToSystems(entity);                                                     // add entity to all systems interested in the entity
    }
    entitiesToBeAdded.clear();                                                          // clear entitiesToBeAdded set after all entities have been added

    for(auto entity: entitiesToBeKilled){                                               // iterate through all entities to be removed
        RemoveEntityFromSystems(entity);                                                // remove entity from all systems
        entityComponentSignatures[entity.GetId()].reset();                              // clear entity's component signature
        freeEntityIds.push_back(entity.GetId());                                        // add entity id to freeEntityIds for reuse
    }
    entitiesToBeKilled.clear();                                                         // clear entitiesToBeKilled set after all entities have been added
};
