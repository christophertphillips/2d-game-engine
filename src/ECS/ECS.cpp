#include "ECS.h"

int Entity::GetId() const {                                                             // (const indicates method doesn't change members)
    return id;                                                                          // return entity's id
}

void System::AddEntityToSystem(Entity entity){
    entities.push_back(entity);                                                         // add entity to system's entities vector
};

std::vector<Entity> System::GetSystemEntities() const{
    return entities;                                                                    // return vector of entities associated with system
};

const Signature& System::GetComponentSignature() const{
    return componentSignature;                                                          // return signature indicating which components are required by the system
};
