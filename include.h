#ifndef _INCLUDE
#define _INCLUDE

//#define _SDL
//#define _XBOX
// Build targets

#ifdef _SDL
#define SDLMAIN <SDL/SDL.h>
#define SDLIMAGE <SDL/SDL_image.h>
#endif

#ifdef _XBOX
#define SDLMAIN <SDL.h>
#define SDLIMAGE <SDL_image.h>
#define _SDL
#define ROOT "D:\\"
#define SL "\\"
#endif

#ifndef SDLMAIN // SDL2
#define SDLMAIN <SDL2/SDL.h>
#define SDLIMAGE <SDL2/SDL_image.h>
#define _SDL2
#endif

#include SDLMAIN
#include SDLIMAGE

#include "types.h"

#define SCREEN_X 640
#define SCREEN_Y 480

#ifndef ROOT
#define ROOT "./"
#endif

#ifndef SL
#define SL "/"
#endif

#define _TEXTURE "ASSETS" SL "TEXTURES" SL

#endif