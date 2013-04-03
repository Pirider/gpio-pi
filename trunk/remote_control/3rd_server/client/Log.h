/*
 * Log.h
 *
 *  Created on: 2013-4-3
 *      Author: m
 */

#ifndef LOG_H_
#define LOG_H_

#include "Poco/FormattingChannel.h"
#include "Poco/FileChannel.h"
#include "Poco/PatternFormatter.h"
#include "Poco/Logger.h"

using Poco::Message;
using Poco::PatternFormatter;
using Poco::FileChannel;
using Poco::FormattingChannel;
using std::string;
using Poco::Logger;

class Log {
private:
	FormattingChannel* pFCApp;
public:
	Log();
	void info(char* msg);
	virtual ~Log();
};


#endif /* LOG_H_ */
