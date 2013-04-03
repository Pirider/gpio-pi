/*
 * ClientDb.cpp
 *
 *  Created on: 2013-4-3
 *      Author: m
 */

#include "ClientDb.h"


ClientDb::~ClientDb() {
	// TODO Auto-generated destructor stub
}

ClientDb::ClientDb() {
  c.connect("localhost");
}

void ClientDb::addclient(char* url, int port) {
  BSONObj p = BSON( "url" << url << "port" << port );
  c.insert("gpio_pi.client", p);
}
