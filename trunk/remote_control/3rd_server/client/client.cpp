
#include "Poco/Thread.h"
#include "Poco/RunnableAdapter.h"
#include "SocketManager.h"
#include "Pi.h"
#include "Log.h"

using namespace std;

#define SERV_HOST_ADDR_0 "106.187.47.234"
#define SERV_UDP_PORT 6501

Pi *pi = NULL;
Log *log = NULL;

int main(int argc, char *argv[]){
	log = new Log();
	log->info("wangkangluo1");
	SocketManager socket_manager;
	pi = new Pi();
}
