#ifndef __struct_timespec_h
#define __struct_timespec_h

#include <sys/types.h>
#include <sys/cdefs.h>
#include <stddef.h>
#include <__typedef_time_t.h>

struct timespec
{
    time_t tv_sec;
    long tv_nsec;
};

#endif // __struct_timespec_h