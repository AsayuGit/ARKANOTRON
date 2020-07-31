#include "GUI_Functions.h"

void ScaleLine(int* line, int ScreenResolution, float ScalingFactor){
    (*line) = (int)((float)ScreenResolution * ScalingFactor);
}

void Scale(Vector2i* SpriteDim, Vector2i ScreenResolution, float ScalingFactor){
    Vector2f NewRes;
    NewRes.x = (float)ScreenResolution.x * ScalingFactor;
    NewRes.y = ((SpriteDim->y)/(SpriteDim->x))*NewRes.x;
    SpriteDim->x = (int)NewRes.x;
    SpriteDim->y = (int)NewRes.y;
}