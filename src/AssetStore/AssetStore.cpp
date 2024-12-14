#include "./AssetStore.h"
#include "../Logger/Logger.h"
#include <SDL2/SDL_image.h>

AssetStore::AssetStore(){                                                               // AssetStore constructor
    Logger::Log("AssetStore constructor called!");
}

AssetStore::~AssetStore(){                                                              // AssetStore destructor
    ClearAssets();                                                                      // call ClearAssets() to clear/destroy all assets in asset maps
    Logger::Log("AssetStore destructor called!");
}

void AssetStore::ClearAssets(){                                                         // clear/destroy all assets in asset maps
    for(auto texturesRef: textures){                                                    // loop through each texture
        SDL_DestroyTexture(texturesRef.second);                                         // destroy texture
    }
    textures.clear();                                                                   // clear textures map
}

void AssetStore::AddTexture(SDL_Renderer* renderer, const std::string& assetId, const std::string& filePath){   // add texture to textures map
    SDL_Surface* surface = IMG_Load(filePath.c_str());                                  // create surface from PNG image
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);             // create texture from surface
    SDL_FreeSurface(surface);                                                           // destroy surface

    textures.emplace(assetId, texture);                                                 // add texture to textures map

    Logger::Log("New texture added to the asset store with id = " + assetId);
}

SDL_Texture* AssetStore::GetTexture(const std::string& assetId) const{                  // get texture from textures map
    return textures.at(assetId);                                                        // get texture with associated id
}
