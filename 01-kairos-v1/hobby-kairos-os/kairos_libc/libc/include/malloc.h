#ifndef _malloc_h
#define _malloc_h 1

#include <sys/cdefs.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

void free(void *ptr);

void *malloc(size_t size);

void *calloc(size_t nmemb, size_t size);

int posix_memalign(void **memptr, size_t alignment, size_t size);

#ifdef __cplusplus
}
#endif

#endif