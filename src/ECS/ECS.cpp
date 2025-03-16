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

void Entity::KillEntity(){                                                              // remove entity from registry
    registry->KillEntity(*this);                                                        // call Registry::KillEntity()
}

void Entity::Tag(const std::string& tag){
    registry->TagEntity(*this, tag);                                                    // call Registry::TagEntity() (passing entity as an argument)
}

bool Entity::HasTag(const std::string& tag) const{
    return registry->EntityHasTag(*this, tag);                                          // call Registry::EntityHasTag() (passing entity as an argument)
}

void Entity::Group(const std::string& group){
    registry->GroupEntity(*this, group);                                                // call Registry::GroupEntity() (passing entity as an argument)
}

bool Entity::BelongsToGroup(const std::string& group) const{
    return registry->EntityBelongsToGroup(*this, group);                                // call Registry::EntityBelongsToGroup() (passing entity as an argument)
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
    int entityId;                                                                       // declare variable to store entity id

    if(freeEntityIds.empty()){                                                          // are any free entity ids available?
        entityId = numEntities++;                                                       // if no, create a new (incremented) entity id

        if(entityId >= entityComponentSignatures.size()){                               // if entity's component signature can't fit in entityComponentSignatures...
            entityComponentSignatures.resize(entityId + 1);                             // ... increase entityComponentSignatures size by 1
        }
    }
    else{
        entityId = freeEntityIds.front();                                               // else, get a previously-used entity id from the front of the deque
        freeEntityIds.pop_front();                                                      // pop the id to remove it from the deque
    }

    Entity entity(entityId);                                                            // create entity (on stack)
    entity.registry = this;                                                             // set Entity's registry member to point to registry object
    entitiesToBeAdded.insert(entity);                                                   // add entity to entitiesToBeAdded set

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

void Registry::TagEntity(Entity entity, const std::string& tag){
    tagToEntity.emplace(tag, entity);                                                   // add (tag, entity) pair to tagToEntity
    entityToTag.emplace(entity.GetId(), tag);                                           // add (entity.id, tag) pair to entityToTag
}

bool Registry::EntityHasTag(Entity entity, const std::string& tag) const{
    auto entityToTagIterator = entityToTag.find(entity.GetId());                        // find entity in entityToTag
    if(entityToTagIterator != entityToTag.end()){                                       // was the entity found in entityToTag?
        return (entityToTagIterator->second == tag);                                    // if yes, compare associated tag (if found) with specified tag and return result
    }
    else{
        return false;                                                                   // else, return faslse
    }
}

Entity Registry::GetEntityByTag(const std::string& tag) const{
    return tagToEntity.at(tag);                                                         // return tag asssociated with entity
}

void Registry::RemoveEntityTag(Entity entity){
    auto entityToTagIterator = entityToTag.find(entity.GetId());                        // find entity in entityToTag
    if(entityToTagIterator != entityToTag.end()){                                       // was the entity found in in entityToTag?
        auto tag = entityToTagIterator->second;                                         // if yes, get tag associated with entity
        entityToTag.erase(entityToTagIterator);                                         // remove (entity.id, tag) pair from entityToTag (via iterator argument)
        tagToEntity.erase(tag);                                                         // remove (tag, entity) pair from tagToEntity (via key argument)
    }
}

void Registry::GroupEntity(Entity entity, const std::string& group){
    groupToEntities.emplace(group, std::set<Entity>());                                 // if (group, set<Entity>) doesn't already exist, create it
    groupToEntities[group].emplace(entity);                                             // add entity to entities set associated with specified group in groupToEntities
    entityToGroup.emplace(entity.GetId(), group);                                       // add (entity.id, group) pair to entityToGroup
}

bool Registry::EntityBelongsToGroup(Entity entity, const std::string& group) const{
    auto entityToGroupIterator = entityToGroup.find(entity.GetId());                    // find entity in entityToGroup
    if(entityToGroupIterator != entityToGroup.end()){                                   // was the entity found in entityToGroup?
        return (entityToGroupIterator->second == group);                                // if yes, compare associated group (if found) with specified gropup and return result
    }
    else{
        return false;                                                                   // else, return false
    }
}

std::vector<Entity> Registry::GetEntitiesByGroup(const std::string& group) const{
    auto& entities = groupToEntities.at(group);                                         // get reference to  entities set associated with specified group (maybe gives better performance?)
    return std::vector<Entity>(entities.begin(), entities.end());                       // return vector created from entities
}

void Registry::RemoveEntityGroup(Entity entity){
    auto entityToGroupIterator = entityToGroup.find(entity.GetId());                    // find entity in entityToGroup
    if(entityToGroupIterator != entityToGroup.end()){                                   // was the entity found in entityToGroup?
        auto group = entityToGroupIterator->second;                                     // if yes, get group associated with entity
        auto& entities = groupToEntities.at(group);                                     // get reference to entities set associated with group
        entities.erase(entity);                                                         // remove entity from (group, entities) set
        entityToGroup.erase(entityToGroupIterator);                                     // remove (entity.id, group) pair from entityToGroup (via iterator argument)
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
