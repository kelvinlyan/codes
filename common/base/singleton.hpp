#ifndef _BASE_SINGLETON_HPP
#define _BASE_SINGLETON_HPP

#include "noncopyable.h"
#include "mutex.h"

template <typename T>
class Singleton 
	: public Noncopyable
{
	public:
    	static T& Shared()
    	{
        	if(_pInstance == NULL)
        	{
				_mutex.lock();
				if(_pInstance == NULL)
				{
            		_pInstance = new T();
				}
				_mutex.unlock();
        	}
        	return *_pInstance;
    	}
    
    	void Destroy()
    	{
        	if(_pInstance)
        	{
				_mutex.lock();
				if(_pInstance)
				{
					delete _pInstance;
            		_pInstance = NULL;
				}
				_mutex.unlock();
        	}
    	}

	protected:
		Singleton(){}
		virtual ~Singleton(){}

	private:
    	static T* _pInstance;
		static mutex _mutex;
};

template<typename T>
T* Singleton<T>::_pInstance = NULL;

template<typename T>
mutex Singleton<T>::_mutex;

#define SINGLETON_HELPER(T)\
	friend class Singleton<T>

/*
example:
	class A
		: public Singleton<A>
	{
		public:

		private:
			A();
			SINGLETON_HELPER(A);
	};

*/

#endif 
