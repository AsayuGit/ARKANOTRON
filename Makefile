SDL2:
	gcc -o main main.c $$(sdl2-config --cflags --libs)
	./main

SDL:
	gcc -o main main.c -lSDL
	./main
	
run:
	./main