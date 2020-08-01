#include "GUI_Functions.h"

void BallRespown(Vector2f* BallSpeed, float NominalSpeed){
    float Direction;
    Vector2f TempSpeed;

    Direction = 60 - (rand()%121); // entre 0 et 120
    Direction = Direction*3.14f/180.0f; // Deg to Rad
    TempSpeed.y = -NominalSpeed;
    TempSpeed.x = 0;

    // Rotation Matrix
    BallSpeed->x = TempSpeed.x * cos(Direction) - TempSpeed.y * sin(Direction);
    BallSpeed->y = TempSpeed.x * sin(Direction) + TempSpeed.y * cos(Direction);
}