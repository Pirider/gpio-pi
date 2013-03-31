main:
	g++ server.cc -o server -lboost_thread

mongo:
	g++ mongodb.cc -pthread -lmongoclient -lboost_thread-mt -lboost_filesystem -lboost_system -o mongo
