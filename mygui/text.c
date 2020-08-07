#include "./tools/utilities.h"
int gGameover = 0;

/*定义窗口位置(100,100),大小(640,480)*/
SDL_Rect gMainWinRect = {100, 100, 640, 480};
/* 窗口指针变量 */
SDL_Window *gMainWindow = NULL;
/* 图形绘制环境指针 */
SDL_Renderer *gMainRenderer = NULL;

int main(int argc, char *argv[])
{
    SDL_Surface *surface = NULL;
    SDL_Texture *texture = NULL;

    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);
    // Create a window via SDL
    gMainWindow = SDL_CreateWindow("Hello World", gMainWinRect.x, gMainWinRect.y, gMainWinRect.w, gMainWinRect.h, 0);
    // Create rendering context
    gMainRenderer = SDL_CreateRenderer(gMainWindow, -1, SDL_RENDERER_ACCELERATED);
    TTF_Init();
     SDL_Color textcolor = {255, 255, 0, 255};
    drawstring(gMainRenderer, "hello world", 100, 100, "./ttf/FreeSerif.ttf", 16, textcolor);
    SDL_RenderPresent(gMainRenderer);
    // Enter main loop
    while (!gGameover)
    {
        SDL_Event e; // 处理事件
        while (!gGameover && SDL_PollEvent(&e))
        {
            if ((e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE) ||
                e.type == SDL_QUIT) //user close window or press ESC key
            {
                gGameover = 1; // 终止应用程序
            }
            // other events
        }
        // 做一些其他的事情。。。。。。。。
        SDL_Delay(10); // 延时10ms，避免独霸CPU
    }
    // Destroy and quit
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(gMainRenderer);
    SDL_DestroyWindow(gMainWindow);
    SDL_Quit();
    // Finished!
    return 0;
}