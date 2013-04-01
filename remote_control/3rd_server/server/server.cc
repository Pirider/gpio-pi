#include <iostream>
#include <boost/thread/thread.hpp>
using namespace std;

#include <stdio.h>
#include<string.h>
#include<strings.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include <ctype.h>
#include "mongo/client/dbclient.h"
using namespace mongo;
using namespace bson;
class SocketManager;
class ClientDb;

SocketManager *socket_manage;
ClientDb *client_db;

#define SERV_UDP_PORT 6501
class ClientDb {
    public:
        ClientDb();
        void addclient(char *url, int port); 
    private:
        mongo::DBClientConnection c;
};

ClientDb::ClientDb() {
  c.connect("localhost");
}

void ClientDb::addclient(char* url, int port) {
  BSONObj p = BSON( "url" << url << "port" << port );
  c.insert("gpio_pi.client", p);
}

class SocketManager {
    private:
        int sockfd, n, struct_len, i, str_len;
        struct sockaddr_in server_addr;
        struct sockaddr_in client_addr;
        char sendline[512], recvline[513];
        void notify();
        void send();
    public:
        SocketManager();
};

SocketManager::SocketManager() {
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero((char *)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERV_UDP_PORT);

    struct_len = sizeof(server_addr);
    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    boost::thread* thr1 = new boost::thread(boost::bind(&SocketManager::notify, this));
    boost::thread* thr2 = new boost::thread(boost::bind(&SocketManager::send, this));
    thr1->join( );
    thr2->join( );
}

void SocketManager::notify() {
    for(;;){
        n = recvfrom(sockfd, recvline, 512, 0, (struct sockaddr *) &client_addr,  (socklen_t *) &struct_len);
        client_db->addclient(inet_ntoa(client_addr.sin_addr), client_addr.sin_port); 
        i=0;
        while(recvline[i] != '\0'){
            recvline[i]=toupper(recvline[i]);
            i++;
        }
        recvline[n]=0;
        fputs(recvline, stdout);
        fflush(stdout);
        str_len=strlen(recvline);
    }
}

void SocketManager::send() {
	for (;;) {
		string strs;
		cin >> strs;
		sendto(sockfd, strs.c_str(), strs.length(), 0,
				(struct sockaddr *) &client_addr, sizeof(client_addr));
	}
}


int main(){
    client_db = new ClientDb;
    socket_manage =  new SocketManager; 
}
