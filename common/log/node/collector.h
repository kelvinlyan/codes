#ifndef _LOG_COLLECTOR_H
#define _LOG_COLLECTOR_H

#include "data_slot.h"

namespace Log
{
	class Collector
	{
		public:
			Collector(const int severity, const std::string& tag, const time_t time, DataSlot* slot)
				: _slot(slot)
			{
				_slot->start(severity, time, tag);
			}

			~Collector()
			{
				_slot->end();
			}
			
			template<typename T>
			Collector& operator<<(const T& data)
			{
				_slot->operator<<(data);
				return *this;
			}
			
		private:
			DataSlot* _slot;
	};
}

#endif
