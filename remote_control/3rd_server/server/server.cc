

#include "ClientDb.h"
#include "SocketManager.h"

SocketManager *socket_manage;
ClientDb *client_db;


int main(){
    client_db = new ClientDb;
    socket_manage =  new SocketManager; 
}
