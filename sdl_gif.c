#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "SDL_anigif/SDL_anigif.h"
#define TITLE "SDL2 test gif"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    //获取gif图最大数量
    int gifMax = AG_LoadGIF("gif009.gif", NULL, 0);
    AG_Frame *frames = (AG_Frame *)malloc(sizeof(AG_Frame) * gifMax);
    AG_LoadGIF("gif009.gif", frames, gifMax);

    SDL_Rect rect = {0, 0, 0, 0};

    rect.w = frames[0].surface->w;
    rect.h = frames[0].surface->h;

    // SDL_Texture **textures = (SDL_Texture **)malloc(sizeof(SDL_CreateTextureFromSurface(render, frames[0].surface)) * gifMax);

    // int i;
    // for (i = 0; i < gifMax; i++)
    // {
    //     textures[i] = SDL_CreateTextureFromSurface(render, frames[i].surface);
    // }
    // SDL_Texture *texture = SDL_CreateTexture(render, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, rect.w, rect.h);

     SDL_Texture *texture = NULL;
    // int i ;
    // for (i = 0; i < gifMax; i++)
    // {
    //     SDL_RenderClear(render);
    //     texture = SDL_CreateTextureFromSurface(render, frames[i].surface);
    //     // SDL_UpdateTexture(texture, &rect, frames[i].surface->pixels, frames[i].surface->pitch);
    //     SDL_RenderCopy(render, texture, NULL, &rect);
    //     SDL_RenderPresent(render);
    //     SDL_Delay(frames->delay);
    //     SDL_DestroyTexture(texture);
    //     texture = NULL;
    // }

    bool quit = false;
    SDL_Event event;
    int i = 0;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            }
        }
         SDL_RenderClear(render);
        texture = SDL_CreateTextureFromSurface(render, frames[i].surface);
        // SDL_UpdateTexture(texture, &rect, frames[i].surface->pixels, frames[i].surface->pitch);
        SDL_RenderCopy(render, texture, NULL, &rect);
        SDL_RenderPresent(render);
        SDL_Delay(frames->delay);
        SDL_DestroyTexture(texture);
        texture = NULL;
        i = (i + 1) % gifMax;
    }
    free(frames);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}