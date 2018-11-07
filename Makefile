CC = g++
CFLAGS = -Wall -std=c++11 `pkg-config --cflags glew glfw3`
LFLAGS = `pkg-config --static --libs glew glfw3`
SOURCES = $(wildcard src/*.cc)
OBJECTS = $(SOURCES:.cc=.o)
TARGET = bin/circle_evader

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LFLAGS) -o $@ $^

%.o: %.cc
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf src/*.o

rebuild: clean all

open: rebuild
	./$(TARGET)
