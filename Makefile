CC=g++
CFLAGS=-c -std=c++11 
LDFLAGS=
SOURCES=main.cpp cuckoo.cpp bloom.cpp noFilter.cpp hashing.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXE=program

$(EXE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $<

all: $(SOURCES) $(EXE)

.PHONY: clean

clean:
	rm -f *.o *.exe