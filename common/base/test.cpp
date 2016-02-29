#include "color.h"
#include <iostream>

int main()
{
	std::cout << Color::mRED("This is a test!") << std::endl;
	std::cout << Color::makeColor("This is a test!", Color::RED) << std::endl;
}
