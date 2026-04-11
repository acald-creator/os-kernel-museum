#ifndef _stdlib_h
#define _stdlib_h 1

#include <sys/cdefs.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

__attribute__((_noreturn__))

/**
* Requirements for libgcc
* abort(), free(), malloc()
* Requirements for all-target-libgcc
* atexit(), atoi(), getenv()
* Requirements of libgcov
* calloc
*/

/* C17 7.22.3.3 */
void free(void *ptr);
/* C17 7.22.3.4 */
void *malloc(size_t size);
/* C17 7.22.4.1
__Noreturn void abort(void):
*/
void abort(void);
//---------------------------------------
/* C17 7.22.1.2 */
int atoi(const char *nptr);
/* C17 7.22.4.2 */
int atexit(void (*func)(void));
/* C17 7.22.4.6 */
char *getenv(const char *name);
//---------------------------------------
// C17 8.22.3.2
void *calloc(size_t nmemb, size_t size);
//---------------------------------------
// Needed for clang libcxx
int posix_memalign(void **memptr, size_t alignment, size_t size);

#ifdef __cplusplus
}
#endif

#endif