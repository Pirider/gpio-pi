CC=g++
CFLAGS=-c -g
LDFLAGS=-lPocoUtil -lPocoXML -lPocoFoundation -lboost_thread  -pthread -lmongoclient -lboost_thread-mt -lboost_filesystem -lboost_system
SOURCES=server.cc\
ClientDb.cpp\
SocketManager.cpp

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=server

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC)  $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *o server
	