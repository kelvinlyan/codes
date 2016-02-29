#include <iostream>

#include "formatter.h"
#include "../attribute/time.h"
#include "../attribute/line_number.h"

class A
{
	public:
		A& operator%(int a)
		{
			_a = a;
			return *this;
		}

		int _a;
};

int main()
{
	Log::Formatter& f = (*(Log::Formatter::create()))
		.add("Time", "[%Y-%02m-%02d %02H:%02M:%02S]", color::YELLOW)
		.add("LineNumber", "[%02d]", color::RED)
		.add("Message", NULL, color::GREEN);

	Log::State s;
	std::cout << f.handle(s, "This is Message") << std::endl;
	std::cout << f.handle(s, "This is Message") << std::endl;
}

