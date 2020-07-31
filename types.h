#ifndef _TYPES
#define _TYPES

#ifdef _SDL
#define SDL_Window SDL_Surface
#endif

#define ARK_Position SDL_Rect // Just for convinience

typedef struct{
    int x;
    int y;
}Vector2i;

typedef struct{
    float x;
    float y;
}Vector2f;

#endif