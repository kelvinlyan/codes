#include "logger.h"
#include "node/formatter.h"
#include "node/printer.h"

int main()
{
	Log::Logger& myLog = *(Log::Logger::create());
	Log::Formatter& formatter = *(Log::Formatter::create())
		% Log::LineNumber::create("[%04d] ", color::YELLOW)
		% Log::Time::create("[%Y-%02m-%02d %02H:%02M:%02S] ", color::GREEN)
		% Log::Severity::create(myLog, "[%s]: ", color::BLUE)
		% Log::Message::create(color::RED);
		% ("Time") % ()
	formatter.addSink(Log::Printer::create());
	myLog.addSink(&formatter);

	for(int i = 0; i < 10000; ++i)
	{
		myLog.rcd(i % 7) << "I am in test, count: " << i << "\n";
	}
}
