CC=g++
CFLAGS=-c -g
LDFLAGS=-lPocoFoundation -lwiringPi
SOURCES=client.cpp SocketManager.cpp Pi.cpp Log.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=client

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC)  $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *o client