CC=gcc
CFLAGS=-c -Wall -lGL -lGLU -lglut -lm
LDFLAGS=-lGL -lGLU -lglut -lm
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
