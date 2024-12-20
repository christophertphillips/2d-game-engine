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

Game::Game(){
    isRunning = false;                                                                  // set isRunning to false until game is initialized
    registry = std::make_unique<Registry>();                                            // instantiate Registry object
    assetStore = std::make_unique<AssetStore>();                                        // instantiate AssetStore object
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

    assetStore->AddTexture(renderer, "tank-image", "./assets/images/tank-panther-right.png");   // add tank texture
    assetStore->AddTexture(renderer, "truck-image", "./assets/images/truck-ford-right.png");    // add truck texture

    Entity tank = registry->createEntity();                                             // create tank entity
    tank.AddComponent<TransformComponent>(glm::vec2(10.0, 10.0), glm::vec2(1.0, 1.0), 0.0);  // add transform component to tank
    tank.AddComponent<RigidBodyComponent>(glm::vec2(40.0, 0.0));                        // add rigid body component to tank
    tank.AddComponent<SpriteComponent>("tank-image", 10, 10);                           // add sprite component to tank

    Entity truck = registry->createEntity();                                             // create truck entity
    truck.AddComponent<TransformComponent>(glm::vec2(50.0, 100.0), glm::vec2(1.0, 1.0), 0.0);  // add transform component to truck
    truck.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 50.0));                        // add rigid body component to truck
    truck.AddComponent<SpriteComponent>("truck-image", 10, 50);                         // add sprite component to truck
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

    registry->GetSystem<MovementSystem>().Update(deltaTime);                            // update movement system

    registry->Update();                                                                 // update registry (add and remove entities)
}

void Game::Render(){
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);                                  // set renderer color to dark gray (background)
    SDL_RenderClear(renderer);                                                          // clear renderer

    registry->GetSystem<RenderSystem>().Update(renderer, assetStore);                   // update render system

    SDL_RenderPresent(renderer);                                                        // swap back buffer with front buffer
}

void Game::Destroy(){
    SDL_DestroyRenderer(renderer);                                                      // destroy SDL renderer instance
    SDL_DestroyWindow(window);                                                          // destroy SDL window instance
    SDL_Quit();                                                                         // close SDL
}
