#include "Game.h"
#include <SDL2/SDL.h>
#include <iostream>

Game::Game(){
    isRunning = false;                                                                  // set isRunning to false until game is initialized
    std::cout << "Game constructor called!" << std::endl;
}

Game::~Game(){
    std::cout << "Game destructor called!" << std::endl;
}

void Game::Initialize(){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){                                             // initialize SDL and catch errors
        std::cerr << "Error installing SDL." << std::endl;
        return;
    }

    SDL_DisplayMode sdlDisplayMode;                                                     // create SDL display mode struct
    SDL_GetCurrentDisplayMode(0, &sdlDisplayMode);                                      // set values of display mode struct
    windowWidth = sdlDisplayMode.w;                                                     // set windowWidth public member
    windowHeight = sdlDisplayMode.h;                                                    // set windowHeight public member

    window = SDL_CreateWindow(                                                          // create SDL window instance
        NULL,                                                                           // window title
        SDL_WINDOWPOS_CENTERED,                                                         // x position
        SDL_WINDOWPOS_CENTERED,                                                         // y position
        windowWidth,                                                                    // width
        windowHeight,                                                                   // height
        SDL_WINDOW_BORDERLESS                                                           // flags
    );

    if(!window){                                                                        // catch window errors
        std::cerr << "Error creating SDL window" << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(                                                      // create SDL renderer to go inside SDL window
        window,                                                                         // associated window
        -1,                                                                             // associated display (-1 = default)
        0                                                                               // flags
    );

    if(!renderer){                                                                      // catch renderer errors
        std::cerr << "Error creating SDL renderer." << std::endl;
        return;
    }

    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);                             // set window to (real) fullscreen

    isRunning = true;                                                                   // set isRunning to true once game is initialized
}

void Game::Run(){
    while(isRunning){                                                                   // execute game loop while isRunning is true
        ProcessInput();                                                                 // process inputs
        Update();                                                                       // update game state
        Render();                                                                       // render display
    }
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

}

void Game::Render(){
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);                                   // set renderer color to red
    SDL_RenderClear(renderer);                                                          // clear renderer

    SDL_RenderPresent(renderer);                                                        // paint window with renderer
}

void Game::Destroy(){
    SDL_DestroyRenderer(renderer);                                                      // destroy SDL renderer instance
    SDL_DestroyWindow(window);                                                          // destroy SDL window instance
    SDL_Quit();                                                                         // close SDL
}
