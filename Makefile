SDL2:
	gcc -o main main.c GUI_Functions.c $$(sdl2-config --cflags --libs) -lSDL2_image
	./main

SDL:
	gcc -o main main.c GUI_Functions.c -lSDL -lSDL_image
	./main
	
run:
	./main