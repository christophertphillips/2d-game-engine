#include "ECS.h"

int Entity::GetId() const {                                                             // (const indicates method doesn't change members)
    return id;                                                                          // return entity's id
}

std::vector<Entity> System::GetSystemEntities() const{
    return entities;                                                                    // return vector of entities associated with system
};

const Signature& System::GetComponentSignature() const{
    return componentSignature;                                                          // return signature indicating which components are required by the system
};
