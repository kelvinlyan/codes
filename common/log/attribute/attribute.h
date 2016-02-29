#ifndef _LOG_ATTRIBUTE_H
#define _LOG_ATTRIBUTE_H

#include <string>

namespace Log
{
	enum{
		ATTR_BUFF_SIZE = 10240
	};

	class IAttribute
	{
		public:
			virtual ~IAttribute(){}
			virtual std::string get() = 0;
	};
}

#endif
