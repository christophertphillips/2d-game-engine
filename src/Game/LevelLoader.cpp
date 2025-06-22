#include "./LevelLoader.h"
#include <SDL2/SDL.h>
#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"
#include "../Logger/Logger.h"
#include <sol/sol.hpp>
#include "./Game.h"
#include <fstream>
#include <sstream>
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"

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

    // ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Load tilemap

    sol::table tilemap = lua["level"]["tilemap"];                                                                           // load Lua table "level/tilemap"
    std::string mapFilePath = tilemap["map_file_path"];                                                                     // load map file path
    std::string textureId = tilemap["texture_id"];                                                                          // load map texture id
    int tileSize = tilemap["tile_size"];                                                                                    // load tile size
    double tileScale = tilemap["tile_scale"];                                                                               // load tile scale
    int tileIndexX = 0;                                                                                                     // initialize tile x index
    int tileIndexY = 0;                                                                                                     // initialize tile y index
    int tilesAdded = 0;                                                                                                     // initialize tiles added
    std::string fileLine;                                                                                                   // delare string to hold current line
    std::ifstream fileStream("./assets/tilemaps/jungle.map");                                                               // create input stream from file

    while(std::getline(fileStream, fileLine)){                                                                              // iterate through lines of file

        std::string fileToken;                                                                                              // declare string to hold current token from current line
        std::istringstream fileLineStream(fileLine);                                                                        // create input stream from current line
        while(std::getline(fileLineStream, fileToken, ',')){                                                                // iterate through current line

            int srcRectX = tileSize * std::stoi(fileToken.substr(1,1));                                                     // calculate source rect x position
            int srcRectY = tileSize * std::stoi(fileToken.substr(0,1));                                                     // calculate source rect y position
            double backgroundTileXPos = tileIndexX * tileSize * tileScale;                                                  // calculate background tile x position
            double backgroundTileYPos = tileIndexY * tileSize * tileScale;                                                  // calculate background tile y position

            Entity backgroundTile = registry->CreateEntity();                                                               // create background tile entity
            backgroundTile.Group("tiles");
            tilesAdded++;                                                                                                   // increment tiles added

            backgroundTile.AddComponent<TransformComponent>(                                                                // add transform component to background tile entity
                glm::vec2(backgroundTileXPos, backgroundTileYPos),                                                          // position
                glm::vec2(tileScale, tileScale),                                                                            // scale
                0.0                                                                                                         // rotation
            );
            backgroundTile.AddComponent<SpriteComponent>(                                                                   // add sprite component to background tile entity
                "jungle-map",                                                                                               // asset id
                tileSize,                                                                                                   // width
                tileSize,                                                                                                   // height
                0,                                                                                                          // z-index
                false,                                                                                                      // isFixed
                srcRectX,                                                                                                   // source rect x position
                srcRectY                                                                                                    // source rect y position
            );

            tileIndexX++;                                                                                                   // increase tile x index
        }

        tileIndexX = 0;                                                                                                     // reset tile x index
        tileIndexY++;                                                                                                       // increase tile y index
    }
    fileStream.close();                                                                                                     // close file stream

    Game::fieldWidth = (tilesAdded / tileIndexY) * tileSize * tileScale;                                                    // calculate width of field = (num of tiles wide) * (tile size in pixels) * (tile scale)
    Game::fieldHeight = tileIndexY * tileSize * tileScale;                                                                  // calculate height of field = (num of tiles tall) * (tile size in pixels) * (tile scale)

}
