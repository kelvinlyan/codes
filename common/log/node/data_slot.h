#ifndef _LOG_DATASLOT_H
#define _LOG_DATASLOT_H

#include <sstream>

#include "node.h"

namespace Log
{
	class DataSlot
		: public Node
	{
		public:
			inline void start(const int severity, const std::string& tag, const time_t time)
			{
				_stream.str("");
				_state.reset(severity, tag, time);
			}

			inline void end()
			{
				run(_state, _stream.str());
			}

			virtual std::string handle(const State& state, const std::string& str)
			{
				return str;
			}

			template<typename T>
			DataSlot& operator<<(const T& data)
			{
				_stream << data;
				return *this;
			}

		private:
			State _state;
			std::ostringstream _stream;
	};
}

#endif
