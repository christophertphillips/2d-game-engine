#ifndef ASSETSTORE_H
#define ASSETSTORE_H

#include <map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class AssetStore{
    private:
        std::map<std::string, SDL_Texture*> textures;                                   // map storing textures in [id, texture pointer] pairs
        std::map<std::string, TTF_Font*> fonts;                                         // map storing fonts in in [id, font pointer] pairs

    public:
        AssetStore();                                                                   // AssetStore constructor
        ~AssetStore();                                                                  // AssetStore destructor
        void ClearAssets();                                                             // clear/destroy all assets in asset maps
        void AddTexture(SDL_Renderer* renderer, const std::string& assetId, const std::string& filePath);   // add texture to textures map
        SDL_Texture* GetTexture(const std::string& assetId) const;                      // get texture from textures map
};

#endif
