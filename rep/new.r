#ifndef	__CLASS_R__
#define	__CLASS_R__

#include <stdarg.h>
#include <stdio.h>

struct Class {
	size_t size;
	void * (* ctor) (void * self, va_list * app);
	void * (* dtor) (void * self);
	void * (* clone) (const void * self);
	int (* differ) (const void * self, const void * b);
};

#endif /* __CLASS_R__ */
