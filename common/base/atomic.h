#ifndef _ATOMIC_H
#define _ATOMIC_H

class Atomic
{
	public:
		static void Add(uint32_t* pw)
		{
			__asm__
			(
				"lock\n\t"
				"incl %0":
				"=m"(*pw):
				"m"(pw):
				"cc"
			);
		}
		static void Sub(uint32_t* pw)
		{
			__asm__
			(
				"lock\n\t"
				"decl %0":
				"=m"(*pw):
				"m"(pw):
				"cc"
			);
		}
};

#endif
