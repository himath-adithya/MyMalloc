#ifndef MYMALLOC_H
#define MYMALLOC_H

#include <stddef.h> // uses size_t and NULL

#ifndef NULL
#define NULL ((void *)0)
#endif // NULL (defines if not defined by stddef.h)

#ifndef _SIZE_T_DEFINED
#ifndef size_t
typedef unsigned long size_t;
#endif // size_t (defines if not defined by stddef.h)
#define _SIZE_T_DEFINED
#endif // _SIZE_T_DEFINED

#define MEM_CAP 25000
#define HEADER_SIZE 2
#define TRUE 1
#define FALSE 0

typedef struct
{
  unsigned int is_free : 1;
  unsigned int size : 15; // max value possible: 24998
} Header;

void *MyMalloc(size_t size);
void MyFree(void *ptr);

#endif // MYMALLOC_H
