/*
 * Pi.cpp
 *
 *  Created on: 2013-4-3
 *      Author: m
 */

#include "Pi.h"
#include <wiringPi.h>
#include <iostream>
using namespace std;

Pi::Pi() {
	// TODO Auto-generated constructor stub
	 if (-1 == wiringPiSetup()) {
	    cout << "Setup wiringPi failed!" << endl;
	  }
}

void setValue() {
	pinMode(4, OUTPUT); // set mode to output
	digitalWrite(4, 1); // output a high level
}

void getVaule() {

}

Pi::~Pi() {
	// TODO Auto-generated destructor stub
}
