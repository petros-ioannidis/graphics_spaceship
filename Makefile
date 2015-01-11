CC=gcc
CFLAGS=-c -Wall -lGL -lGLU -lglut
LDFLAGS=-lGL -lGLU -lglut
SOURCES=spaceship.c main.c
OBJECTS=$(SOURCES:.c=.o)
VPATH=src:headers
EXECUTABLE=spaceship

all: $(SOURCES) $(EXECUTABLE)
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY : clean
clean:
	rm -rvf $(OBJECTS)
