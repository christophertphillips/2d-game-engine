#include "ECS.h"

int Entity::GetId() const {                                                             // (const indicates method doesn't change members)
    return id;                                                                          // return entity's id
}

std::vector<Entity> System::GetSystemEntities() const{
    return entities;                                                                    // return vector of entities associated with system
};
