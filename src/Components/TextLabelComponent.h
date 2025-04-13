#ifndef TEXTLABELCOMPONENT_H
#define TEXTLABELCOMPONENT_H

#include <glm/glm.hpp>
#include <string>
#include <SDL2/SDL.h>

struct TextLabelComponent{
    std::string text;
    std::string assetId;
    SDL_Color color;
    bool isFixed;

    TextLabelComponent(std::string text = "", std::string assetId = "", const SDL_Color color = { 0, 0, 0 }, bool isFixed = true){
        this->text = text;
        this->assetId = assetId;
        this->color = color;
        this->isFixed = isFixed;
    }
};

#endif
