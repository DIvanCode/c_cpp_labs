.PHONY: all prepare compile link clean

CC=gcc
CFLAGS=-c -Wall -Werror -Wextra
INCLUDES=-Iinclude
EXECUTABLE=lab-04_intrusive-list

all: prepare compile link

prepare: obj

obj:
	mkdir obj

compile: obj/main.o obj/clist.o

obj/main.o: src/main.c
	$(CC) $(CFLAGS) $(INCLUDES) src/main.c -o obj/main.o

obj/clist.o: src/clist.c
	$(CC) $(CFLAGS) $(INCLUDES) src/clist.c -o obj/clist.o

link: $(EXECUTABLE)

$(EXECUTABLE): obj/main.o obj/clist.o
	$(CC) obj/*.o -o $(EXECUTABLE)

clean:
	rm -rf obj/*.o $(EXECUTABLE)
