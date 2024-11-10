#include "ECS.h"

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
