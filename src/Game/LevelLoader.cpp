#include "./LevelLoader.h"
#include <SDL2/SDL.h>
#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"
#include "../Logger/Logger.h"
#include <sol/sol.hpp>

LevelLoader::LevelLoader(){
    Logger::Log("LevelLoader constructor called!");
}

LevelLoader::~LevelLoader(){
    Logger::Log("LevelLoader destructor called!");
}

void LevelLoader::LoadLevel(sol::state& lua, SDL_Renderer* renderer, const std::unique_ptr<Registry>& registry, const std::unique_ptr<AssetStore>& assetStore, int levelNumber){

    // ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Load + execute Lua script

    std::string luaScriptPath = "./assets/scripts/Level" + std::to_string(levelNumber) + ".lua";                            // create path for Lua script containing level data
    sol::load_result luaScriptResult = lua.load_file(luaScriptPath);                                                        // load (but don't execute) Lua script, to check for errors

    if(!luaScriptResult.valid()){                                                                                           // if Lua script has an error...
        sol::error luaScriptError = luaScriptResult;                                                                        // get the error
        std::string luaScriptErrorMessage = luaScriptError.what();                                                          // get the message associated with the error
        Logger::Err("Error loading the Lua script: " + luaScriptErrorMessage);                                              // log the error message
        return;                                                                                                             // return from LoadLevel (thus stopping further execution)
    }

    lua.script_file(luaScriptPath);                                                                                         // load (and execute) the Lua script

    // ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Load assets

    sol::table assets = lua["level"]["assets"];                                                                             // load Lua table "level/assets"
    for(int i = 0; i <= assets.size(); i++){                                                                                // iterate through items in "level/assets" table...

        sol::table asset = assets[i];                                                                                       // get asset (Lua table "level/assets/[assset[i]]")
        std::string assetType = asset["type"];                                                                              // get asset type
        if(assetType == "texture"){                                                                                         // if asset is a texture...
            assetStore->AddTexture(renderer, asset["id"], asset["file_path"]);                                              // ... load texture into asset store
        }
        else if(assetType == "font"){                                                                                       // ... else if asset is a font...
            assetStore->AddFont(asset["id"], asset["file_path"], asset["font_size"]);                                       // ... load font into the asset store
        }
    }

}
