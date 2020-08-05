#include "Scenes.h"

int MainGAME(int argc, char* argv[], DisplayDevice* DDevice, InputDevice* IDevice){
// Vars
	// Textures
	SDL_Surface* Loading_Surface = NULL;
    SDL_Surface* Background_Surface = NULL;
    SDL_Surface* BrickSheet_Surface = NULL;
	SDL_Surface* PadBall_Surface = NULL;
    SDL_Surface* Heart_Surface = NULL;
    SDL_Surface* Hud_Surface = NULL;
	#ifdef _SDL2
    SDL_Texture* Background_Texture = NULL;
    SDL_Texture* BrickSheet_Texture = NULL;
	SDL_Texture* PadBall_Texture = NULL;
    SDL_Texture* Heart_Texture = NULL;
    SDL_Texture* Hud_Texture = NULL;
    #endif

	// Music
	Mix_Music* BackgroundMusic = NULL;

	// Sounds Effects
	Mix_Chunk* BallBounce = NULL;

    // Inputs
	Vector2s Lstick;

    SDL_Rect Pad_Rect, Ball_Rect;
    SDL_Rect Brick_Rect[8];
    ARK_Position Pad_Pos, Ball_Pos, Heart_Pos, Hud_Pos;
    ARK_Position Brick_Pos[BRICK_X*BRICK_Y];
    char Brick_Hit[BRICK_X*BRICK_Y];
    char Brick_Color[BRICK_X*BRICK_Y];

    Vector2f BallSpeed, BallFPos, PadFPos;
    //char BallSides;
    float PadSpeed;
    unsigned int Lives;

    char BallThrown;

    SDL_Event event;

	Uint32 OldTime, NewTime, DeltaTime;
	double FrameTimeLimit;

    #ifdef _XBOX
	LD_LAUNCH_DASHBOARD LaunchData;
    #endif

    int i, j;

// Code
	OldTime = 0; NewTime = 0; FrameTimeLimit = 1000.0 / (double)MAX_FPS; IDevice->JoySupport = 1;

    // Loading Sprites
    Background_Surface = LoadSufaceFromFile(ROOT""_TEXTURE"""Background"TEX);
    BrickSheet_Surface = LoadSufaceFromFile(ROOT""_TEXTURE"Brick"TEX);

	PadBall_Surface = LoadSufaceFromFile(ROOT""_TEXTURE"PadBall"TEX);
    Heart_Surface = LoadSufaceFromFile(ROOT""_TEXTURE"Heart"TEX);

    // Color key
    SetColorKey(PadBall_Surface, 0, 0xff, 0);
    SetColorKey(Heart_Surface, 0, 0xff, 0);

	Hud_Surface = LoadSufaceFromFile(ROOT""_TEXTURE"Hud3"TEX);

	Heart_Pos.x = 10;	Heart_Pos.y = 5;	Heart_Pos.w = Heart_Surface->w;	Heart_Pos.h = Heart_Surface->h;
	Hud_Pos.x = 0;	Hud_Pos.y = 0;	Hud_Pos.w = Hud_Surface->w;	Hud_Pos.h = Hud_Surface->h;
    #ifdef _SDL2
    Background_Texture = SDL_CreateTextureFromSurface(DDevice->Renderer, Background_Surface);
    SDL_FreeSurface(Background_Surface);
    BrickSheet_Texture = SDL_CreateTextureFromSurface(DDevice->Renderer, BrickSheet_Surface);
    SDL_FreeSurface(BrickSheet_Surface);
	PadBall_Texture = SDL_CreateTextureFromSurface(DDevice->Renderer, PadBall_Surface);
	SDL_FreeSurface(PadBall_Surface);
    Heart_Texture = SDL_CreateTextureFromSurface(DDevice->Renderer, Heart_Surface);
    SDL_FreeSurface(Heart_Surface);
    Hud_Texture = SDL_CreateTextureFromSurface(DDevice->Renderer, Hud_Surface);
    SDL_FreeSurface(Hud_Surface);
    #endif
	Pad_Rect.x = 0;	Pad_Rect.y = 32;	Pad_Rect.w = 160;	Pad_Rect.h = 25;
	Ball_Rect.x = 0;	Ball_Rect.y = 0;	Ball_Rect.w = 23;	Ball_Rect.h = 22;
    for (i = 0; i < 2; i++){
        for (j = 0; j < 4; j++){
			Brick_Rect[j + (i * 4)].x = j * 72;	Brick_Rect[j + (i * 4)].y = i * 40;	Brick_Rect[j + (i * 4)].w = 64;	Brick_Rect[j + (i * 4)].h = 32;
        }
    }

	// Loading Music
	BackgroundMusic = LoadMusicFromFile(ROOT""_SOUNDS"BGTheme"SMX);

	// Loading Sounds effects
	BallBounce = LoadChuckFromFile(ROOT""_SOUNDS"Click2"SDX);
	if (BallBounce == NULL){
		return 0;
	}
	Mix_VolumeMusic(MIX_MAX_VOLUME/2);
	Mix_PlayMusic(BackgroundMusic, -1); // Play the background music forever
    // Settings position and Logic
GameInit:
    // Default pos
    PadFPos.x = (float)((SCREEN_X - Pad_Rect.w) >> 1);
	PadFPos.y = 0;
	Pad_Pos.x = (int)PadFPos.x;	Pad_Pos.y = (int)PadFPos.y;	Pad_Pos.w = Pad_Rect.w;	Pad_Pos.h = Pad_Rect.h;

    ScaleLine((int*)(&(Pad_Pos.y)), SCREEN_Y, 0.9f);
    PadFPos.y = (float)Pad_Pos.y;

    BallFPos.x = (float)((SCREEN_X - Ball_Rect.w) >> 1);
    BallFPos.y = (float)((SCREEN_Y - Ball_Rect.h) >> 1);
	Ball_Pos.x = (int)BallFPos.x;	Ball_Pos.y = (int)BallFPos.y;	Ball_Pos.w = Ball_Rect.w;	Ball_Pos.h = Ball_Rect.h;

    for (i = 0; i < BRICK_Y; i++){
        for (j = 0; j < BRICK_X; j++){
			// init the briks
			Brick_Pos[j + (i * BRICK_X)].x = j * 64;
			Brick_Pos[j + (i * BRICK_X)].y = i * 32 + HUDHEIGHT;
			Brick_Pos[j + (i * BRICK_X)].w = 64;
			Brick_Pos[j + (i * BRICK_X)].h = 32;

            Brick_Color[j + (i * BRICK_X)] = rand()%8; // init their colors
            Brick_Hit[j + (i * BRICK_X)] = 1;
        }
    }
    Lives = NBOFLIVES;

    BallRespown(&BallSpeed, BALLSPEED);
    PadSpeed = PADSPEED;
    BallThrown = 0;

    while (1){
		// Framerate Interpolation
		OldTime = NewTime;
		NewTime = SDL_GetTicks();
		DeltaTime = (NewTime - OldTime);

        // Frame actions
        
        // Check victory conditions
        j = 0;
        for (i = 0; i < (BRICK_X * BRICK_Y); i++){
            j += Brick_Hit[i];
        }
        if (j == 0){
            // Victory !
            goto GameInit;
        }

        // Event
        while(SDL_PollEvent(&event)){
            switch (event.type)
            {
            case SDL_QUIT:
                goto Shutdown;
                break;

            case SDL_KEYDOWN:
                
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    goto Shutdown;
                    break;
                
                case SDLK_SPACE:
                    BallThrown = 1;
                    break;
                
                case SDLK_BACKSPACE:
                    goto GameInit;
                    break;
                
                default:
                    break;
                }
                break;
            
            default:
                break;
            }
        }

		// Joystick control
        if (IDevice->JoySupport){
            SDL_JoystickUpdate();
            if (SDL_JoystickGetButton(IDevice->Joy1, JOY_A)){
                BallThrown = 1;
            }
            if (SDL_JoystickGetButton(IDevice->Joy1, JOY_BACK)){
                goto GameInit;
            }
            if (SDL_JoystickGetButton(IDevice->Joy1, JOY_BLACK)){ // Back to the dash (SoftReset) [XBOX]
                goto Shutdown;
            }
            Lstick.x = SDL_JoystickGetAxis(IDevice->Joy1, 0);
            Lstick.y = SDL_JoystickGetAxis(IDevice->Joy1, 1);

            // Deadzone controll
            if ((Lstick.x < DEADZONE) && (Lstick.x > -DEADZONE)){
                Lstick.x = 0;
            }else{
                PadFPos.x += PadSpeed * ((float)Lstick.x / STICK_MAX) * DeltaTime;
            }
        }

		// Pad Mouvement
        if (IDevice->KeyStates[ARK_LEFT]){
            PadFPos.x -= PadSpeed * DeltaTime;
        }else if (IDevice->KeyStates[ARK_RIGHT]){
            PadFPos.x += PadSpeed * DeltaTime;
        }


        // Pad boundaries
        if (PadFPos.x < PADBD){
            PadFPos.x = PADBD;
        }

        if (PadFPos.x > SCREEN_X - Pad_Rect.w - PADBD){
            PadFPos.x = SCREEN_X - Pad_Rect.w - PADBD;
        }

        // Updating pad position
        Pad_Pos.x = (int)PadFPos.x;
        Pad_Pos.y = (int)PadFPos.y;
        
        // Bounce with the wall
        if (((BallFPos.x + (Ball_Rect.w >> 1)) > SCREEN_X) || ((BallFPos.x + (Ball_Rect.w >> 1)) < 0)){
            BallSpeed.x = -BallSpeed.x;
            BallFPos.x += BallSpeed.x * DeltaTime;
			Mix_PlayChannel(-1, BallBounce, 0);
        }
        if ((BallFPos.y + (Ball_Rect.h >> 1)) < HUDHEIGHT){
            BallSpeed.y = -BallSpeed.y;
            BallFPos.y += BallSpeed.y *DeltaTime;
			Mix_PlayChannel(-1, BallBounce, 0);
        }

        if (BallThrown){
            if ((BallFPos.y + (Ball_Rect.h >> 1)) > SCREEN_Y){ // Ball Over
                BallRespown(&BallSpeed, BALLSPEED);
                BallThrown = 0;
                Lives--;
            }
        }else{
           BallFPos.x = PadFPos.x + ((Pad_Rect.w - Ball_Rect.w) >> 1);
           BallFPos.y = PadFPos.y - Ball_Rect.h - 1;
        }

        // Live Max
        if (Lives > NBOFLIVES){
            Lives = NBOFLIVES;
        }

        if (Lives == 0){
            goto GameInit;
        }

        // Bounce with the Bar
		if(Bounce(&Ball_Pos, &Pad_Pos, &BallSpeed)){
			Mix_PlayChannel(-1, BallBounce, 0);
            BallFPos.x += BallSpeed.x * DeltaTime;
            BallFPos.y += BallSpeed.y *DeltaTime;
		}

        // Bounce with the bricks
        for (i = 0; i < (BRICK_X*BRICK_Y); i++){
            if (Brick_Hit[i]){
                if (Bounce(&Ball_Pos, &Brick_Pos[i], &BallSpeed)){
                    Brick_Hit[i] = 0;
					Mix_PlayChannel(-1, BallBounce, 0);
                    BallFPos.x += BallSpeed.x * DeltaTime;
                    BallFPos.y += BallSpeed.y *DeltaTime;
                }
            }
        }

        // We add the speed to the ball each frame
        if (BallThrown){
            BallFPos.x += BallSpeed.x * DeltaTime;
            BallFPos.y += BallSpeed.y *DeltaTime;
        }

        // Updating on screen ball position
        Ball_Pos.x = (int)BallFPos.x;
        Ball_Pos.y = (int)BallFPos.y;

        // Drawing Everything On Screen
        #ifdef _SDL
        SDL_BlitSurface(Background_Surface, NULL, DDevice->Screen, NULL); // Draw the background
        SDL_BlitSurface(PadBall_Surface, &Ball_Rect, DDevice->Screen, &Ball_Pos); // Draw the ball
        SDL_BlitSurface(PadBall_Surface, &Pad_Rect, DDevice->Screen, &Pad_Pos); // Draw the bottom bar
		for (i = 0; i < (BRICK_X*BRICK_Y); i++){
            if (Brick_Hit[i]){
                SDL_BlitSurface(BrickSheet_Surface, &Brick_Rect[Brick_Color[i]], DDevice->Screen, &Brick_Pos[i]); // Draw the briks
            }
        }
        SDL_BlitSurface(Hud_Surface, NULL, DDevice->Screen, NULL); // Draw the Hud
        for (i = 0; i < (int)Lives; i++){
			Heart_Pos.x = 10 + i * (Heart_Pos.h + 15);
			SDL_BlitSurface(Heart_Surface, NULL, DDevice->Screen, &Heart_Pos); // Draw the hearts
        }

        SDL_Flip(DDevice->Screen);
        #else
        SDL_RenderClear(DDevice->Renderer);
        SDL_RenderCopy(DDevice->Renderer, Background_Texture, NULL, NULL); // Draw the background
        SDL_RenderCopy(DDevice->Renderer, PadBall_Texture, &Ball_Rect, &Ball_Pos); // Draw the ball
        SDL_RenderCopy(DDevice->Renderer, PadBall_Texture, &Pad_Rect, &Pad_Pos); // Draw the bottom bar
        for (i = 0; i < (BRICK_X*BRICK_Y); i++){
            if (Brick_Hit[i]){
                SDL_RenderCopy(DDevice->Renderer, BrickSheet_Texture, &Brick_Rect[Brick_Color[i]], &Brick_Pos[i]); // Draw the briks
            }
        }
        SDL_RenderCopy(DDevice->Renderer, Hud_Texture, NULL, &Hud_Pos);// Draw the Hud
        for (int i = 0; i < Lives; i++){
            SDL_RenderCopy(DDevice->Renderer, Heart_Texture, NULL, &(SDL_Rect){Heart_Pos.x + i * (Heart_Pos.h + 15), Heart_Pos.y, Heart_Pos.w, Heart_Pos.h}); // Draw the hearts
        }
        SDL_RenderPresent(DDevice->Renderer);
        #endif
        //SDL_Delay(16); // 60fps lock, kinda
    }

Shutdown:
    #ifdef _SDL
    if (SDL_JoystickOpened(0)){
		SDL_JoystickClose(IDevice->Joy1);
	}
    SDL_FreeSurface(Background_Surface);
    #endif

    #ifdef _SDL2
    SDL_DestroyTexture(Background_Texture);
    #endif
	
	Mix_FreeChunk(BallBounce);
	Mix_FreeMusic(BackgroundMusic);

	// Api cleanup
#ifdef _PNG
    IMG_Quit();
#endif
	Mix_CloseAudio();
	Mix_Quit();
    SDL_Quit();

    #ifdef _XBOX
    LaunchData.dwReason = XLD_LAUNCH_DASHBOARD_MAIN_MENU;
    XLaunchNewImage(NULL, (LAUNCH_DATA*)&LaunchData);
    #endif

    return 0;
}