CC=g++
CFLAGS=-c -Wall
LDFLAGS= -lncurses
SOURCES=main.cpp ../common/curse_extras.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=midnightbox

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
