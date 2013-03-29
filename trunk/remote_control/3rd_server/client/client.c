#include <stdio.h>
#include<string.h>
#include<strings.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define SERV_HOST_ADDR_0 "106.187.47.234"
#define SERV_UDP_PORT 6501

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
