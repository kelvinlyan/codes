#ifndef _LOG_CONSTANT_H
#define _LOG_CONSTANT_H

#include "../../base/color.h"
#include "attribute.h"

namespace Log
{
	class Constant
		: public IAttribute
	{
		public:
			static Constant* create(const char* pstr, int color = Color::DEFAULT)
			{
				return new Constant(pstr, color);
			}

			virtual ~Constant(){}

			virtual std::string get()
			{
				return _value;
			}

		private:
			Constant(const char* pstr, int color)
			{
				_value = Color::makeColor(pstr, color);
			}

		private:
			std::string _value;
	};
}

#endif
