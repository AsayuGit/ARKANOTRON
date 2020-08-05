#ifndef _INCLUDE
#define _INCLUDE

//#define _SDL
//#define _XBOX
#define _MP3
// Build targets

#ifdef _SDL
#define SDLMAIN <SDL/SDL.h>
#define SDLIMAGE <SDL/SDL_image.h>
#define SDLMIXER <SDL/SDL_mixer.h>
#endif

#ifdef _XBOX
#define SDLMAIN <SDL.h>
#define SDLIMAGE <SDL_image.h>
#define SDLMIXER <SDL_mixer.h>
#define _SDL
#define ROOT "D:\\"
#define SL "\\"
#endif

#ifndef SDLMAIN // SDL2
#define SDLMAIN <SDL2/SDL.h>
#define SDLIMAGE <SDL2/SDL_image.h>
#define SDLMIXER <SDL2/SDL_mixer.h>
#define _SDL2
#endif

#include SDLMAIN
#ifdef _PNG
#include SDLIMAGE
#endif
#include SDLMIXER

#include "types.h"
#include "GUI_Functions.h"
#include "GAME_Functions.h"
#include "keymap.h"
#include "System.h"
#include <time.h>
#include <math.h>
#include <string.h>
#include "Scenes.h"

// Game settings
#define SCREEN_X 640
#define SCREEN_Y 480
#define MAX_FPS 60
#define PADBD 15.0f
#define BALLSPEED 0.6f
#define PADSPEED 0.4f
#define BRICK_X 10
#define BRICK_Y 5
#define NBOFLIVES 3
#define HUDHEIGHT 43
#define BOUNCE_OFFSET 5 // Prevent the ball from glitching in a wall

#define DEADZONE 0
#define STICK_MAX 32768.0f

#ifndef ROOT
#define ROOT "./"
#endif

#ifndef SL
#define SL "/"
#endif

#ifndef TEX
#ifdef _PNG
#define TEX ".png"
#else
#define TEX ".bmp"
#endif
#endif

#define SMX ".mp3"
#define SDX ".wav"

#define _TEXTURE "ASSETS" SL "TEXTURES" SL
#define _SOUNDS "ASSETS" SL "SOUNDS" SL

#endif