SDL2:
	gcc -o ARKANOTRON src/*.c -Iinclude $$(sdl2-config --cflags --libs) -lSDL2_image -lSDL2_mixer -lm
	./ARKANOTRON

SDL:
	gcc -o ARKANOTRON src/*.c -Iinclude -lSDL -lSDL_image -lSDL_mixer -lm
	./ARKANOTRON
	
run:
	./ARKANOTRON