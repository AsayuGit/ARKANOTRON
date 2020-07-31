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

#endif