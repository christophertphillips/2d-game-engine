#ifndef RENDERHEALTHSYSTEM_H
#define RENDERHEALTHSYSTEM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../ECS/ECS.h"
#include "../Components/HealthComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../AssetStore/AssetStore.h"

class RenderHealthSystem: public System {
    public:
        RenderHealthSystem(){
            RequireComponent<HealthComponent>();                                                                            // entity must have health component
            RequireComponent<TransformComponent>();                                                                         // entity must have transform component
            RequireComponent<SpriteComponent>();                                                                            // entity must have sprite component
        }

        void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& AssetStore, const SDL_Rect& camera){

            for(auto entity: GetSystemEntities()){
                const auto healthComponent = entity.GetComponent<HealthComponent>();                                        // get entity's health component
                const auto transformComponent = entity.GetComponent<TransformComponent>();                                  // get entity's transform component
                const auto spriteComponent = entity.GetComponent<SpriteComponent>();                                        // get entity's sprite component

                // set health display offset + color
                double healthDisplayOffset = spriteComponent.width * transformComponent.scale.x;                            // calculate health display offset
                SDL_Color healthDisplayColor = {0, 0, 0};
                if(healthComponent.healthPercentage >= 70){                                                                 // if entity's health component has a health percentage >= 80...
                    healthDisplayColor = {0, 255, 0};                                                                       //  ... set health display color to green
                }
                else if(healthComponent.healthPercentage >= 30){                                                            // else if entity's health component has a health percentage >= 40...
                    healthDisplayColor = {255, 255, 0};                                                                     // ... set health display color to yellow
                }
                else{
                    healthDisplayColor = {255, 0, 0};                                                                       // ... else set health display color to red
                }

                // draw health bar
                double healthBarWidth = (healthComponent.healthPercentage/100.0) * 20.0;                                    // calcualte health bar width
                int healthBarHeight = 2;
                SDL_Rect healthBar = {                                                                                      // create health bar rectangle
                    static_cast<int>(transformComponent.position.x - camera.x + healthDisplayOffset),                       // set health bar rectangle x position, adjusting relative to camera x position
                    static_cast<int>(transformComponent.position.y - camera.y),                                             // set health bar rectangle y position, adjusting relative to camera y position
                    static_cast<int>(healthBarWidth),                                                                       // set health bar rectangle width as a proportion of 32 pixels
                    healthBarHeight                                                                                         // set health bar rectange height
                };

                SDL_SetRenderDrawColor(renderer, healthDisplayColor.r, healthDisplayColor.g, healthDisplayColor.b, 255);    // set heatlh display color
                SDL_RenderFillRect(renderer, &healthBar);                                                                   // draw filled rectangle for health display

                // draw health text
                SDL_Surface* surface = TTF_RenderText_Blended(                                                              // create surface from font
                    AssetStore->GetFont("charriot-font-12"),                                                                // font (TTF_Font*)
                    std::to_string(healthComponent.healthPercentage).c_str(),                                               // text to display (const char*)
                    healthDisplayColor                                                                                      // font color (SDL_Color)
                );
                SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);                                     // create texture from surface
                SDL_FreeSurface(surface);                                                                                   // destroy surface

                int healthTextWidth = 0;
                int healthTextHeight = 0;
                SDL_QueryTexture(                                                                                           // query texture to determine label width + height
                    texture,                                                                                                // texture (SDL_Texture*)
                    NULL,                                                                                                   // raw format of texture to fill in via query (Uint32*)
                    NULL,                                                                                                   // access to the texture to fill in via query (int*)
                    &healthTextWidth,                                                                                       // width to fill in via query (int)
                    &healthTextHeight                                                                                       // height to fill in via query (int)
                );

                SDL_Rect dstRect = {                                                                                        // create destination recttangle for label
                    static_cast<int>(transformComponent.position.x - camera.x + healthDisplayOffset),                       // set destination rectangle x position, adjusting relative to camera x position
                    static_cast<int>(transformComponent.position.y - camera.y + 1),                                         // set destination rectangle y position, adjusting relative to camera y position (plus 1 pixel offset)
                    healthTextWidth,                                                                                        // set destination rectangle's width
                    healthTextHeight                                                                                        // set destination rectangle's height
                };

                SDL_RenderCopy(
                    renderer,                                                                                               // renderer (SDL_Renderer*)
                    texture,                                                                                                // texture (SDL_Texture*)
                    NULL,                                                                                                   // source rectangle (SDL_Rect*)
                    &dstRect                                                                                                // destination rectnagle (SDL_Rect*)
                );

                SDL_DestroyTexture(texture);                                                                                // destroy texture
            }
        }
};

#endif
