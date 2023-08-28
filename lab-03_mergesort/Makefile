.PHONY: all prepare compile link clean

CC=gcc
CFLAGS=-c -Wall -Werror -Wextra
INCLUDES=-Iinclude
EXECUTABLE=lab-03_mergesort

all: prepare compile link

prepare: obj

obj:
	mkdir obj

compile: obj/main.o obj/mergesort.o

obj/main.o: src/main.c
	$(CC) $(CFLAGS) $(INCLUDES) src/main.c -o obj/main.o

obj/mergesort.o: src/mergesort.c
	$(CC) $(CFLAGS) $(INCLUDES) src/mergesort.c -o obj/mergesort.o

link: $(EXECUTABLE)

$(EXECUTABLE): obj/main.o obj/mergesort.o
	$(CC) obj/*.o -o $(EXECUTABLE)

clean:
	rm -rf obj/*.o $(EXECUTABLE)