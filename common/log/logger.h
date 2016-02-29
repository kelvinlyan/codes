#ifndef _LOG_LOGGER_H
#define _LOG_LOGGER_H

#include "node/data_slot.h"
#include "node/collector.h"

namespace Log
{
	enum{
		TRACE = 0,
		DEBUG,
		INFO,
		WARNING,
		ERROR,
		FATAL
	};

	const char* Severitys[] = {
		"TRACE",
		"DEBUG",
		"INFO",
		"WARNING",
		"ERROR",
		"FATAL"
	};

	class Logger
	{
		public:
			static Logger* create()
			{
				return new Logger();
			}

			Collector rcd(const int severity = INFO, const std::string& tag = "")
			{
				return Collector(severity, tag, time(NULL), &_slot);
			}

			void addSink(Node* n)
			{
				_slot.addSink(n);
			}

		private:
			Logger(){}

		private:
			DataSlot _slot;
	};
}

#endif
