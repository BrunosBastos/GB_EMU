.PHONY: all clean

CC = g++
CFLAGS = -w -g
LDFLAGS = -lm
OBJFILES = $(wildcard *.cpp)

TARGET = main

all: clean $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS) `sdl2-config --cflags --libs`

clean:
	rm -f *.o
