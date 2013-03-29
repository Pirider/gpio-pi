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
#define SERV_UDP_PORT 6501

class SocketManager {
    private:
        int sockfd, n, struct_len, i, str_len;
        struct sockaddr_in addr;
        struct sockaddr_in ca;
        char sendline[512], recvline[513];

    public:
        SocketManager();

};
SocketManager::SocketManager() {
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero((char *)&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(SERV_UDP_PORT);

    struct_len = sizeof(addr);
    bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));

    for(;;){
        n = recvfrom(sockfd, recvline, 512, 0, (struct sockaddr *) &ca,  (socklen_t *) &struct_len);
        printf("From %s[%d]", inet_ntoa(ca.sin_addr), ca.sin_port);

        i=0;
        while(recvline[i] != '\0'){    //大写转化
            recvline[i]=toupper(recvline[i]);
            i++;
        }
        recvline[n]=0;
        fputs(recvline, stdout);
        fflush(stdout);
        str_len=strlen(recvline);
        string strs;
        cin >> strs;
        sendto(sockfd, strs.c_str(), strs.length(), 0, (struct sockaddr *)&ca, sizeof(ca));
    }
}


int main(){
    SocketManager socket_manage;
}
