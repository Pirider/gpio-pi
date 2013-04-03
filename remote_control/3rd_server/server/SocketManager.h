/*
 * SocketManager.h
 *
 *  Created on: 2013-4-3
 *      Author: m
 */



#ifndef SOCKETMANAGER_H_
#define SOCKETMANAGER_H_

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
        struct sockaddr_in server_addr;
        struct sockaddr_in client_addr;
        char sendline[512], recvline[513];
        void notify();
        void send();
    public:
        SocketManager();
};



#endif /* SOCKETMANAGER_H_ */
