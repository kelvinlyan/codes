#ifndef _NONCOPYABLE_H
#define _NONCOPYABLE_H

#define DISALLOW_COPY_AND_ASSIGN(TYPE)\
	TYPE(const TYPE&);\
	const TYPE& operator=(const TYPE&)

class Noncopyable
{
	protected:
		Noncopyable(){}
		virtual ~Noncopyable(){}
	private:
		DISALLOW_COPY_AND_ASSIGN(Noncopyable);
};


#endif
