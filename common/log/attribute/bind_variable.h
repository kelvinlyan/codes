#ifndef _LOG_BIND_VARIABLE_H
#define _LOG_BIND_VARIABLE_H

#include "../../base/color.h"
#include "attribute.h"

namespace Log
{
	template<typename T>
	class BindVariable
		: public IAttribute
	{
		public:
			static BindVariable* create(const T* const var_addr, const char* format, int color = Color::DEFAULT)
			{
				return new BindVariable<T>(var_addr, format, color);
			}

			virtual ~BindVariable(){}

			virtual std::string get()
			{
				snprintf(_buff, ATTR_BUFF_SIZE, _format.c_str(), *_var);
				return std::string(_buff);
			}

		private:
			BindVariable(const T* const var_addr, const char* format, int color)
				: _var(var_addr)
			{
				_format = Color::makeColor(format, color);
			}


		private:
			const T* const _var;
			std::string _format;
			char _buff[ATTR_BUFF_SIZE];
	};
}

#endif
