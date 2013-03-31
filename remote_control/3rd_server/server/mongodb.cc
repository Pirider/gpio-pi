/*
 * =====================================================================================
 *
 *       Filename:  mongodb.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/31/2013 05:25:58 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kangle.wang (mn), wangkangluo1@gmail.com
 *        Company:  APE-TECH
 *
 * =====================================================================================
 */

#include <cstdlib>
#include <iostream>
#include "mongo/client/dbclient.h"

void run() {
  mongo::DBClientConnection c;
  c.connect("localhost");
}

int main() {
  try {
    run();
    std::cout << "connected ok" << std::endl;
  } catch( const mongo::DBException &e ) {
    std::cout << "caught " << e.what() << std::endl;
  }
  return EXIT_SUCCESS;
}
