#ifndef _KEYMAP
#define _KEYMAP

#include "include.h"


#ifdef _SDL
#define ARK_LEFT SDLK_LEFT
#define ARK_RIGHT SDLK_RIGHT
#define ARK_UP SDLK_UP
#define ARK_DOWN SDLK_DOWN
#endif

#ifdef _SDL2
#define ARK_LEFT SDL_SCANCODE_LEFT
#define ARK_RIGHT SDL_SCANCODE_RIGHT
#define ARK_UP SDL_SCANCODE_UP
#define ARK_DOWN SDL_SCANCODE_DOWN
#endif

#ifdef _XBOX
#define XB_A 0
#define XB_B 1
#define XB_X 2
#define XB_Y 3
#define XB_BLACK 4
#define XB_WHITE 5
#define XB_LTRIGGER 6
#define XB_RTRIGGER 7
#define XB_START 8
#define XB_BACK 9
#define XB_LSTICK 10
#define XB_RSTICK 11
#endif

#endif