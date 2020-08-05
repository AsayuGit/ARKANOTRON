#ifndef _TYPES
#define _TYPES

#include "include.h"

#ifdef _SDL
#define SDL_Window SDL_Surface
#endif

#define ARK_Position SDL_Rect // Just for convinience

typedef struct{
    SDL_Window* Screen;
    #ifdef _SDL2
    SDL_Renderer* Renderer;
    #endif
}DisplayDevice;

typedef struct{
    const Uint8* KeyStates;
    SDL_Joystick* Joy1;
    SDL_Joystick* Joy2;
    SDL_Joystick* Joy3;
    SDL_Joystick* Joy4;
    char JoySupport;
}InputDevice;

typedef struct{
    int x;
    int y;
}Vector2i;

typedef struct{
    float x;
    float y;
}Vector2f;

typedef struct{
	Sint16 x;
	Sint16 y;
}Vector2s;

#endif