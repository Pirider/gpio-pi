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
#include "Poco/Timer.h"
#include "Poco/Stopwatch.h"

using namespace std;
using Poco::Timer;
using Poco::TimerCallback;
using Poco::Thread;
using Poco::Stopwatch;

#ifndef SOCKETMANAGER_H_
#define SOCKETMANAGER_H_

#define SERV_HOST_ADDR_0 "106.187.47.234"
#define SERV_UDP_PORT 6501

class SocketManager {
private:
	int sockfd, str_len, flag, n;
	  struct sockaddr_in sa;
	  char sendline[512], sendline2[513], recvline[513];
	void notify();
	void send(string &msg);
	void beat(Timer& timer);

public:
	SocketManager();
	virtual ~SocketManager();
};

#endif /* SOCKETMANAGER_H_ */
