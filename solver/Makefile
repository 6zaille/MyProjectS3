all: solver draw

solver: solver.c
	gcc -o $@ $^

draw: draw.c
	gcc -o $@ $^ `pkg-config --cflags --libs sdl2` -lSDL2_ttf -lSDL2_image

clean:
	rm -f solver draw
