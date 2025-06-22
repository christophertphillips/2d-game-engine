#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include <SDL2/SDL.h>
#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"
#include <sol/sol.hpp>

class LevelLoader{
    public:
        LevelLoader();
        ~LevelLoader();

        void LoadLevel(sol::state& lua, SDL_Renderer* renderer, const std::unique_ptr<Registry>& registry, const std::unique_ptr<AssetStore>& assetStore, int levelNumber);
};

#endif
