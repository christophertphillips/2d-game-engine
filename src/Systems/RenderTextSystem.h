#ifndef RENDERTEXTSYSTEM_H
#define RENDERTEXTSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/TextLabelComponent.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../AssetStore/AssetStore.h"
#include "../Components/TransformComponent.h"

class RenderTextSystem: public System {
    public:
        RenderTextSystem(){
            RequireComponent<TextLabelComponent>();
            RequireComponent<TransformComponent>();
        }

        void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& AssetStore, const SDL_Rect& camera){
            for (auto entity: GetSystemEntities()){
                const auto textLabelComponent = entity.GetComponent<TextLabelComponent>();                                  // get entity's text label component
                const auto transformComponent = entity.GetComponent<TransformComponent>();

                SDL_Surface* surface = TTF_RenderText_Blended(                                                              // create surface from font
                    AssetStore->GetFont(textLabelComponent.assetId),                                                        // font (TTF_Font*)
                    textLabelComponent.text.c_str(),                                                                        // text to display (const char*)
                    textLabelComponent.color                                                                                // font color (SDL_Color)
                );
                SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);                                     // create texture from surface
                SDL_FreeSurface(surface);                                                                                   // destroy surface

                int labelWidth = 0;
                int labelHeight = 0;
                SDL_QueryTexture(                                                                                           // query texture to determine label width + height
                    texture,                                                                                                // texture (SDL_Texture*)
                    NULL,                                                                                                   // raw format of texture to fill in via query (Uint32*)
                    NULL,                                                                                                   // access to the texture to fill in via query (int*)
                    &labelWidth,                                                                                            // width to fill in via query (int)
                    &labelHeight                                                                                            // height to fill in via query (int)
                );

                SDL_Rect dstRect = {                                                                                        // create destination recttangle for label
                    static_cast<int>(transformComponent.position.x - (textLabelComponent.isFixed ? 0 : camera.x)),          // set destination rectangle x position, adjusting relative to camera x position
                    static_cast<int>(transformComponent.position.y - (textLabelComponent.isFixed ? 0 : camera.y)),          // set destination rectangle y position, adjusting relative to camera y position
                    labelWidth,                                                                                             // set destination rectangle's width
                    labelHeight                                                                                             // set destination rectangle's height
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
