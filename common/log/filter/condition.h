#ifndef _LOG_CONDITION_H
#define _LOG_CONDITION_H

namespace Log
{
	class ICondition
	{
		public:
			bool match() = 0;
	};
	

}

#endif
