#include <iostream>
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

int main(){
  int sockfd, n, struct_len, i, str_len;
  struct sockaddr_in addr;
  struct sockaddr_in ca;
  char sendline[512], recvline[513];

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
	string str;
	cin >> str;
    sendto(sockfd, str.c_str(), str.length(), 0, (struct sockaddr *)&ca, sizeof(ca));
  }
}
