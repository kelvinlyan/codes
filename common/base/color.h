#ifndef _BASE_COLOR_H
#define _BASE_COLOR_H

#include <stdio.h>

#include <string>
#include <sstream>

namespace Color
{

#ifndef NCOLORBUF
#define NCOLORBUF 10240
#endif

#define CREATE_COLOR(color) \
	template<typename T> \
	inline std::string m##color(const T& value) \
	{ \
		std::ostringstream os; \
		os << "\033[" << color << "m\033[1m" << value << "\033[0m"; \
		return os.str(); \
	}

	enum{
		DEFAULT = -1,
		BLACK = 30,
		RED,
		GREEN,
		YELLOW,
		BLUE,
		PURPLE,
		DARK_GREEN,
		WHITE,
	};

	CREATE_COLOR(BLACK);
	CREATE_COLOR(RED);
	CREATE_COLOR(GREEN);
	CREATE_COLOR(YELLOW);
	CREATE_COLOR(BLUE);
	CREATE_COLOR(PURPLE);
	CREATE_COLOR(DARK_GREEN);
	CREATE_COLOR(WHITE);

	template<typename T>
	inline std::string makeColor(const T& str, int color)
	{
		switch(color)
		{
			case BLACK:
				return mBLACK(str);
			case RED:
				return mRED(str);
			case GREEN:
				return mGREEN(str);
			case YELLOW:
				return mYELLOW(str);
			case BLUE:
				return mBLUE(str);
			case PURPLE:
				return mPURPLE(str);
			case DARK_GREEN:
				return mDARK_GREEN(str);
			case WHITE:
				return mWHITE(str);
			default:
				break;
		}
		std::ostringstream os;
		os << str;
		return os.str();
	}
}

#endif
