#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdbool.h>

#include "include/inf8.h"


bool init(Inf8 *inf8)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_WINDOW_RESIZABLE) != 0)
    {
        printf("Can't init: %s\n", SDL_GetError());
        return true;
    }

    inf8->win = SDL_CreateWindow("События",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        INF8_DISPLAY_WIDTH, INF8_DISPLAY_HEIGHT, SDL_WINDOW_SHOWN);

    if (inf8->win == NULL)
    {
        printf("Can't create window: %s\n", SDL_GetError());
        return true;
    }
    SDL_SetWindowResizable(inf8->win, SDL_FALSE);

    inf8->surface = SDL_GetWindowSurface(inf8->win);

    return false;
}

bool quit(Inf8 *inf8)
{
    inf8->game.finish(inf8);

    SDL_DestroyWindow(inf8->win);
    SDL_Quit();

    Inf8_Destroy(inf8);

    return false;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./inf8 <path-to-so-file>\n");
        return 1;
    }

    Inf8 inf8 = Inf8_Init();
    if (init(&inf8)) return 1;

    if (Inf8_LoadGame(&inf8, argv[1]))
    {
        printf("Inf8_LoadGame: %s\n", Inf8_GetError(&inf8).msg);
        return 1;
    }

    inf8.game.init(&inf8);

    SDL_Event event;
    while (inf8.run)
    {
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) inf8.run = false;

            if (event.type == SDL_KEYDOWN)
            {
                Inf8_Event keydownEvent = {
                    .type = INF8_EVENT_KEYDOWN,
                    .keyCode = event.key.keysym.sym
                };

                Inf8_PushEvent(&inf8, keydownEvent);
            }

            if (event.type == SDL_WINDOWEVENT_RESIZED)
            {

                inf8.surface = SDL_GetWindowSurface(inf8.win);
            }
        }

        inf8.game.update(&inf8);

        for (u16 x = 0; x < INF8_DISPLAY_WIDTH; x++)
        {
            for (u16 y = 0; y < INF8_DISPLAY_HEIGHT; y++)
            {
                SDL_Color curPixel = inf8.display[x][y];
                SDL_Rect r = {x, y, INF8_PIXEL_WIDTH, INF8_PIXEL_HEIGHT};

                //printf("%d, %d, %d\n", curPixel.r, curPixel.g, curPixel.b);
                SDL_FillRect(inf8.surface, &r,
                    SDL_MapRGB(inf8.surface->format, curPixel.r, curPixel.g, curPixel.b));
            }
        }

        SDL_UpdateWindowSurface(inf8.win);
    }

    quit(&inf8);
}