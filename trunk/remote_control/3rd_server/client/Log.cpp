/*
 * Log.cpp
 *
 *  Created on: 2013-4-3
 *      Author: m
 */

#include "Log.h"
#include "Poco/Logger.h"
#include "Poco/PatternFormatter.h"
#include "Poco/FormattingChannel.h"
#include "Poco/ConsoleChannel.h"
#include "Poco/FileChannel.h"
#include "Poco/Message.h"


using Poco::Logger;
using Poco::PatternFormatter;
using Poco::FormattingChannel;
using Poco::ConsoleChannel;
using Poco::FileChannel;
using Poco::Message;

Log::Log() {/*
	// TODO Auto-generated constructor stub
	FormattingChannel* pFCApp = new FormattingChannel(
			new PatternFormatter("[%Y-%m-%d %H-%M-%S.%c %N %P %l %s %q ]%t"));

	pFCApp->setChannel(new FileChannel("./FCApp.log"));

	pFCApp->open();

	Logger& appLogger = Logger::create("FCAppLog", pFCApp,
			Message::PRIO_INFORMATION);
	for (int i = 0; i < 10; i++) {
		string msg;
		msg += "FCAppLog information";
		appLogger.information(msg);
	}*/

	FormattingChannel* pFCConsole = new FormattingChannel(
			new PatternFormatter("%s: %p: %t"));
	pFCConsole->setChannel(new ConsoleChannel);
	pFCConsole->open();

	FormattingChannel* pFCFile = new FormattingChannel(
			new PatternFormatter("%Y-%m-%d %H:%M:%S.%c %N[%P]:%s:%q:%t"));
	pFCFile->setChannel(new FileChannel("sample.log"));
	pFCFile->open();

	// create two Logger objects - one for
	// each channel chain.
	Logger& consoleLogger = Logger::create("ConsoleLogger", pFCConsole,
			Message::PRIO_INFORMATION);
	Logger& fileLogger = Logger::create("FileLogger", pFCFile,
			Message::PRIO_WARNING);

	// log some messages
	consoleLogger.error("An error message");
	fileLogger.error("An error message");

	consoleLogger.warning("A warning message");
	fileLogger.error("A warning message");

	consoleLogger.information("An information message");
	fileLogger.information("An information message");

	poco_information(consoleLogger, "Another informational message");
	//poco_warning_f2(consoleLogger, "A warning message with arguments: %d, %d",1, 2);

	//Logger::get("ConsoleLogger").error("Another error message");

}



Log::~Log() {
	// TODO Auto-generated destructor stub
	// pFCApp->close();
}

