#ifndef _LOG_LINE_NUMBER_H
#define _LOG_LINE_NUMBER_H

#include "counter.h"

namespace Log
{
	class LineNumber
		: public Counter
	{
		public:
			static LineNumber* create(const char* format = NULL, int color = Color::DEFAULT)
			{
				return new LineNumber(format, color);
			}

			virtual ~LineNumber(){}

		private:
			LineNumber(const char* format, int color)
				: Counter(1, 1, format, color){}
	};
}

#endif
