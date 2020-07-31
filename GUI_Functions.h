#ifndef _GUIFUNCTIONS
#define _GUIFUNCTIONS

#include "include.h"

// Scale a line by a factor of the screen resolution
void ScaleLine(int* line, int ScreenResolution, float ScalingFactor);

// Scale a Vector2i in the X direction while keeping it's aspect ratio
void Scale(Vector2i* SpriteDim, Vector2i ScreenResolution, float ScalingFactor);


#endif