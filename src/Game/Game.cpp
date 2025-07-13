#include "Game.h"
#include "../Logger/Logger.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <iostream>
#include "../ECS/ECS.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"
#include <fstream>
#include <sstream>
#include "../Systems/AnimationSystem.h"
#include "../Systems/CollisionSystem.h"
#include "../Systems/RenderCollisionSystem.h"
#include "../Systems/DamageSystem.h"
#include "../Systems/KeyboardControlSystem.h"
#include "../Events/KeyPressedEvent.h"
#include "../Systems/CameraMovementSystem.h"
#include "../Systems/ProjectileEmitSystem.h"
#include "../Systems/ProjectileLifecycleSystem.h"
#include <SDL2/SDL_ttf.h>
#include "../Systems/RenderTextSystem.h"
#include "../Systems/RenderHealthSystem.h"
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_impl_sdlrenderer2.h>
#include "../Systems/RenderGUISystem.h"
#include "./LevelLoader.h"
#include <sol/sol.hpp>
#include "../Systems/ScriptSystem.h"

int Game::windowWidth;
int Game::windowHeight;
int Game::fieldWidth;
int Game::fieldHeight;

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

    if(TTF_Init() != 0){                                                                // initialize TTF and catch errors
        Logger::Err("Error initializing SDL TTF");
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

    IMGUI_CHECKVERSION();                                                               // initialize ImGui
    ImGui::CreateContext();                                                             // ...
    ImGuiIO& io = ImGui::GetIO();                                                       // ...
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;                               // ...
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;                                // ...
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);                                // ...
    ImGui_ImplSDLRenderer2_Init(renderer);                                              // ...

    camera.x = 0;                                                                       // initialize camera x position
    camera.y = 0;                                                                       // initialize camera y position
    camera.w = windowWidth;                                                             // initialize camera width
    camera.h = windowHeight;                                                            // initialize camera height

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
    registry->AddSystem<KeyboardControlSystem>();                                       // add keyboard control system
    registry->AddSystem<CameraMovementSystem>();
    registry->AddSystem<ProjectileEmitSystem>();                                        // add projectile emit system
    registry->AddSystem<ProjectileLifecycleSystem>();                                   // add projectile lifecycle system
    registry->AddSystem<RenderTextSystem>();                                            // add render-text system
    registry->AddSystem<RenderHealthSystem>();                                          // add render-health system
    registry->AddSystem<RenderGUISystem>();                                             // add render-gui system
    registry->AddSystem<ScriptSystem>();                                                // add script system

    LevelLoader levelLoader;                                                            // create LevelLoader instance
    lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::os);                   // load libraries into Lua virtual machine
    // levelLoader.LoadLevel(lua, renderer, registry, assetStore, 1);                   // load first level
    levelLoader.LoadLevel(lua, renderer, registry, assetStore, 2);                      // load second level
}

void Game::ProcessInput(){
    SDL_Event sdlEvent;                                                                 // create SDL event struct
    while(SDL_PollEvent(&sdlEvent)){                                                    // poll SDL events

        ImGui_ImplSDL2_ProcessEvent(&sdlEvent);                                         // enable ImGui to receive SDL mouse events
        ImGuiIO& io = ImGui::GetIO();                                                   // ...
        int mouseX, mouseY;                                                             // ...
        const int mouseButtons = SDL_GetMouseState(&mouseX, &mouseY);                   // ...
        io.MousePos = ImVec2(mouseX, mouseY);                                           // ...
        io.MouseDown[0] = mouseButtons & SDL_BUTTON(SDL_BUTTON_LEFT);                   // ...
        io.MouseDown[1] = mouseButtons & SDL_BUTTON(SDL_BUTTON_RIGHT);                  // ...

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
                eventBus->EmitEvent<KeyPressedEvent>(sdlEvent.key.keysym.sym);          // emit KeyPressed event and pass SDL Keycode for key pressed
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
    registry->GetSystem<MovementSystem>().SubscribeToEvents(eventBus);                  // subscribe movement system to event bus
    registry->GetSystem<DamageSystem>().SubscribeToEvents(eventBus);                    // subscribe damage system to event bus
    registry->GetSystem<KeyboardControlSystem>().SubscribeToEvents(eventBus);           // subscribe keyboard control system to event bus
    registry->GetSystem<ProjectileEmitSystem>().SubscribeToEvents(eventBus);            // subscribe projectile emit system to event bus

    registry->GetSystem<MovementSystem>().Update(deltaTime);                            // update movement system
    registry->GetSystem<AnimationSystem>().Update();                                    // update animation system
    registry->GetSystem<CollisionSystem>().Update(eventBus);                            // update collision system
    registry->GetSystem<ProjectileEmitSystem>().Update(registry);                       // update projectile emit system
    registry->GetSystem<CameraMovementSystem>().Update(camera);                         // update camera movement system
    registry->GetSystem<ProjectileLifecycleSystem>().Update();                          // update projectile lifecycle system
    registry->GetSystem<ScriptSystem>().Update();                                       // update script system

    registry->Update();                                                                 // update registry (add and remove entities)
}

void Game::Render(){
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);                                  // set renderer color to dark gray (background)
    SDL_RenderClear(renderer);                                                          // clear renderer

    registry->GetSystem<RenderSystem>().Update(renderer, assetStore, camera);           // update render system
    registry->GetSystem<RenderTextSystem>().Update(renderer, assetStore, camera);       // update render-text system
    registry->GetSystem<RenderHealthSystem>().Update(renderer, assetStore, camera);     // update render-health system
    if(isDebug){                                                                        // if debug mode is active...
        registry->GetSystem<RenderCollisionSystem>().Update(renderer, camera);          // ...update render-collision system
        registry->GetSystem<RenderGUISystem>().Update(renderer, registry, camera);      // ...update render-gui system
    }

    SDL_RenderPresent(renderer);                                                        // swap back buffer with front buffer
}

void Game::Destroy(){
    ImGui_ImplSDLRenderer2_Shutdown();                                                  // shutdown/destroy ImGui...
    ImGui_ImplSDL2_Shutdown();                                                          // ...
    ImGui::DestroyContext();                                                            // ...
    SDL_DestroyRenderer(renderer);                                                      // destroy SDL renderer instance
    SDL_DestroyWindow(window);                                                          // destroy SDL window instance
    SDL_Quit();                                                                         // close SDL
}
