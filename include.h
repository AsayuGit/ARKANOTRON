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
#include "GUI_Functions.h"
#include "GAME_Functions.h"
#include "keymap.h"
#include <time.h>
#include <math.h>

// Game settings
#define SCREEN_X 640
#define SCREEN_Y 480
#define MAX_FPS 60
#define PADBD 15.0f
#define BALLSPEED 10.0f
#define PADSPEED 7.0f
#define BRICK_X 10
#define BRICK_Y 5
#define NBOFLIVES 3
#define HUDHEIGHT 43

#define DEADZONE 10
#define STICK_MAX 32768.0f

#ifndef ROOT
#define ROOT "./"
#endif

#ifndef SL
#define SL "/"
#endif

#define _TEXTURE "ASSETS" SL "TEXTURES" SL

#endif