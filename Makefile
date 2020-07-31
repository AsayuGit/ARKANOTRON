SDL2:
	gcc -o main main.c GUI_Functions.c GAME_Functions.c $$(sdl2-config --cflags --libs) -lSDL2_image -lm
	./main

SDL:
	gcc -o main main.c GUI_Functions.c GAME_Functions.c -lSDL -lSDL_image -lm
	./main
	
run:
	./main