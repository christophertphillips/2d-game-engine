#include "Game.h"
#include "../Logger/Logger.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <iostream>
#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"
#include "../Components/SpriteComponent.h"
#include <fstream>
#include <sstream>
#include "../Systems/AnimationSystem.h"
#include "../Components/AnimationComponent.h"
#include "../Systems/CollisionSystem.h"
#include "../Components/BoxColliderComponent.h"
#include "../Systems/RenderCollisionSystem.h"
#include "../Systems/DamageSystem.h"

Game::Game(){
    isRunning = false;                                                                  // set isRunning to false until game is initialized
    isDebug = false;                                                                    // set isDebug to false by default
    registry = std::make_unique<Registry>();                                            // instantiate Registry object
    assetStore = std::make_unique<AssetStore>();                                        // instantiate AssetStore object
    eventBus = std::make_unique<EventBus>();                                            // instantiate EventBus object
    Logger::Log("Game constructor called!");
}

Game::~Game(){
    Logger::Log("Game destructor called!");
}

void Game::Initialize(){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){                                             // initialize SDL and catch errors
        Logger::Err("Error installing SDL.");
        return;
    }

    SDL_DisplayMode sdlDisplayMode;                                                     // create SDL display mode struct
    SDL_GetCurrentDisplayMode(0, &sdlDisplayMode);                                      // set values of display mode struct
    windowWidth = 800; //sdlDisplayMode.w;                                              // set windowWidth public member
    windowHeight = 600; //sdlDisplayMode.h;                                             // set windowHeight public member

    window = SDL_CreateWindow(                                                          // create SDL window instance
        NULL,                                                                           // window title
        SDL_WINDOWPOS_CENTERED,                                                         // x position
        SDL_WINDOWPOS_CENTERED,                                                         // y position
        windowWidth,                                                                    // width
        windowHeight,                                                                   // height
        SDL_WINDOW_BORDERLESS                                                           // flags
    );

    if(!window){                                                                        // catch window errors
        Logger::Err("Error creating SDL window");
        return;
    }

    renderer = SDL_CreateRenderer(                                                      // create SDL renderer to go inside SDL window
        window,                                                                         // associated window
        -1,                                                                             // associated display (-1 = default)
        0                                                                               // flags
    );

    if(!renderer){                                                                      // catch renderer errors
        Logger::Err("Error creating SDL renderer.");
        return;
    }

    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);                             // set window to (real) fullscreen

    isRunning = true;                                                                   // set isRunning to true once game is initialized
}

void Game::Run(){
    Setup();                                                                            // configure stuff before game loop starts
    while(isRunning){                                                                   // execute game loop while isRunning is true
        ProcessInput();                                                                 // process inputs
        Update();                                                                       // update game state
        Render();                                                                       // render display
    }
}

