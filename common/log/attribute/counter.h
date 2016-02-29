#ifndef _LOG_COUNTER_H
#define _LOG_COUNTER_H

#include "../../base/color.h"
#include "attribute.h"

namespace Log
{
	class Counter
		: public IAttribute
	{
		public:
			static Counter* create(int start, int step, const char* format = NULL, int color = Color::DEFAULT)
			{
				return new Counter(start, step, format, color);
			}

			virtual ~Counter(){}

			virtual std::string get()
			{
				snprintf(_buff, ATTR_BUFF_SIZE, _format.c_str(), _current);
				_current += _step;
				return std::string(_buff);
			}

		protected:
			Counter(int start, int step, const char* format, int color)
				: _start(start), _step(step), _current(start)
			{
				if(!format)
					format = "%d";
				_format = Color::makeColor(format, color);
			}

		private:
			int _start;
			int _current;
			int _step;

			std::string _format;
			char _buff[ATTR_BUFF_SIZE];
	};
}

#endif
