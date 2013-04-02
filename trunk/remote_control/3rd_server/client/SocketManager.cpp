/*
 * SocketManager.cpp
 *
 *  Created on: 2013-4-2
 *      Author: m
 */

#include "SocketManager.h"


SocketManager::~SocketManager() {
	// TODO Auto-generated destructor stub
}

SocketManager::SocketManager() {
	bzero((char*) &sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR_0);
	sa.sin_port = htons(SERV_UDP_PORT);

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	flag = 1;

	Timer timer(0, 5000);
	timer.start(TimerCallback<SocketManager>(*this, &SocketManager::send));
	Poco::RunnableAdapter<SocketManager> runnable(*this,
			&SocketManager::notify);
	Poco::Thread thread;
	thread.start(runnable);
	thread.join();
}

void SocketManager::notify() {
	for (;;) {
		n = recvfrom(sockfd, recvline, 512, 0, (struct sockaddr *) 0,
				(socklen_t *) 0);
		recvline[n] = 0;
		printf("Return -->");
		fputs(recvline, stdout);
		fflush (stdout);
	}
}


void SocketManager::send(Timer& timer) {
		string me = "wangkangluo1";
		str_len = strlen(sendline2);
		sendto(sockfd, me.c_str(), me.length(), 0, (struct sockaddr *) &sa,
				sizeof(sa));
}
