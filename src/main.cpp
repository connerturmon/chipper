#include <iostream>
#include "SDL2/SDL.h"

const int SDL_ERROR = 3;
const unsigned int WIN_WIDTH = 1200;
const unsigned int WIN_HEIGHT = 600;

int main(int argc, char *argv[])
{
    // Initialization
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "ERROR Initializing SDL2: " << SDL_GetError() << std::endl;
        return SDL_ERROR;
    }

    SDL_Window *main_window = nullptr;
    SDL_Renderer *main_renderer = nullptr;
    SDL_Event event;
    bool emulator_running = true;
    
    // Panels for main viewport and debug viewport.
    SDL_Rect main_viewport = {
        0, 0, 800, 600
    };
    SDL_Rect debug_viewport = {
        800, 0, 400, 600
    };

    // Used to draw backround for viewports. Not sure why
    // using the viewport rects themselves does not work.
    SDL_Rect viewport_bg = {
        0, 0, WIN_WIDTH, WIN_HEIGHT
    };

    main_window = SDL_CreateWindow(
        "Chipper",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIN_WIDTH, WIN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (main_window == nullptr)
    {
        std::cout << "ERROR Initializing Main Window: " << SDL_GetError() << std::endl;
        return SDL_ERROR;
    }

    main_renderer = SDL_CreateRenderer(
        main_window, -1, SDL_RENDERER_ACCELERATED
    );
    if (main_renderer == nullptr)
    {
        std::cout << "ERROR Initializing Main Renderer: " << SDL_GetError() << std::endl;
        return SDL_ERROR;
    }

    // Main Render Loop
    while (emulator_running)
    {
        while (SDL_PollEvent(&event) != 0)
            if (event.type == SDL_QUIT)
                emulator_running = false;
        
        SDL_RenderSetViewport(main_renderer, &main_viewport);
        SDL_SetRenderDrawColor(main_renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderFillRect(main_renderer, &viewport_bg);

        SDL_RenderSetViewport(main_renderer, &debug_viewport);
        SDL_SetRenderDrawColor(main_renderer, 0, 0, 0, 0xff);
        SDL_RenderFillRect(main_renderer, &viewport_bg);

        SDL_RenderPresent(main_renderer);
        SDL_Delay(10);
    }

    SDL_Quit();

    return 0;
}