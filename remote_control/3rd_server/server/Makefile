main:
	g++ -g server.cc ClientDb.cpp SocketManager.cpp -o server -lboost_thread  -pthread -lmongoclient -lboost_thread-mt -lboost_filesystem -lboost_system

mongo:
	g++ mongodb.cc -pthread -lmongoclient -lboost_thread-mt -lboost_filesystem -lboost_system -o mongodb
