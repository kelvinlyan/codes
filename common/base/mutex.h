#ifndef _MUTEX_H
#define _MUTEX_H

#include <pthread.h>
#include "noncopyable.h"
#include "macro.h"

class Mutex
	: public Noncopyable
{
	public:
		mutex()
		{
			int rc = pthread_mutex_init(&_mutex, NULL);
			POSIX_ASSERT(rc);
		}
		virtual ~mutex()
		{
			int rc = pthread_mutex_destroy(&_mutex);
			POSIX_ASSERT(rc);
		}
		inline void lock()
		{
			int rc = pthread_mutex_lock(&_mutex);
			POSIX_ASSERT(rc);
		}
		inline bool trylock()
		{
			int rc = pthread_mutex_trylock(&_mutex);
			if(rc == EBUSY)
				return false;
			POSIX_ASSERT(rc);
			return true;
		}
		inline void unlock()
		{
			int rc = pthread_mutex_unlock(&_mutex);
			POSIX_ASSERT(rc);
		}

	private:
		pthread_mutex_t _mutex;
};

class ScopedLock
	: public Noncopyable
{
	public:
		ScopedLock(Mutex& m)
			: _mutex(m)
		{
			_mutex.lock();
		}
		virtual ~ScopedLock()
		{
			_mutex.unlock();
		}
	private:
		Mutex& _mutex;
};

#endif
