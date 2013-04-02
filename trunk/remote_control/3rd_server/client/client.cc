#include <iostream>
#include <stdio.h>
#include<string.h>
#include<strings.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include "Poco/Thread.h"
#include "Poco/RunnableAdapter.h"
using namespace std;

#define SERV_HOST_ADDR_0 "106.187.47.234"
#define SERV_UDP_PORT 6501


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
    Poco::RunnableAdapter<SocketManager> runnable1(*this, &SocketManager::notify);
    Poco::RunnableAdapter<SocketManager> runnable2(*this, &SocketManager::send);

    Poco::Thread thread1;
    thread1.start(runnable1);
    thread1.join();

    Poco::Thread thread2;
    thread2.start(runnable2);
    thread2.join();

}

void SocketManager::notify() {
    for(;;){
        n = recvfrom(sockfd, recvline, 512, 0, (struct sockaddr *) &client_addr,  (socklen_t *) &struct_len);
        //client_db->addclient(inet_ntoa(client_addr.sin_addr), client_addr.sin_port);
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


int main(int argc, char *argv[]){

  int sockfd, str_len, flag, n;
  struct sockaddr_in sa;
  char sendline[512], sendline2[513]="", recvline[513];

  if(argc > 2){
    printf("Please Input Your name!!\n");
    return 1;
  }
  bzero((char*)&sa, sizeof(sa));
  sa.sin_family = AF_INET;
  sa.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR_0);
  sa.sin_port = htons(SERV_UDP_PORT);

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  flag = 1;

  for(;;){
    printf("Send -->");
    fgets(sendline,512,stdin);

    if(argv[1] != NULL){
      strcpy(sendline2,argv[1]);
      strcat(sendline2, sendline);
    }else{
      strcpy(sendline2,sendline);
    }
    str_len = strlen(sendline2);
    sendto(sockfd, sendline2, str_len, 0, (struct sockaddr *)&sa, sizeof(sa));
    n = recvfrom(sockfd, recvline, 512, 0, (struct sockaddr *) 0,   (socklen_t *) 0);
    recvline[n]=0;
    printf("Return -->");
    fputs(recvline, stdout);
    fflush(stdout);
 }
}
