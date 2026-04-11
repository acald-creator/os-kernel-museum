#ifndef _string_h
#define _string_h 1

#include <sys/cdefs.h>
#include <sys/types.h>

// kernel data types
typedef int errno_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * C17 7.24.2.1
 * GNU GCC libgcc requirement
 * */
void *memcpy(void *restrict s1, const void *restrict s2, size_t n);

/**
 * C17 7.24.6.1
 * GNU GCC libgcc requirement
 * */
void *memset(void *s, int c, size_t n);

/**
 * C17 7.24.6.3
 * GNU GCC libgcc requirement
 * */
size_t strlen(const char *s);

//-------------------------------------------------------------------

/**
 * C17 7.24.2.3
 * GNU GCC all-target-libgcc requirement
 * */
char *strcpy(char *restrict s1, const char *restrict s2);

//-------------------------------------------------------------------

/**
 * C17 7.24.4.2
 * */
int strcmp(const char *s1, const char *s2);

int strncmp(const char *s1, const char *s2, size_t n);

char *strncpy(char *restrict s1, const char *restrict s2, size_t n);

char *strstr(const char *s1, const char *s2);

size_t strnlen(const char *str, size_t maxlen);

char *strdup(const char *str);

char *strndup(const char *str, size_t n);

//--------------------------------------------------------------------
char* strerror(int errnum);

errno_t strerror_s(char *buf, rsize_t bufsz, errno_t errnum);

size_t strerrorlen_s(errno_t errnum);

#ifdef __cplusplus
}
#endif

#endif