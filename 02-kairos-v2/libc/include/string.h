#ifndef _string_h
#define _string_h 1

#include <sys/cdefs.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* Requirements for libgcc
* size_t, memcpy, memset(), strlen()
* Requirements for all-target-libgcc
* strcpy()
*/

/* C17 7.24.2.1 */
void *memcpy(void * restrict s1, const void * restrict s2, size_t n);
/* C17 7.24.6.1 */
void *memset(void *s, int c, size_t n);
/* C17 7.24.6.3 */
size_t strlen(const char *s);
//-------------------------------------------------------------------
/* C17 7.24.2.3 */
char *strcpy(char * restrict s1, const char * restrict s2);

#ifdef __cplusplus
}
#endif

#endif