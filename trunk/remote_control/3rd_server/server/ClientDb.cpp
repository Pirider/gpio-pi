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

void ClientDb::addclient(char *id, char* url, int port) {
	auto_ptr<DBClientCursor> cursor = c.query("gpio_pi.client", QUERY("url" << url));
	while (cursor->more()) {
	    BSONObj p = cursor->next();
	    cout << p.getStringField("url") << endl;
	    return;
	}

	BSONObj p = BSON("id" << id << "url" << url << "port" << port);
	c.insert("gpio_pi.client", p);
}
