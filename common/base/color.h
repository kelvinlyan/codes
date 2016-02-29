#ifndef _BASE_COLOR_H
#define _BASE_COLOR_H

#include <stdio.h>

#include <string>
#include <sstream>

namespace color
{

#ifndef NCOLORBUF
#define NCOLORBUF 10240
#endif

#define CREATE_COLOR(color) \
	static inline std::string m##color(const char* pstr) \
	{ \
		char buff[NCOLORBUF]; \
		snprintf(buff, NCOLORBUF - 1, "\033[%dm\033[1m%s\033[0m", color, pstr); \
		return std::string(buff); \
	} \
	static inline std::string m##color(int num) \
	{ \
		char buff[NCOLORBUF]; \
		snprintf(buff, NCOLORBUF - 1, "\033[%dm\033[1m%d\033[0m", color, num); \
		return std::string(buff); \
	} \
	static inline std::string m##color(unsigned int num) \
	{ \
		char buff[NCOLORBUF]; \
		snprintf(buff, NCOLORBUF - 1, "\033[%dm\033[1m%u\033[0m", color, num); \
		return std::string(buff); \
	} \
	static inline std::string m##color(double num) \
	{ \
		char buff[NCOLORBUF]; \
		snprintf(buff, NCOLORBUF - 1, "\033[%dm\033[1m%lf\033[0m", color, num); \
		return std::string(buff); \
	} \

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

	static inline std::string makeFormat(const char* format, int color)
	{
		if(color >= BLACK && color <= WHITE)
		{
			std::ostringstream os;
			os << "\033[" << color << "m\033[1m" << format << "\033[0m";
			return os.str();
		}
		else
		{
			return std::string(format);
		}
	}

	template<typename T>
	static inline std::string makeColor(const T& str, int color)
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
			{
				std::ostringstream os;
				os << str;
				return os.str();
			}
		}
	}
}

#endif
