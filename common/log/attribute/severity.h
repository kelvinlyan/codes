#ifndef _LOG_SEVERITY_H
#define _LOG_SEVERITY_H

#include <string>

#include "../../base/color.h"
#include "attribute.h"

namespace Log
{
	class Severity
		: public IAttribute
	{
		public:
			typedef boost::function<const std::string&()> GetSeverityFunc;

			static Severity* create(GetSeverityFunc func, const char* format = NULL, int color = Color::DEFAULT)
			{
				return new Severity(func, format, color);
			}

			virtual ~Severity(){}

			virtual std::string get()
			{
				snprintf(_buff, ATTR_BUFF_SIZE, _format.c_str(), _func().c_str());
				return std::string(_buff);
			}

		private:
			Severity(GetSeverityFunc func, const char* format, int color)
				: _func(func)
			{
				if(!format)
					format = "%s";
				_format = Color::makeColor(format, color);
			}

		private:
			GetSeverityFunc _func;

			std::string _format;
			char _buff[ATTR_BUFF_SIZE];
	};
}

#endif
