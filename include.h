#ifndef _INCLUDE
#define _INCLUDE

//#define _SDL
//#define _XBOX
// Build targets

#ifdef _SDL
#define SDLMAIN <SDL/SDL.h>
#endif

#ifdef _XBOX
#define SDLMAIN <SDL.h>
#define _SDL
#define ROOT "D:\\"
#endif

#ifndef SDLMAIN // SDL2
#define SDLMAIN <SDL2/SDL.h>
#define _SDL2
#endif

#include SDLMAIN

#include "types.h"

#define SCREEN_X 640
#define SCREEN_Y 480

#ifndef ROOT
#define ROOT "./"
#endif

#endif