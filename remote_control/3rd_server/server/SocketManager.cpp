/*
 * SocketManager.cpp
 *
 *  Created on: 2013-4-3
 *      Author: m
 */

#include "SocketManager.h"
#include "ClientDb.h"

extern ClientDb *client_db;

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
