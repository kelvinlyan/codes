#ifndef _LOG_BIND_FUNCTION_H
#define _LOG_BIND_FUNCTION_H

#include <boost/function.hpp>

#include "../../base/color.h"
#include "attribute.h"

namespace Log
{
	class BindFunction
		: public IAttribute
	{
		public:
			typedef boost::function<std::string(void)> FunctionType;

			static BindFunction* create(FunctionType func, const char* format = NULL, int color = Color::DEFAULT)
			{
				return new BindFunction(func, format, color);
			}

			virtual ~BindFunction(){}

			virtual std::string get()
			{
				snprintf(_buff, ATTR_BUFF_SIZE, _format.c_str(), _func().c_str());
				return std::string(_buff);
			}

		private:
			BindFunction(FunctionType func, const char* format, int color)
				: _func(func)
			{
				if(!format)
					format = "%s";
				_format = Color::makeColor(format, color);
			}

		private:
			FunctionType _func;
			std::string _format;
			char _buff[ATTR_BUFF_SIZE];
	};
}

#endif
