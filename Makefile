
CC=gcc
LDFLAGS= -g -lm
CFLAGS=-Wextra -g -pedantic -ansi -std=c99 -I inc

all: main

obj/image.o: src/image.c inc/image.h
obj/image_util.o: src/image_util.c inc/image_util.h
obj/quadtree.o: src/quadtree.c inc/quadtree.h
obj/quadAppDesc.o: src/quadAppDesc.c inc/quadAppDesc.h
obj/main.o: src/main.c

obj/%.o: src/%.c
	$(CC) -c $< -o $@ $(CFLAGS)
main: obj/main.o obj/image.o obj/image_util.o obj/quadtree.o obj/quadAppDesc.o
	$(CC) $^ -o $@ $(LDFLAGS)
clean:
	-rm obj/*o
distclean:
	-rm main
