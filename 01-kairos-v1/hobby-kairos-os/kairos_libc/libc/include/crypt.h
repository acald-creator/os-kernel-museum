#ifndef _crypt_h
#define _crypt_h

#include <sys/cdefs.h>
/**
 * Compiling compiler-rt requested crypt.h through sanitizer_platform_limits_posix.cpp
 */

#ifdef __cplusplus
extern "C" {
#endif

struct crypt_data {
    int initialized;
    char __buf[256];
};

char *crypt(const char *, const char *);

char *crypt_r(const char *, const char *, struct crypt_data);


#ifdef __cplusplus
};
#endif

#endif