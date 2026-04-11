#ifndef VOLETA_LIBC_STRING_H
#define VOLETA_LIBC_STRING_H 1

#include <sys/cdefs.h>
#include <sys/types.h>

#include <stddef.h>

#ifdef  __cplusplus
extern "C" {
#endif

int memcmp(const void *, const void *, size_t);

void *memcpy(void *restrict, const void *restrict, size_t);

void *memmove(void *, const void *, size_t);

void *memset(void *, int, size_t);

size_t strlen(const char *);


#ifdef  __cplusplus
}
#endif

#endif //VOLETA_LIBC_STRING_H
