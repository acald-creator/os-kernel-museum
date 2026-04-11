#ifndef _dlfcn_h
#define _dlfcn_h 1

#include <sys/cdefs.h>
#include <sys/types.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RTLD_LAZY   1
#define RTLD_NOW    2
#define RTLD_NOLOAD 4
#define RTLD_NODELETE 4096
#define RTLD_GLOBAL 256
#define RTLD_LOCAL  0

#define RTLD_NEXT    ((void *)-1)
#define RTLD_DEFAULT ((void *)0)

#define RTLD_DI_LINKMAP 2

int dlclose(void *);

char *dlerror(void);

void *dlopen(const char *, int);

void *dlsym(void *restrict, const char *restrict);

typedef struct {
    const char *dli_fname;
    void *dli_fbase;
    const char *dli_sname;
    void *dli_saddr;
} Dl_info;

int dladdr(const void *, Dl_info *);
int dlinfo(void *, int, void *);

#ifdef __cplusplus
}
#endif

#endif