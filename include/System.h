#ifndef _SYSTEM
#define _SYSTEM

#include "include.h"

void Init();

void CreateDisplay(int ResX, int ResY, char Title[], DisplayDevice* DDevice);

void InitInputs(InputDevice* IDevice);

#endif