#include "ECS.h"

int Entity::GetId() const {                                                             // (const indicates method doesn't change members)
    return id;                                                                          // return entity's id
}
