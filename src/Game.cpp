#include "Game.h"
#include <SDL2/SDL.h>
#include <iostream>

Game::Game(){
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

    SDL_Window* window = SDL_CreateWindow(                                              // create SDL window instance
        NULL,                                                                           // window title
        SDL_WINDOWPOS_CENTERED,                                                         // x position
        SDL_WINDOWPOS_CENTERED,                                                         // y position
        800,                                                                            // width
        600,                                                                            // height
        SDL_WINDOW_BORDERLESS                                                           // flags
    );

    if(!window){                                                                        // catch window errors
        std::cerr << "Error creating SDL window" << std::endl;
        return;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(                                        // create SDL renderer to go inside SDL window
        window,                                                                         // associated window
        -1,                                                                             // associated display (-1 = default)
        0                                                                               // flags
    );

    if(!renderer){                                                                      // catch renderer errors
        std::cerr << "Error creating SDL renderer." << std::endl;
        return;
    }
}

void Game::Run(){

}

void Game::ProcessInput(){

}

void Game::Update(){

}

void Game::Render(){

}

void Game::Destroy(){

}
