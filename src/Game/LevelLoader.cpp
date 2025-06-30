#include "./LevelLoader.h"
#include <SDL2/SDL.h>
#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"
#include "../Logger/Logger.h"
#include <sol/sol.hpp>
#include "./Game.h"
#include <fstream>
#include <sstream>
#include <string>
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/KeyboardControlledComponent.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/TextLabelComponent.h"

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

    // ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Load entities and assign components

    Entity chopper = registry->CreateEntity();                                          // create chopper entity
    chopper.AddComponent<AnimationComponent>(2, 15);                                    // add animation component to chopper
    chopper.AddComponent<KeyboardControlledComponent>(glm::vec2(0, -80), glm::vec2(80, 0), glm::vec2(0, 80), glm::vec2(-80, 0)); // add keyboard controlled component to chopper
    chopper.AddComponent<CameraFollowComponent>();                                      // add camera follow component to chopper
    chopper.AddComponent<ProjectileEmitterComponent>(glm::vec2(200.0, 200.0), 0, 4000, 25, true);    // add projectile emitter component to chopper

    Entity radar = registry->CreateEntity();                                            // add radar entity
    radar.AddComponent<AnimationComponent>(8,5);                                        // add animation component to chopper

    Entity tank = registry->CreateEntity();                                             // create tank entity
    tank.AddComponent<ProjectileEmitterComponent>(glm::vec2(0.0, -100.0), 1000, 4000, 25, false);   // add projectile emitter component to tank

    Entity truck = registry->CreateEntity();                                             // create truck entity
    truck.AddComponent<ProjectileEmitterComponent>(glm::vec2(0.0, -100.0), 1000, 2000, 25, false);   // add projectile emitter component to truck

    Entity treeA = registry->CreateEntity();                                            // create treeA entity

    Entity treeB = registry->CreateEntity();                                            // create treeB entity

    Entity label = registry->CreateEntity();                                            // create label entity
    SDL_Color green = { 0, 255, 0 };                                                    // create SLD_Color struct
    label.AddComponent<TextLabelComponent>("CHOPPER 1.0", "charriot-font", green, true);  // add text label component to label

    std::vector<Entity> initializedEntities = {chopper, radar, tank, truck, treeA, treeB, label};                           // [temporary vector for storing initialized entities]

    sol::table entitiesTable = lua["level"]["entities"];                                                                    // get entities table ("level/entities")
    for(int i = 0; i <= entitiesTable.size(); i++){                                                                         // iterate through items in "level/entities" table...
        sol::table entityTable = entitiesTable[i];                                                                          // get entity table ("level/entities/[entity[i]]")

        sol::optional<std::string> hasTag = entityTable["tag"];                                                             // if entity has a tag...
        if(hasTag != sol::nullopt){                                                                                         // ...
            initializedEntities[i].Tag(entityTable["tag"]);                                                                 // add tag to entity
        }

        sol::optional<std::string> hasGroup = entityTable["group"];                                                         // if entity has a group...
        if(hasGroup != sol::nullopt){                                                                                       // ...
            initializedEntities[i].Group(entityTable["group"]);                                                             // add group to entity
        }

        sol::optional<sol::table> hasComponents = entityTable["components"];                                                // if entity has components...
        if(hasComponents != sol::nullopt){                                                                                  // ...

            sol::optional<sol::table> hasTransformComponent = entityTable["components"]["transform_component"];             // if entity has transform component...
            if(hasTransformComponent != sol::nullopt){                                                                      // ...

                sol::table transformComponentTable = entityTable["components"]["transform_component"];                      // get transform component table ("level/entities/[entity[i]]/transform_component")
                initializedEntities[i].AddComponent<TransformComponent>(                                                    // add transform component to entity
                    glm::vec2(
                        transformComponentTable["position"]["x"],                                                           // x position
                        transformComponentTable["position"]["y"]                                                            // y position
                    ),
                    glm::vec2(
                        transformComponentTable["scale"]["x"].get_or(1.0),                                                  // x scale
                        transformComponentTable["scale"]["y"].get_or(1.0)                                                   // y scale
                    ),
                    transformComponentTable["rotation"].get_or(0.0)                                                         // rotation
                );

            }

            sol::optional<sol::table> hasRigidBodyComponent = entityTable["components"]["rigid_body_component"];            // if entity  has rigid body component...
            if(hasRigidBodyComponent != sol::nullopt){                                                                      // ...

                sol::table rigidBodyComponentTable = entityTable["components"]["rigid_body_component"];                     // get rigid body component table ("level/entities/[entity[i]]/rigid_body_component")
                initializedEntities[i].AddComponent<RigidBodyComponent>(                                                    // add rigid body component to entity
                    glm::vec2(
                        rigidBodyComponentTable["velocity"]["x"],                                                           // x velocity
                        rigidBodyComponentTable["velocity"]["y"]                                                            // y velocity
                    )
                );

            }

            sol::optional<sol::table> hasSpriteComponent = entityTable["components"]["sprite_component"];                   // if entity  has sprite component...
            if(hasSpriteComponent != sol::nullopt){                                                                         // ...

                sol::table spriteComponentTable = entityTable["components"]["sprite_component"];                            // get sprite component table ("level/entities/[entity[i]]/sprite_component")
                initializedEntities[i].AddComponent<SpriteComponent>(                                                       // add sprite component to entity
                    spriteComponentTable["asset_id"].get_or(static_cast<std::string>("")),                                  // sprite asset id (NOTE- default value "" is invalid, included here for consistency)
                    spriteComponentTable["width"],                                                                          // sprite width
                    spriteComponentTable["height"],                                                                         // sprite height
                    spriteComponentTable["z_index"],                                                                        // sprite z-index
                    spriteComponentTable["is_fixed"].get_or(false),                                                         // is sprite fixed onscreen
                    spriteComponentTable["src_rec_x"],                                                                      // source rectangle x
                    spriteComponentTable["src_rec_y"]                                                                       // source rectangle y
                );

            }

            sol::optional<sol::table> hasBoxColliderComponentTable = entityTable["components"]["box_collider_component"];   // if entity has box collider component...
            if(hasBoxColliderComponentTable != sol::nullopt){                                                               // ...

                sol::table boxColliderComponentTable = entityTable["components"]["box_collider_component"];                 // get box collider component table ("level/entities/[entity[i]]/box_collider_component")
                initializedEntities[i].AddComponent<BoxColliderComponent>(                                                  // add box collider component to entity
                    boxColliderComponentTable["width"],                                                                     // box collider width
                    boxColliderComponentTable["height"],                                                                    // box collider height
                    glm::vec2(
                        boxColliderComponentTable["scale"]["x"].get_or(1.0),                                                // box collider x scale
                        boxColliderComponentTable["scale"]["y"].get_or(1.0)                                                 // box collider y scale
                    ),
                    glm::vec2(
                        boxColliderComponentTable["offset"]["x"],                                                           // box collider x offset
                        boxColliderComponentTable["offset"]["y"]                                                            // box collider y offset
                    )
                );

            }

            sol::optional<sol::table> hasHealthComponent = entityTable["components"]["health_component"];                   // if entity has health component...
            if(hasHealthComponent != sol::nullopt){                                                                         // ...

                sol::table healthComponentTable = entityTable["components"]["health_component"];                            // get health component table ("level/entities/[entity[i]]/health_component")
                initializedEntities[i].AddComponent<HealthComponent>(                                                       // add health component to entity
                    static_cast<int>(healthComponentTable["health_percentage"])                                             // health percentage (NOTE- static cast needed to prevent ambiguous constructor call, for reasons unclear)
                );

            }

        }
    }
}
