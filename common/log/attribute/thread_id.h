#ifndef _LOG_THREAD_ID_H
#define _LOG_THREAD_ID_H

#include <sys/syscall.h>
#include <sys/types.h>
#include <string>

#include "../../base/color.h"
#include "attribute.h"

namespace Log
{
	class ThreadId
		: public IAttribute
	{
		public:
			static ThreadId* create(const char* format = NULL, int color = Color::DEFAULT)
			{
				return new ThreadId(format, color);
			}

			virtual ~ThreadId(){}

			virtual std::string get()
			{
				snprintf(_buff, ATTR_BUFF_SIZE, _format.c_str(), syscall(SYS_gettid));
				return std::string(_buff);
			}

		private:
			ThreadId(const char* format, int color)
			{
				if(!format)
					format = "%u";
				_format = Color::makeColor(format, color);
			}

		private:
			std::string _format;
			char _buff[ATTR_BUFF_SIZE];
	};
}

#endif
