.PHONY: all prepare compile link clean

CC=g++
CFLAGS=-std=gnu++17 -c
INCLUDES=-Iinclude
EXECUTABLE=lab-06_int-vector

all: prepare compile link

prepare: obj

obj:
	mkdir obj

compile: obj/main.o obj/my_vector.o

obj/main.o: src/main.cpp
	$(CC) $(CFLAGS) $(INCLUDES) src/main.cpp -o obj/main.o

obj/my_vector.o: src/my_vector.cpp
	$(CC) $(CFLAGS) $(INCLUDES) src/my_vector.cpp -o obj/my_vector.o

link: $(EXECUTABLE)

$(EXECUTABLE): obj/main.o obj/my_vector.o
	$(CC) obj/*.o -o $(EXECUTABLE)

clean:
	rm -rf obj/*.o $(EXECUTABLE)

