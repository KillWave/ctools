#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
void drawrect(SDL_Renderer *gMainRenderer, int x, int y, int w, int h, int color);
int   Color2Int(SDL_Color cc);
SDL_Color Int2Color(int color);
SDL_Rect drawstring(SDL_Renderer *gMainRenderer,char s[], // 文本字符串
	int x, int y,             // 绘制的位置
	char fontFile[],          // 指定字体文件
	int fontSize,             // 字体大小
	SDL_Color color);         // 颜色