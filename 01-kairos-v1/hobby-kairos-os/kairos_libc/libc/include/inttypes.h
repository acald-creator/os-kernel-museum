#ifndef _inittypes_h
#define _inittypes_h 1

#include <sys/cdefs.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef long int imaxdiv_t;

/* C17 7.8.2.1 */
intmax_t imaxabs(intmax_t j);
/* C17 7.8.2.2 */
imaxdiv_t imaxdiv(intmax_t numer, intmax_t demon);

#ifdef __cplusplus
}
#endif

#endif