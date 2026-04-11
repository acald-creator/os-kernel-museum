#ifndef _types__struct_timespec_h
#define _types__struct_timespec_h

#include <sys/cdefs.h>
#include <sys/types.h>
#include <stddef.h>

typedef long long int time_t;

struct timespec
{
    time_t tv_sec;
    long tv_nsec;
};

#endif