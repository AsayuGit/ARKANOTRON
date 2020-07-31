#ifndef _GUIFUNCTIONS
#define _GUIFUNCTIONS

#include "include.h"

#define COL_LEFT 2
#define COL_RIGHT 1
#define COL_UP 8
#define COL_DOWN 4

// Scale a line by a factor of the screen resolution
void ScaleLine(int* line, int ScreenResolution, float ScalingFactor);

// Scale a Vector2i in the X direction while keeping it's aspect ratio
void Scale(Vector2i* SpriteDim, Vector2i ScreenResolution, float ScalingFactor);

// Check if two SDL_Rect are colliding with one another and return 1 if true
char IsRectColliding(SDL_Rect* Rect1, SDL_Rect* Rect2);


#endif