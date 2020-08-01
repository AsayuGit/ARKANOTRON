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

char Bounce(SDL_Rect* Rect1, SDL_Rect* Rect2, Vector2f* BallSpeed) {
    char BallSides = 0;
    if((BallSides = IsRectColliding(Rect1, Rect2))){ // If the Ball is colliding with the bottom bar
        if ((BallSides & COL_RIGHT) && (BallSides & COL_LEFT)){
            BallSpeed->y = -BallSpeed->y;
        } else if ((BallSides & COL_DOWN) && (BallSides & COL_UP)){
            BallSpeed->x = -BallSpeed->x;
        } else if ((BallSides & COL_RIGHT) && (BallSides & COL_UP)){
            if (BallSpeed->x >= 0){
                BallSpeed->x = -BallSpeed->x;
            }
            if (BallSpeed->y < 0){
                BallSpeed->y = -BallSpeed->y;
            }
        } else if ((BallSides & COL_LEFT) && (BallSides & COL_DOWN)){
            if (BallSpeed->x < 0){
                BallSpeed->x = -BallSpeed->x;
            }
            if (BallSpeed->y >= 0) {
                BallSpeed->y = -BallSpeed->y;
            }
        } else if ((BallSides & COL_RIGHT) && (BallSides & COL_DOWN)){
            if (BallSpeed->x >= 0){
                BallSpeed->x = -BallSpeed->x;
            }
            if (BallSpeed->y >= 0){
                BallSpeed->y = -BallSpeed->y;
            }
        } else if ((BallSides & COL_LEFT) && (BallSides & COL_UP)){
            if (BallSpeed->x < 0){
                BallSpeed->x = -BallSpeed->x;
            }
            if (BallSpeed->y < 0){
                BallSpeed->y = -BallSpeed->y;
            }
        }
    }

    #ifdef _SHOW_COLISION
    if (BallSides){
        printf("BS : %d\n", BallSides);

        if (BallSides & COL_RIGHT){
            printf("1 Right\n"); // Right
        }
        if (BallSides & COL_LEFT){
            printf("2 Left\n"); // Left
        }
        if (BallSides & COL_DOWN){
            printf("4 Down\n"); // Down
        }
        if (BallSides & COL_UP){ // Up
            printf("8 Up\n");
        }
    }
    #endif

    return BallSides;
}