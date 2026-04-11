#ifndef _stdbool_h
#define _stdbool_h 1

#include <sys/cdefs.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define true 1
#define false 0
typedef _Bool bool;

#ifdef __cplusplus
}
#endif

#endif