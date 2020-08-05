#include "System.h"

void Init(){
    // SDL Init
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        fprintf(stderr, "SDL Initialisation failed (%s)\n", SDL_GetError());
    }

	// SDL_Mixer init
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1){
		fprintf(stderr, "SDL_Mixer Initialisation failed (%s)\n", Mix_GetError());
	}
    if ((Mix_Init(MIX_INIT_MP3)&MIX_INIT_MP3) != MIX_INIT_MP3){
		fprintf(stderr, "MP3 Initialisation failed (%s)\n", Mix_GetError());
	}
}

void CreateDisplay(int ResX, int ResY, char Title[], DisplayDevice* DDevice){
    #ifdef _SDL
    DDevice->Screen = SDL_SetVideoMode(ResX, ResY, 0, SDL_HWSURFACE);
    SDL_WM_SetCaption(Title, NULL);
	SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 1); //Vsync
    #else
    DDevice->Screen = SDL_CreateWindow(Title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ResX, ResY, SDL_WINDOW_SHOWN);
    DDevice->Renderer = SDL_CreateRenderer(DDevice->Screen, -1, 0);
    SDL_GL_SetSwapInterval(1); // VSync
    #endif
}


void InitInputs(InputDevice* IDevice){
    IDevice->Joy1 = IDevice->Joy2 = IDevice->Joy3 = IDevice->Joy4 = NULL;
    if (SDL_NumJoysticks() && IDevice->JoySupport){
	    IDevice->Joy1 = SDL_JoystickOpen(0); // Attempt to allocate Player1 to the first joystick
        printf("There is %d available Joysticks\n", SDL_NumJoysticks());
    }
    #ifdef _SDL
    IDevice->KeyStates = SDL_GetKeyState(NULL);
    IDevice->JoySupport = SDL_JoystickOpened(0);
    #else
    IDevice->KeyStates = SDL_GetKeyboardState(NULL);
    if (IDevice->Joy1 == NULL){
        IDevice->JoySupport = 0;
    }else{
        IDevice->JoySupport = 1;
    }
    #endif
}