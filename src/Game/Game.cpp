#include "Game.h"
#include "../Logger/Logger.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <iostream>

Game::Game(){
    isRunning = false;                                                                  // set isRunning to false until game is initialized
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

glm::vec2 playerPosition;                                                               // 2D GLM vector used to store player position
glm::vec2 playerVelocity;                                                               // 2D GLM vector used to store player velocity

void Game::Setup(){
    playerPosition = glm::vec2(                                                         // initialize playerPosition GLM vector
        10.0,                                                                           // X position
        20.0                                                                            // Y position
    );
    playerVelocity = glm::vec2(                                                         // initialize playerVelocity GLM vector
        100.0,                                                                          // X velocity
        0.0                                                                             // Y velocity
    );
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

    playerPosition.x += playerVelocity.x * deltaTime;                                   // Update player's X position
    playerPosition.y += playerVelocity.y * deltaTime;                                   // Update player's Y position
}

void Game::Render(){
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);                                  // set renderer color to dark gray (background)
    SDL_RenderClear(renderer);                                                          // clear renderer

    SDL_Surface* surface = IMG_Load("./assets/images/tank-tiger-right.png");            // create surface from PNG image
    SDL_Texture* texture = SDL_CreateTextureFromSurface(                                // create texture from surface
        renderer,
        surface
    );
    SDL_FreeSurface(surface);                                                           // destroy surface

    SDL_Rect dstRect = {                                                                // create a destination rectangle for the texture
        static_cast<int>(playerPosition.x),                                             // x position
        static_cast<int>(playerPosition.y),                                             // y position
        32,                                                                             // width
        32                                                                              // height
    };

    SDL_RenderCopy(                                                                     // copy texture to renderer
        renderer,
        texture,
        NULL,                                                                           // source rectangle (NULL = capture entire source texture)
        &dstRect                                                                        // reference to destination rectangle
    );

    SDL_DestroyTexture(texture);                                                        // destroy texture

    SDL_RenderPresent(renderer);                                                        // swap back buffer with front buffer
}

void Game::Destroy(){
    SDL_DestroyRenderer(renderer);                                                      // destroy SDL renderer instance
    SDL_DestroyWindow(window);                                                          // destroy SDL window instance
    SDL_Quit();                                                                         // close SDL
}