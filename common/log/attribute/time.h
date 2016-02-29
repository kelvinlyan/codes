#ifndef _LOG_TIME_H
#define _LOG_TIME_H

#include <time.h>
#include <vector>
#include <boost/function.hpp>

#include "../../base/macro.h"
#include "../../base/color.h"
#include "attribute.h"
#include "bind_variable.h"
#include "constant.h"

namespace Log
{
	class Time
		: public IAttribute
	{
		public:
			typedef boost::function<time_t()> GetTimeFunc;

			static Time* create(GetTimeFunc func, const char* format = NULL, int color = Color::DEFAULT)
			{
				return new Time(func, format, color);
			}

			virtual ~Time(){}

			virtual std::string get()
			{
				tick();
				std::string buff;
				FOREACH(AttrList, it, _attrs)
					buff += (*it)->get();
				if(_color != Color::DEFAULT)
					buff = Color::makeColor(buff.c_str(), _color);
				return buff;
			}
			
		private:
			Time(GetTimeFunc func, const char* format, int color)
				: _func(func), _color(color)
			{
				init(std::string(format));
			}

			void tick()
			{
				_time_stamp = _func();
				localtime_r(&_time_stamp, &_tm);
				_tm.tm_year = _tm.tm_year + 1900;
				_tm.tm_mon = _tm.tm_mon + 1;
			}

			void init(const std::string& format)
			{
				int begin = 0, end = 0;
				do{
					if((end = format.find("%", begin))
						== std::string::npos)
						break;
					for(int i = end + 1; i < format.size(); ++i)
					{
						bool flag = false;
						switch(format[i])
						{
							case 'Y': flag = addAttr(format, begin, i, &_tm.tm_year, 'd'); break;
							case 'm': flag = addAttr(format, begin, i, &_tm.tm_mon, 'd'); break;
							case 'd': flag = addAttr(format, begin, i, &_tm.tm_mday, 'd'); break;
							case 'H': flag = addAttr(format, begin, i, &_tm.tm_hour, 'd'); break;
							case 'M': flag = addAttr(format, begin, i, &_tm.tm_min, 'd'); break;
							case 'S': flag = addAttr(format, begin, i, &_tm.tm_sec, 'd'); break;
							case 's': flag = addAttr(format, begin, i, &_time_stamp, 'u'); break;
							default:
								break;
						}
						if(flag)
						{
							begin = i + 1;
							break;
						}
					}
				}while(true);
				
				if(begin != format.size())
					_attrs.push_back(Constant::create(format.substr(begin).c_str()));
			}
			
			template<typename T>
			bool addAttr(const std::string& format, int begin, int end, T* var, char type)
			{
				std::string temp = format.substr(begin, end - begin + 1);
				temp[temp.size() - 1] = type;
				_attrs.push_back(BindVariable<T>::create(var, temp.c_str()));
				return true;
			}

		private:
			typedef std::vector<IAttribute*> AttrList;
			AttrList _attrs;

			GetTimeFunc _func;

			time_t _time_stamp;
			struct tm _tm;
			int _color;
	};
}

#endif
