// ARKANOTRON.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "include.h"

int main(int argc, char *argv[]){

// Vars
    SDL_Window* screen = NULL;
    SDL_Surface* Background_Surface = NULL;
    SDL_Surface* SpriteSheet_Surface = NULL;
    SDL_Surface* Heart_Surface = NULL;
    SDL_Surface* Hud_Surface = NULL;

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
    const Uint8* KeyStates;

    #ifdef _SDL2
    SDL_Renderer* Renderer;
    SDL_Texture* Background_Texture = NULL;
    SDL_Texture* SpriteSheet_Texture = NULL;
    SDL_Texture* Heart_Texture = NULL;
    SDL_Texture* Hud_Texture = NULL;
    #endif

    int i, j;

// Code
    srand(time(NULL));
    // SDL Init
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        fprintf(stderr, "SDL Initialisation failed\n%s\n", SDL_GetError());
    }
    
    #ifdef _INIT_IMG
    // SDL_Image Init
    if(IMG_Init(IMG_INIT_PNG) != 0){
        fprintf(stderr, "SDL_Image Initialisation failed\n%s\n", IMG_GetError());
    }
    #endif

 
    printf("Hey everything works :3\n");
    // Creating the Window/Screen
    #ifdef _SDL
    screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
    KeyStates = SDL_GetKeyState(NULL);
    #else
    screen = SDL_CreateWindow("Henlo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_X, SCREEN_Y, SDL_WINDOW_SHOWN);
    Renderer = SDL_CreateRenderer(screen, -1, 0);
    KeyStates = SDL_GetKeyboardState(NULL);
    #endif

    // Loading Sprites
    Background_Surface = IMG_Load(ROOT""_TEXTURE"""Background.png");
    if (Background_Surface == NULL){
        fprintf(stderr, "Can't load BackgroundSurface !\n%s\n", IMG_GetError());
    }
    SpriteSheet_Surface = IMG_Load(ROOT""_TEXTURE"BasicArkanoidPack.png");
    if (SpriteSheet_Surface == NULL){
        fprintf(stderr, "Can't load SpriteSheet_Surface !\n%s\n", IMG_GetError());
    }
    Heart_Surface = IMG_Load(ROOT""_TEXTURE"Heart.png");
    if (Heart_Surface == NULL){
        fprintf(stderr, "Can't load Heart_Surface !\n%s\n", IMG_GetError());
    }
    Hud_Surface = IMG_Load(ROOT""_TEXTURE"Hud3.png");
    if (Hud_Surface == NULL){
        fprintf(stderr, "Can't load Hud_Surface !\n%s\n", IMG_GetError());
    }
    //Heart_Pos = (SDL_Rect){10, 5, Heart_Surface->w, Heart_Surface->h};
	Heart_Pos.x = 10;	Heart_Pos.y = 5;	Heart_Pos.w = Heart_Surface->w;	Heart_Pos.h = Heart_Surface->h;
    //Hud_Pos = (SDL_Rect){0, 0, Hud_Surface->w, Hud_Surface->h};
	Hud_Pos.x = 0;	Hud_Pos.y = 0;	Hud_Pos.w = Hud_Surface->w;	Hud_Pos.h = Hud_Surface->h;
    #ifdef _SDL2
    Background_Texture = SDL_CreateTextureFromSurface(Renderer, Background_Surface);
    SDL_FreeSurface(Background_Surface);
    SpriteSheet_Texture = SDL_CreateTextureFromSurface(Renderer, SpriteSheet_Surface);
    SDL_FreeSurface(SpriteSheet_Surface);
    Heart_Texture = SDL_CreateTextureFromSurface(Renderer, Heart_Surface);
    SDL_FreeSurface(Heart_Surface);
    Hud_Texture = SDL_CreateTextureFromSurface(Renderer, Hud_Surface);
    SDL_FreeSurface(Hud_Surface);
    #endif
    //Pad_Rect = (SDL_Rect){0, 111, 160, 25};
	Pad_Rect.x = 0;	Pad_Rect.y = 111;	Pad_Rect.w = 160;	Pad_Rect.h = 25;
    //Ball_Rect = (SDL_Rect){0, 81, 23, 22};
	Ball_Rect.x = 0;	Ball_Rect.y = 81;	Ball_Rect.w = 23;	Ball_Rect.h = 22;
    for (i = 0; i < 2; i++){
        for (j = 0; j < 4; j++){
            //Brick_Rect[j + (i * 4)] = (SDL_Rect){j * 72, i * 40, 65, 32};
			Brick_Rect[j + (i * 4)].x = j * 72;	Brick_Rect[j + (i * 4)].y = i * 40;	Brick_Rect[j + (i * 4)].w = 65;	Brick_Rect[j + (i * 4)].h = 32;
        }
    }

    // Settings position and Logic
GameInit:
    // Default pos
    PadFPos.x = (float)((SCREEN_X - Pad_Rect.w) >> 1);
	PadFPos.y = 0;
    //Pad_Pos = (ARK_Position){(int)PadFPos.x, PadFPos.y, Pad_Rect.w, Pad_Rect.h};
	Pad_Pos.x = (int)PadFPos.x;	Pad_Pos.y = (int)PadFPos.y;	Pad_Pos.w = Pad_Rect.w;	Pad_Pos.h = Pad_Rect.h;

    ScaleLine((int*)(&(Pad_Pos.y)), SCREEN_Y, 0.9f);
    PadFPos.y = (float)Pad_Pos.y;

    BallFPos.x = (float)((SCREEN_X - Ball_Rect.w) >> 1);
    BallFPos.y = (float)((SCREEN_Y - Ball_Rect.h) >> 1);
    //Ball_Pos = (ARK_Position){(int)BallFPos.x, (int)BallFPos.y, Ball_Rect.w, Ball_Rect.h};
	Ball_Pos.x = (int)BallFPos.x;	Ball_Pos.y = (int)BallFPos.y;	Ball_Pos.w = Ball_Rect.w;	Ball_Pos.h = Ball_Rect.h;

    for (i = 0; i < BRICK_Y; i++){
        for (j = 0; j < BRICK_X; j++){
            //Brick_Pos[j + (i * BRICK_X)] = (SDL_Rect){j * 65, i * 32 + HUDHEIGHT, 65, 32}; // init the briks
			// init the briks
			Brick_Pos[j + (i * BRICK_X)].x = j * 65;
			Brick_Pos[j + (i * BRICK_X)].y = i * 32 + HUDHEIGHT;
			Brick_Pos[j + (i * BRICK_X)].w = 65;
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

        // Pad Mouvement
        if (KeyStates[ARK_LEFT]){
            PadFPos.x -= PadSpeed;
        }else if (KeyStates[ARK_RIGHT]){
            PadFPos.x += PadSpeed;
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
        }
        if ((BallFPos.y + (Ball_Rect.h >> 1)) < HUDHEIGHT){
            BallSpeed.y = -BallSpeed.y;
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
        Bounce(&Ball_Pos, &Pad_Pos, &BallSpeed);

        // Bounce with the bricks
        for (i = 0; i < (BRICK_X*BRICK_Y); i++){
            if (Brick_Hit[i]){
                if (Bounce(&Ball_Pos, &Brick_Pos[i], &BallSpeed)){
                    Brick_Hit[i] = 0;
                }
            }
        }

        // We add the speed to the ball each frame
        if (BallThrown){
            BallFPos.x += BallSpeed.x;
            BallFPos.y += BallSpeed.y;
        }

        // Updating on screen ball position
        Ball_Pos.x = (int)BallFPos.x;
        Ball_Pos.y = (int)BallFPos.y;

        // Drawing Everything On Screen
        #ifdef _SDL
        SDL_BlitSurface(Background_Surface, NULL, screen, NULL); // Draw the background
        SDL_BlitSurface(SpriteSheet_Surface, &Ball_Rect, screen, &Ball_Pos); // Draw the ball
        SDL_BlitSurface(SpriteSheet_Surface, &Pad_Rect, screen, &Pad_Pos); // Draw the bottom bar
        for (i = 0; i < (BRICK_X*BRICK_Y); i++){
            if (Brick_Hit[i]){
                SDL_BlitSurface(SpriteSheet_Surface, &Brick_Rect[Brick_Color[i]], screen, &Brick_Pos[i]); // Draw the briks
            }
        }
        SDL_BlitSurface(Hud_Surface, NULL, screen, NULL); // Draw the Hud
        for (i = 0; i < (int)Lives; i++){
            //SDL_BlitSurface(Heart_Surface, NULL, screen, &(SDL_Rect){Heart_Pos.x + i * (Heart_Pos.h + 15), Heart_Pos.y, Heart_Pos.w, Heart_Pos.h}); // Draw the hearts
			Heart_Pos.x = 10 + i * (Heart_Pos.h + 15);
			SDL_BlitSurface(Heart_Surface, NULL, screen, &Heart_Pos);
        }

        SDL_Flip(screen);
        #else
        SDL_RenderClear(Renderer);
        SDL_RenderCopy(Renderer, Background_Texture, NULL, NULL); // Draw the background
        SDL_RenderCopy(Renderer, SpriteSheet_Texture, &Ball_Rect, &Ball_Pos); // Draw the ball
        SDL_RenderCopy(Renderer, SpriteSheet_Texture, &Pad_Rect, &Pad_Pos); // Draw the bottom bar
        for (i = 0; i < (BRICK_X*BRICK_Y); i++){
            if (Brick_Hit[i]){
                SDL_RenderCopy(Renderer, SpriteSheet_Texture, &Brick_Rect[Brick_Color[i]], &Brick_Pos[i]); // Draw the briks
            }
        }
        SDL_RenderCopy(Renderer, Hud_Texture, NULL, &Hud_Pos);// Draw the Hud
        for (int i = 0; i < Lives; i++){
            SDL_RenderCopy(Renderer, Heart_Texture, NULL, &(SDL_Rect){Heart_Pos.x + i * (Heart_Pos.h + 15), Heart_Pos.y, Heart_Pos.w, Heart_Pos.h}); // Draw the hearts
        }
        SDL_RenderPresent(Renderer);
        #endif
        //SDL_Delay(16); // 60fps lock, kinda
    }

Shutdown:

    #ifdef _SDL
    SDL_FreeSurface(Background_Surface);
    #endif

    #ifdef _SDL2
    SDL_DestroyTexture(Background_Texture);
    #endif

    IMG_Quit();
    SDL_Quit();

    return 0;
}