void Game::Setup(){
    registry->AddSystem<MovementSystem>();                                              // add movement system
    registry->AddSystem<RenderSystem>();                                                // add render system
    registry->AddSystem<AnimationSystem>();                                             // add animation system
    registry->AddSystem<CollisionSystem>();                                             // add collision system
    registry->AddSystem<RenderCollisionSystem>();                                       // add render-collision system
    registry->AddSystem<DamageSystem>();                                                // add damage system

    assetStore->AddTexture(renderer, "tank-image", "./assets/images/tank-panther-right.png");   // add tank texture
    assetStore->AddTexture(renderer, "truck-image", "./assets/images/truck-ford-right.png");    // add truck texture
    assetStore->AddTexture(renderer, "chopper-image", "./assets/images/chopper.png");   // add chopper texture
    assetStore->AddTexture(renderer, "radar-image", "./assets/images/radar.png");       // add radar texture
    assetStore->AddTexture(renderer, "jungle-map", "./assets/tilemaps/jungle.png");     // add jungle texture

    int tileSize = 32;                                                                  // initialize tile size (32 x 32)
    double tileScale = 1.0;                                                             // initialize tile scale
    int tileIndexX = 0;                                                                 // initialize tile x index
    int tileIndexY = 0;                                                                 // initialize tile y index
    std::string fileLine;                                                               // delare string to hold current line
    std::ifstream fileStream("./assets/tilemaps/jungle.map");                           // create input stream from file

    while(std::getline(fileStream, fileLine)){                                          // iterate through lines of file

        std::string fileToken;                                                          // declare string to hold current token from current line
        std::istringstream fileLineStream(fileLine);                                    // create input stream from current line
        while(std::getline(fileLineStream, fileToken, ',')){                            // iterate through current line

            int srcRectX = tileSize * std::stoi(fileToken.substr(1,1));                 // calculate source rect x position
            int srcRectY = tileSize * std::stoi(fileToken.substr(0,1));                 // calculate source rect y position
            double backgroundTileXPos = tileIndexX * tileSize * tileScale;              // calculate background tile x position
            double backgroundTileYPos = tileIndexY * tileSize * tileScale;              // calculate background tile y position

            Entity backgroundTile = registry->CreateEntity();                           // create background tile entity

            backgroundTile.AddComponent<TransformComponent>(                            // add transform component to background tile entity
                glm::vec2(backgroundTileXPos, backgroundTileYPos),                      // position
                glm::vec2(tileScale, tileScale),                                        // scale
                0.0                                                                     // rotation
            );
            backgroundTile.AddComponent<SpriteComponent>(                               // add sprite component to background tile entity
                "jungle-map",                                                           // asset id
                tileSize,                                                               // width
                tileSize,                                                               // height
                0,                                                                      // z-index
                srcRectX,                                                               // source rect x position
                srcRectY                                                                // source rect y position
            );

            tileIndexX++;                                                               // increase tile x index
        }

        tileIndexX = 0;                                                                 // reset tile x index
        tileIndexY++;                                                                   // increase tile y index
    }
    fileStream.close();                                                                 // close file stream

    Entity chopper = registry->CreateEntity();                                          // create chopper entity
    chopper.AddComponent<TransformComponent>(glm::vec2(100.0, 100.0), glm::vec2(1.0, 1.0), 0.0);    // add transform component to chopper
    chopper.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));                      // add rigid body component to chopper
    chopper.AddComponent<SpriteComponent>("chopper-image", 32, 32, 1);                  // add sprite component to chopper
    chopper.AddComponent<AnimationComponent>(2, 15);                                    // add animation component to chopper

    Entity radar = registry->CreateEntity();                                            // add radar entity
    radar.AddComponent<TransformComponent>(glm::vec2(windowWidth - 74, 10.0), glm::vec2(1.0, 1.0), 0.0);    // add transform component to radar
    // radar.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));                     // add rigid body component to radar
    radar.AddComponent<SpriteComponent>("radar-image", 64, 64, 1);                      // add sprite component to chopper
    radar.AddComponent<AnimationComponent>(8,5);                                        // add animation component to chopper

    Entity tank = registry->CreateEntity();                                             // create tank entity
    tank.AddComponent<TransformComponent>(glm::vec2(10.0, 10.0), glm::vec2(1.0, 1.0), 0.0);  // add transform component to tank
    tank.AddComponent<RigidBodyComponent>(glm::vec2(50.0, 0.0));                        // add rigid body component to tank
    tank.AddComponent<SpriteComponent>("tank-image", 32, 32, 1);                        // add sprite component to tank
    tank.AddComponent<BoxColliderComponent>(32, 32);

    Entity truck = registry->CreateEntity();                                             // create truck entity
    truck.AddComponent<TransformComponent>(glm::vec2(250.0, 10.0), glm::vec2(1.0, 1.0), 0.0);  // add transform component to truck
    truck.AddComponent<RigidBodyComponent>(glm::vec2(-50.0, 0.0));                        // add rigid body component to truck
    truck.AddComponent<SpriteComponent>("truck-image", 32, 32, 1);                      // add sprite component to truck
    truck.AddComponent<BoxColliderComponent>(32, 32);
}

void Game::ProcessInput(){
    SDL_Event sdlEvent;                                                                 // create SDL event struct
    while(SDL_PollEvent(&sdlEvent)){                                                    // poll SDL events
        switch(sdlEvent.type){                                                          // switch on type of SDL event
            case SDL_QUIT:                                                              // if user clicked 'X" button, set isRunning to false
                isRunning = false;
                break;
            case SDL_KEYDOWN:                                                           // is user pressed "Escape", set isRunning to False
                if(sdlEvent.key.keysym.sym == SDLK_ESCAPE){
                    isRunning = false;
                }
                else if(sdlEvent.key.keysym.sym == SDLK_d){                             // if user pressed "d", toggle isDebug
                    isDebug = !isDebug;
                }
                break;
        }
    }
}

void Game::Update(){
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);   // calculate time to wait until next frame should begin
    if(timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME){                            // delay if timeToWait is within bounds (latter bound provided for thoroughness)
        SDL_Delay(timeToWait);                                                          // delay necessary time until next frame should begin
    }

    double deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;              // difference in time since last frame (converted to seconds)

    millisecsPreviousFrame = SDL_GetTicks();                                            // set current milliseconds for next Update() call

    eventBus->Reset();                                                                  // reset event bus subscribers
    registry->GetSystem<DamageSystem>().SubscribeToEvents(eventBus);                    // subscribe damage system to event bus

    registry->GetSystem<MovementSystem>().Update(deltaTime);                            // update movement system
    registry->GetSystem<AnimationSystem>().Update();                                    // update animation system
    registry->GetSystem<CollisionSystem>().Update(eventBus);                            // update collision system

    registry->Update();                                                                 // update registry (add and remove entities)
}

void Game::Render(){
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);                                  // set renderer color to dark gray (background)
    SDL_RenderClear(renderer);                                                          // clear renderer

    registry->GetSystem<RenderSystem>().Update(renderer, assetStore);                   // update render system
    if(isDebug){                                                                        // if debug mode is active...
        registry->GetSystem<RenderCollisionSystem>().Update(renderer);                  // ...update render-collision system
    }

    SDL_RenderPresent(renderer);                                                        // swap back buffer with front buffer
}

void Game::Destroy(){
    SDL_DestroyRenderer(renderer);                                                      // destroy SDL renderer instance
    SDL_DestroyWindow(window);                                                          // destroy SDL window instance
    SDL_Quit();                                                                         // close SDL
}
