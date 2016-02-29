#include <iostream>
#include <boost/bind.hpp>

#include "time.h"
#include "counter.h"
#include "constant.h"
#include "thread_id.h"
#include "bind_function.h"
#include "message.h"

class A
{
	public:
		std::string get()
		{
			return std::string("This is Bind Function in class");
		}
		time_t getTime()
		{
			return 0;
		}
};

int main()
{
	A a;
	Log::IAttribute* t = Log::Time::create(boost::bind(&A::getTime, &a), "%Y:%02m:%02d %02H:%02M:%02S [%s]", Color::YELLOW);
	std::cout << t->get() << std::endl;

	t = Log::Counter::create(1, 5, "[%04u]", Color::RED);
//	int a = 1;
//	std::cout << Color::mRED(a) << std::endl;;
	std::cout << t->get() << std::endl;
	std::cout << t->get() << std::endl;

	t = Log::Constant::create("This is Constant", Color::WHITE);
	std::cout << t->get() << std::endl;

	t = Log::ThreadId::create("ThreadId: [%u]", Color::BLUE);
	std::cout << t->get() << std::endl;

	t = Log::BindFunction::create(boost::bind(&A::get, &a));
	std::cout << t->get() << std::endl;

	t = Log::Message::create(boost::bind(&A::get, &a), Color::GREEN);
	std::cout << t->get() << std::endl;

	std::cout << "test.." << std::endl;
}
