#ifndef _LOG_MESSAGE_H
#define _LOG_MESSAGE_H

#include <string>

#include "../../base/color.h"
#include "attribute.h"

namespace Log
{
	class Message
		: public IAttribute
	{
		public:
			typedef boost::function<const std::string&()> GetMsgFunc;
			static Message* create(GetMsgFunc func, int color = Color::DEFAULT)
			{
				return new Message(func, color);
			}

			virtual ~Message(){}

			virtual std::string get()
			{
				if(_color == Color::DEFAULT)
					return _func();
				else
				{
					snprintf(_buff, ATTR_BUFF_SIZE, _format.c_str(), _func().c_str());
					return std::string(_buff);
				}
			}

		private:
			Message(GetMsgFunc func, int color)
				: _func(func), _color(color)
			{
				_format = Color::makeColor("%s", color);
			}

		private:
			GetMsgFunc _func;

			char _buff[ATTR_BUFF_SIZE];
			std::string _format;
			int _color;
	};
}

#endif
