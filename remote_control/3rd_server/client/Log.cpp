/*
 * Log.cpp
 *
 *  Created on: 2013-4-3
 *      Author: m
 */

#include "Log.h"

Log::Log() {
	// TODO Auto-generated constructor stub
	pFCApp = new FormattingChannel(
			new PatternFormatter("[%Y-%m-%d %H-%M-%S.%c %N %P %l %s %q ]%t"));
	pFCApp->setChannel(new FileChannel("./app.log"));
	pFCApp->open();
}

void Log::info(char* msg) {
	Logger& appLogger = Logger::create("AppLog", pFCApp, Message::PRIO_INFORMATION);
	appLogger.information(msg);
}

Log::~Log() {
	// TODO Auto-generated destructor stub
    pFCApp->close();
    //delete appLogger;
}

