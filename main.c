#include "include.h"

int main(int argc, char *argv[]){

// Vars
    SDL_Window* screen = NULL;
    SDL_Surface* hello_Surface = NULL;
    SDL_Surface* SpriteSheet_Surface = NULL;

    #ifdef _SDL2
    SDL_Renderer* Renderer;
    SDL_Texture* hello_Texture = NULL;
    SDL_Texture* SpriteSheet_Texture = NULL;
    #endif

// Code
    
    // SDL Init
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        fprintf(stderr, "SDL Initialisation failed\n");
    }
    // SDL_Image Init
    if(IMG_Init(IMG_INIT_PNG) != 0){
        fprintf(stderr, "SDL Initialisation failed\n");
    }

    
    printf("Hey everything works :3\n");
    
    #ifdef _SDL
    screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
    #else
    screen = SDL_CreateWindow("Henlo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_X, SCREEN_Y, SDL_WINDOW_SHOWN);
    Renderer = SDL_CreateRenderer(screen, -1, 0);
    #endif

    // Loading Sprites
    hello_Surface = SDL_LoadBMP(ROOT"hello.bmp");
    if (hello_Surface == NULL){
        fprintf(stderr, "Can't load HelloSurface !\n");
    }
    SpriteSheet_Surface = IMG_Load(ROOT""_TEXTURE"BasicArkanoidPack.png");
    if (SpriteSheet_Surface == NULL){
        fprintf(stderr, "Can't load SpriteSheet_Surface !\n%s\n", IMG_GetError());
    }
    #ifdef _SDL2
    hello_Texture = SDL_CreateTextureFromSurface(Renderer, hello_Surface);
    SDL_FreeSurface(hello_Surface);
    SpriteSheet_Texture = SDL_CreateTextureFromSurface(Renderer, SpriteSheet_Surface);
    SDL_FreeSurface(SpriteSheet_Surface);
    #endif

    // Drawing Everything On Screen
    #ifdef _SDL
    SDL_BlitSurface(hello_Surface, NULL, screen, NULL);
    SDL_BlitSurface(SpriteSheet_Surface, NULL, screen, NULL);
    SDL_Flip(screen);
    #else
    SDL_RenderClear(Renderer);
    SDL_RenderCopy(Renderer, hello_Texture, NULL, NULL);
    SDL_RenderCopy(Renderer, SpriteSheet_Texture, NULL, NULL);
    SDL_RenderPresent(Renderer);
    #endif


    SDL_Delay(2000);

    #ifdef _SDL
    SDL_FreeSurface(hello_Surface);
    #endif

    #ifdef _SDL2
    SDL_DestroyTexture(hello_Texture);
    
    #endif

    IMG_Quit();
    SDL_Quit();

    return 0;
}