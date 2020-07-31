#include "include.h"

int main(int argc, char *argv[]){

// Vars
    SDL_Window* screen = NULL;
    SDL_Surface* Background_Surface = NULL;
    SDL_Surface* SpriteSheet_Surface = NULL;

    SDL_Rect BottomBar_Rect, Ball_Rect;
    ARK_Position BottomBar_Pos, Ball_Pos;

    Vector2f BallSpeed, BallFPos;

    #ifdef _SDL2
    SDL_Renderer* Renderer;
    SDL_Texture* Background_Texture = NULL;
    SDL_Texture* SpriteSheet_Texture = NULL;
    #endif

// Code
    
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
    #else
    screen = SDL_CreateWindow("Henlo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_X, SCREEN_Y, SDL_WINDOW_SHOWN);
    Renderer = SDL_CreateRenderer(screen, -1, 0);
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
    BottomBar_Rect = (SDL_Rect){0, 111, 160, 25};
    Ball_Rect = (SDL_Rect){0, 81, 23, 22};

    // Settings position and Logic

    // Default pos
    BottomBar_Pos = (ARK_Position){(SCREEN_X - BottomBar_Rect.w) >> 1, 0, BottomBar_Rect.w, BottomBar_Rect.h};
    ScaleLine((int*)(&(BottomBar_Pos.y)), SCREEN_Y, 0.9f);

    BallFPos.x = (SCREEN_X - Ball_Rect.w) >> 1;
    BallFPos.y = (SCREEN_Y - Ball_Rect.h) >> 1;
    Ball_Pos = (ARK_Position){(int)BallFPos.x, (int)BallFPos.y, Ball_Rect.w, Ball_Rect.h};

    BallSpeed.x = 5.0f;
    BallSpeed.y = 5.0f;

    while (1){

        // Frame actions
        
        // Bounce with the wall
        if (((BallFPos.x + (Ball_Rect.w >> 1)) > SCREEN_X) || ((BallFPos.x + (Ball_Rect.w >> 1)) < 0)){
            BallSpeed.x = -BallSpeed.x;
        }
        if (((BallFPos.y + (Ball_Rect.h >> 1)) > SCREEN_Y) || ((BallFPos.y + (Ball_Rect.h >> 1)) < 0)){
            BallSpeed.y = -BallSpeed.y;
        }

        // We add the speed to the ball each frame
        printf("BallPos BEFORE %f %f\n", BallFPos.x, BallFPos.y);
        BallFPos.x += BallSpeed.x;
        BallFPos.y += BallSpeed.y;

        printf("Ballspeed %f %f\n", BallSpeed.x, BallSpeed.y);
        printf("BallPos AFTER %f %f\n", BallFPos.x, BallFPos.y);

        // Updating on screen ball position
        Ball_Pos.x = (int)BallFPos.x;
        Ball_Pos.y = (int)BallFPos.y;

        // Drawing Everything On Screen
        #ifdef _SDL
        SDL_BlitSurface(Background_Surface, NULL, screen, NULL); // Draw the background
        SDL_BlitSurface(SpriteSheet_Surface, &Ball_Rect, screen, &Ball_Pos); // Draw the ball
        SDL_BlitSurface(SpriteSheet_Surface, &BottomBar_Rect, screen, &BottomBar_Pos); // Draw the bottom bar
        SDL_Flip(screen);
        #else
        SDL_RenderClear(Renderer);
        SDL_RenderCopy(Renderer, Background_Texture, NULL, NULL); // Draw the background
        SDL_RenderCopy(Renderer, SpriteSheet_Texture, &Ball_Rect, &Ball_Pos); // Draw the ball
        SDL_RenderCopy(Renderer, SpriteSheet_Texture, &BottomBar_Rect, &BottomBar_Pos); // Draw the bottom bar
        SDL_RenderPresent(Renderer);
        #endif
        SDL_Delay(16); // 60fps lock, kinda
    }

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