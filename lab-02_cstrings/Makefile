.PHONY: all prepare compile link clean

CC=gcc
CFLAGS=-c -Wall -Werror -Wextra
INCLUDES=-Iinclude
EXECUTABLE=lab-02_cstrings

all: prepare compile link

prepare: obj

obj:
	mkdir obj

compile: obj/str.o obj/test_str.o obj/test.o

obj/str.o: src/str.c
	$(CC) $(CFLAGS) $(INCLUDES) src/str.c -o obj/str.o

obj/test_str.o: src/test_str.c
	$(CC) $(CFLAGS) $(INCLUDES) src/test_str.c -o obj/test_str.o

obj/test.o: src/test.c
	$(CC) $(CFLAGS) $(INCLUDES) src/test.c -o obj/test.o

link: $(EXECUTABLE)

$(EXECUTABLE): obj/str.o obj/test_str.o obj/test.o
	$(CC) obj/*.o -o $(EXECUTABLE)

clean:
	rm -rf obj/*.o $(EXECUTABLE)
