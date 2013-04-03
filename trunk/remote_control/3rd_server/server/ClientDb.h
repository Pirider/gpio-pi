/*
 * ClientDb.h

 *
 *  Created on: 2013-4-3
 *      Author: m
 */


#ifndef CLIENTDB_H_
#define CLIENTDB_H_

#include "mongo/client/dbclient.h"
using namespace mongo;
using namespace bson;



class ClientDb {
	 public:
        ClientDb();
        void addclient(char *url, int port);
    private:
        mongo::DBClientConnection c;
public:
	virtual ~ClientDb();
};

#endif /* CLIENTDB_H_ */
