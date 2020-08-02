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
#define JOY_A 0
#define JOY_B 1
#define JOY_X 2
#define JOY_Y 3
#define JOY_BLACK 4
#define JOY_WHITE 5
#define JOY_LTRIGGER 6
#define JOY_RTRIGGER 7
#define JOY_START 8
#define JOY_BACK 9
#define JOY_LSTICK 10
#define JOY_RSTICK 11
#else
#define JOY_A 0 // Temp Values
#define JOY_B 1
#define JOY_X 2
#define JOY_Y 3
#define JOY_BLACK 4
#define JOY_WHITE 5
#define JOY_LTRIGGER 6
#define JOY_RTRIGGER 7
#define JOY_START 8
#define JOY_BACK 9
#define JOY_LSTICK 10
#define JOY_RSTICK 11
#endif

#endif