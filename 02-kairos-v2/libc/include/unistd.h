#ifndef _unistd_h
#define _unistd_h 1

#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* Requirements for libgcc
* 
* Requirements for all-target-libgcc
* pid_t, fork(), execv(), execve(), execvp()
*/
unsigned sleep(unsigned seconds);

#ifdef __cplusplus
}
#endif

#endif