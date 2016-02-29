#ifndef _LOG_PRINTER_H
#define _LOG_PRINTER_H

#include <stdio.h>

#include "node.h"

namespace Log
{
	class Printer 
		: public Node
	{
		public:
			static Printer* create()
			{
				return new Printer();
			}

			virtual std::string handle(const std::string& str)
			{
				printf("%s", str.c_str());
				return str;
			}

		private:
			Printer(){}
	};
}

#endif
