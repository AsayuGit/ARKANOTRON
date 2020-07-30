SDL2:
	gcc -o main main.c $$(sdl2-config --cflags --libs) -lSDL2_image
	./main

SDL:
	gcc -o main main.c -lSDL -lSDL_image
	./main
	
run:
	./main