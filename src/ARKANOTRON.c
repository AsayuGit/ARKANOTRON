// ARKANOTRON.cpp : Defines the entry point for the application.
//
#ifdef _XBOX
#include "stdafx.h"
#endif
#include "include.h"

void main(int argc, char *argv[]){

    // Vars
    DisplayDevice DDevice;
    InputDevice IDevice;

    int i;

    // Code
    
    // Terminal parameters
    i = 1;
    while (i < argc){
        if (strcmp(argv[i], "-NoJoystick") == 0){
            IDevice.JoySupport = 0;
            printf("Joystick Dissabled\n");
        }
        i++;
    }


    srand(time(NULL));
    Init(); // Init SDL
    CreateDisplay(SCREEN_X, SCREEN_Y, "ARKANOTRON", &DDevice); // Creating the Window/Screen
    InitInputs(&IDevice); // Init Inputs

    MainGAME(argc, argv, &DDevice, &IDevice); // Launch the game

}