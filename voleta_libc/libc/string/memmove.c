#include <string.h>

/* FUNCTION
 * <<memmove>>
 *
 * SYNOPSIS
 *      #include <string.h>
 *      void *memmove(void *s1, const void *s2, size_t n);
 *
 * DESCRIPTION
 * The memmove() function shall copy n bytes from the object pointed to by s2 into the object pointed to by s1. Copying
 * takes place as if the n bytes from the object pointed to by s2 are first copied into a temporary array of n bytes
 * that does not overlap the objects pointed to by s1 and s2, and then the n bytes from the temporary array are copied
 * into the object pointed to by s1.
 *
 * RETURNS
 *
 * The memmove() function shall return s1; no return value is reserved to indicate an error.
 *
 */

void *memmove(void *dstptr, const void *srcptr, size_t size) {
    unsigned char *dst = (unsigned char *) dstptr;

    const unsigned char *src = (const unsigned char *) srcptr;
    if (dst < src) {
        for (size_t i = 0; i < size; i++)
            dst[i] = src[i];
    } else {
        for (size_t i = size; i != 0; i--)
            dst[i - 1] = src[i - 1];
    }
    return dstptr;
}
