#ifndef _dlfcn_h
#define _dlfcn_h

#include <sys/types.h>
#include <sys/cdefs.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int dlclose(void *);
char *dlerror(void);
void *dlopen(const char *, int);
void *dlsym(void * restrict, const char * restrict);

#ifdef __cplusplus
}
#endif

#endif //