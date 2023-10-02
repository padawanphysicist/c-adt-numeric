#ifndef __NEW_H__
#define __NEW_H__

#include <stddef.h>

void * new (const void * class, ...);
void delete (void * item);

void * clone (const void * self);
int differ (const void * self, const void * b);

size_t sizeOf (const void * self);

#endif /* __NEW_H__ */
