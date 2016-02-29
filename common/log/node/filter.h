#ifndef _LOG_FILTER_H
#define _LOG_FILTER_H

namespace Log
{
	class Filter
	{
		public:
			// (SEVERITY >= INFO && SEVERITY <= ERROR) && (TIME >= '2016-01-10 5:00:00')
			bool match();

		private:
			
	};
}

#endif
