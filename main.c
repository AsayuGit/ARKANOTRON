#include "include.h"

int main(int argc, char *argv[]){

// Vars
    SDL_Window* screen = NULL;
    SDL_Surface* Background_Surface = NULL;
    SDL_Surface* SpriteSheet_Surface = NULL;

    SDL_Rect Pad_Rect, Ball_Rect;
    SDL_Rect Brick_Rect[8];
    ARK_Position Pad_Pos, Ball_Pos;
    ARK_Position Brick_Pos[BRICK_X*BRICK_Y];
    char Brick_Hit[BRICK_X*BRICK_Y] = {0};
    char Brick_Color[BRICK_X*BRICK_Y] = {0};

    Vector2f BallSpeed, BallFPos, PadFPos;
    char BallSides;
    float PadSpeed;

    SDL_Event event;
    const Uint8* KeyStates;

    #ifdef _SDL2
    SDL_Renderer* Renderer;
    SDL_Texture* Background_Texture = NULL;
    SDL_Texture* SpriteSheet_Texture = NULL;
    #endif

    int i, j, k;

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
    #ifdef _SDL2
    Background_Texture = SDL_CreateTextureFromSurface(Renderer, Background_Surface);
    SDL_FreeSurface(Background_Surface);
    SpriteSheet_Texture = SDL_CreateTextureFromSurface(Renderer, SpriteSheet_Surface);
    SDL_FreeSurface(SpriteSheet_Surface);
    #endif
    Pad_Rect = (SDL_Rect){0, 111, 160, 25};
    Ball_Rect = (SDL_Rect){0, 81, 23, 22};
    for (i = 0; i < 2; i++){
        for (j = 0; j < 4; j++){
            Brick_Rect[j + (i * 4)] = (SDL_Rect){j * 72, i * 40, 65, 32};
        }
    }

    // Settings position and Logic

    // Default pos
    PadFPos.x = (SCREEN_X - Pad_Rect.w) >> 1;
    Pad_Pos = (ARK_Position){(int)PadFPos.x, PadFPos.y, Pad_Rect.w, Pad_Rect.h};
    ScaleLine((int*)(&(Pad_Pos.y)), SCREEN_Y, 0.9f);
    PadFPos.y = (float)Pad_Pos.y;

    BallFPos.x = (SCREEN_X - Ball_Rect.w) >> 1;
    BallFPos.y = (SCREEN_Y - Ball_Rect.h) >> 1;
    Ball_Pos = (ARK_Position){(int)BallFPos.x, (int)BallFPos.y, Ball_Rect.w, Ball_Rect.h};

    for (i = 0; i < BRICK_Y; i++){
        for (j = 0; j < BRICK_X; j++){
            Brick_Pos[j + (i * BRICK_X)] = (SDL_Rect){j * 65, i * 32, 65, 32}; // init the briks
            Brick_Color[j + (i * BRICK_X)] = rand()%8; // init their colors
        }
    }

    BallRespown(&BallSpeed, BALLSPEED);
    PadSpeed = PADSPEED;

    while (1){

        // Frame actions

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
                
                default:
                    break;
                }
                break;
            
            default:
                break;
            }
        }

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
        if ((BallFPos.y + (Ball_Rect.h >> 1)) < 0){
            BallSpeed.y = -BallSpeed.y;
        }

        if ((BallFPos.y + (Ball_Rect.h >> 1)) > SCREEN_Y){ // Ball Over
            BallFPos.x = (SCREEN_X - Ball_Rect.w) >> 1;
            BallFPos.y = (SCREEN_Y - Ball_Rect.h) >> 1;
            BallRespown(&BallSpeed, BALLSPEED);
        }


        // Bounce with the Bar
        Bounce(&Ball_Pos, &Pad_Pos, &BallSpeed);

        // Bounce with the bricks
        for (i = 0; i < (BRICK_X*BRICK_Y); i++){
            if (!Brick_Hit[i]){
                if (Bounce(&Ball_Pos, &Brick_Pos[i], &BallSpeed)){
                    Brick_Hit[i] = 1;
                }
            }
        }

        // We add the speed to the ball each frame
        //printf("BallPos BEFORE %f %f\n", BallFPos.x, BallFPos.y);
        BallFPos.x += BallSpeed.x;
        BallFPos.y += BallSpeed.y;

        //printf("Ballspeed %f %f\n", BallSpeed.x, BallSpeed.y);
        //printf("BallPos AFTER %f %f\n", BallFPos.x, BallFPos.y);

        // Updating on screen ball position
        Ball_Pos.x = (int)BallFPos.x;
        Ball_Pos.y = (int)BallFPos.y;

        // Drawing Everything On Screen
        #ifdef _SDL
        SDL_BlitSurface(Background_Surface, NULL, screen, NULL); // Draw the background
        SDL_BlitSurface(SpriteSheet_Surface, &Ball_Rect, screen, &Ball_Pos); // Draw the ball
        SDL_BlitSurface(SpriteSheet_Surface, &Pad_Rect, screen, &Pad_Pos); // Draw the bottom bar
        for (i = 0; i < (BRICK_X*BRICK_Y); i++){
            if (!Brick_Hit[i]){
                SDL_BlitSurface(SpriteSheet_Surface, &Brick_Rect[Brick_Color[i]], screen, &Brick_Pos[i]); // Draw the briks
            }
        }
        SDL_Flip(screen);
        #else
        SDL_RenderClear(Renderer);
        SDL_RenderCopy(Renderer, Background_Texture, NULL, NULL); // Draw the background
        SDL_RenderCopy(Renderer, SpriteSheet_Texture, &Ball_Rect, &Ball_Pos); // Draw the ball
        SDL_RenderCopy(Renderer, SpriteSheet_Texture, &Pad_Rect, &Pad_Pos); // Draw the bottom bar
        for (i = 0; i < (BRICK_X*BRICK_Y); i++){
            if (!Brick_Hit[i]){
                SDL_RenderCopy(Renderer, SpriteSheet_Texture, &Brick_Rect[Brick_Color[i]], &Brick_Pos[i]); // Draw the briks
            }
        }
        SDL_RenderPresent(Renderer);
        #endif
        SDL_Delay(16); // 60fps lock, kinda
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