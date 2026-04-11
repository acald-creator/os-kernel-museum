#ifndef _sys_types_h
#define _sys_types_h 1

#define __need_size_t
#include <stddef.h>
/**
* Requirements for libgcc
* 
* Requirements for all-target-libgcc
* pid_t
* Requirements for libgcov
* intptr_t
* Requirements for libstd++
* off_t
*/
#include <__typedef_off_t.h>
#include <__typedef_pid_t.h>

#include <_types/__typedef_intmax_t.h>
#include <_types/__typedef_intptr_t.h>
#include <_types/__typedef_uintptr_t.h>

#endif