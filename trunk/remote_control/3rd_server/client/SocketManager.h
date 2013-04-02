/*
 * SocketManager.h
 *
 *  Created on: 2013-4-2
 *      Author: m
 */
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include <iostream>
#include <stdio.h>
#include<string.h>
#include<strings.h>
#include "Poco/Thread.h"
#include "Poco/RunnableAdapter.h"


using namespace std;

#ifndef SOCKETMANAGER_H_
#define SOCKETMANAGER_H_

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
	virtual ~SocketManager();
};

#endif /* SOCKETMANAGER_H_ */
