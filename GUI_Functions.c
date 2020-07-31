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

char IsRectColliding(SDL_Rect* Rect1, SDL_Rect* Rect2){
    /*
    if (((Rect1->x + Rect1->w >= Rect2->x) && (Rect1->x + Rect1->w <= Rect2->x + Rect2->w)) || ((Rect1->x >= Rect2->x) && (Rect1->x <= Rect2->x + Rect2->w))){ // Right / Left
        if (((Rect1->y + Rect1->h >= Rect2->y) && (Rect1->y + Rect1->h <= Rect2->y + Rect2->h)) || ((Rect1->y >= Rect2->y) && (Rect1->y <= Rect2->y + Rect2->h))){ // Down / Up
            return 1;
        }
    }*/

    char LeftRight, UpDown;
    LeftRight = 0;
    UpDown = 0;

    if ((Rect1->x + Rect1->w >= Rect2->x) && (Rect1->x + Rect1->w <= Rect2->x + Rect2->w)){ // Right
        LeftRight += COL_RIGHT;
    }
    if ((Rect1->x >= Rect2->x) && (Rect1->x <= Rect2->x + Rect2->w)){ // Left
        LeftRight += COL_LEFT;
    }

    if ((Rect1->y + Rect1->h >= Rect2->y) && (Rect1->y + Rect1->h <= Rect2->y + Rect2->h)){ // Down
        UpDown += COL_DOWN;
    }
    if ((Rect1->y >= Rect2->y) && (Rect1->y <= Rect2->y + Rect2->h)){ // Up
        UpDown += COL_UP;
    }

    if (LeftRight && UpDown){ // si il y a colision
        return LeftRight + UpDown;
    }

    

    return 0;
}