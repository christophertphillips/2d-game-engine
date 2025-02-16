#ifndef BOXCOLLIDERCOMPONENT_H
#define BOXCOLLIDERCOMPONENT_H

#include <glm/glm.hpp>

struct BoxColliderComponent{
    int width;
    int height;
    glm::vec2 offset;

    BoxColliderComponent(int width = 0, int height = 0, glm::vec2 scale = glm::vec2(1.0, 1.0), glm::vec2 offset = glm::vec2(0)){
        this->width = width * scale.x;
        this->height = height * scale.y;
        this->offset = offset;
    }
};

#endif
