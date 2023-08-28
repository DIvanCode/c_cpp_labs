.PHONY: all prepare compile link clean

CC=gcc
CFLAGS=-c
INCLUDES=-Iinclude
EXECUTABLE=hw-01_bmp

all: prepare compile link

prepare: obj

obj:
	mkdir obj

compile: obj/main.o obj/bmp.o

obj/main.o: src/main.c
	$(CC) $(CFLAGS) $(INCLUDES) src/main.c -o obj/main.o

obj/bmp.o: src/bmp.c
	$(CC) $(CFLAGS) $(INCLUDES) src/bmp.c -o obj/bmp.o

link: $(EXECUTABLE)

$(EXECUTABLE): obj/main.o obj/bmp.o
	$(CC) obj/*.o -o $(EXECUTABLE)

clean:
	rm -rf obj/*.o $(EXECUTABLE)

