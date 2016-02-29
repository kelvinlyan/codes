#ifndef _LOG_FORMATTER_H
#define _LOG_FORMATTER_H

#include <vector>
#include <map>

#include <boost/function.hpp>
#include <boost/bind.hpp>

#include "../../base/macro.h"
#include "../attribute/attribute.h"
#include "../attribute/message.h"
#include "../attribute/line_number.h"
#include "../attribute/time.h"
#include "../attribute/severity.h"
#include "../attribute/thread_id.h"
#include "node.h"

namespace Log
{
	class Formatter 
		: public Node
	{
		public:
			typedef std::vector<IAttribute*> AttrList;
			typedef boost::function<IAttribute*(const char*, int)> Creator;
			typedef std::map<std::string, Creator> CreatorMap;

			static Formatter* create()
			{
				return new Formatter();
			}

			bool registerAttribute(const std::string& name, Creator creator)
			{
				if(_creator_map.find(name) != _creator_map.end())
					return false;

				_creator_map.insert(make_pair(name, creator));
				return true;
			}

			Formatter& add(const std::string& name, const char* format = NULL, int color = color::DEFAULT)
			{
				CreatorMap::iterator it = _creator_map.find(name);
				if(it != _creator_map.end())
					_attrs.push_back(it->second(format, color));
				return *this;
			}

			Formatter& add(IAttribute* attr)
			{
				_attrs.push_back(attr);
				return *this;
			}

			virtual std::string handle(const State& state, const std::string& str)
			{
				_state = state;
				_str = str;
				_buff.clear();
				FOREACH(AttrList, it, _attrs)
					_buff += (*it)->get();
				return _buff;
			}

		private:
			Formatter()
			{
				init();
			}

			void init()
			{
				registerAttribute("Constant", boost::bind(&Log::Constant::create, _1, _2));
				registerAttribute("LineNumber", boost::bind(&Log::LineNumber::create, _1, _2));
				//registerAttribute("Counter", boost::bind(&Log::Counter::create, _1, _2));
				registerAttribute("ThreadId", boost::bind(&Log::ThreadId::create, _1, _2));
				Time::GetTimeFunc time_func = boost::bind(&Formatter::time, this);
				registerAttribute("Time", boost::bind(&Log::Time::create, time_func, _1, _2));
				Severity::GetSeverityFunc severity_func = boost::bind(&Formatter::severity, this);
				registerAttribute("Severity", boost::bind(&Log::Severity::create, severity_func, _1, _2));
				registerAttribute("Message", boost::bind(&Formatter::createMessage, this, _1, _2));
			}

			time_t time() const { return _state.time(); } 
			const std::string& severity() const { return _state.severity(); }
			const std::string& tag() const { return _state.tag(); }
			const std::string& message() const { return _str; }

			IAttribute* createMessage(const char* format, int color)
			{
				return Log::Message::create(boost::bind(&Formatter::message, this), color);
			}

		private:
			CreatorMap _creator_map;

			AttrList _attrs;
			std::string _buff;
			State _state;
			std::string _str;
	};
}

#endif
