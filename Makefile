SDL2:
	gcc -o ARKANOTRON ARKANOTRON.c GUI_Functions.c GAME_Functions.c $$(sdl2-config --cflags --libs) -lSDL2_image -lSDL2_mixer -lm
	./ARKANOTRON

SDL:
	gcc -o ARKANOTRON ARKANOTRON.c GUI_Functions.c GAME_Functions.c -lSDL -lSDL_image -lSDL_mixer -lm
	./ARKANOTRON
	
run:
	./ARKANOTRON