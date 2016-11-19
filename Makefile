CC=g++
MPICPP=mpic++
MPICXX=mpicxx
CFLAGS=-c -Wall -std=c++0x -fopenmp
LDFLAGS=-lm -lgomp 
SOURCES=src/main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=task2-solver

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(MPICPP) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(MPICPP) $(CFLAGS) $< -o $@

clean:
	rm -rf src/*.o 
