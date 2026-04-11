#include <string.h>

/* FUNCTION
 * <<memcpy>>
 *
 * SYNOPSIS
 *      #include <string.h>
 *      void *memcpy(void *restrict s1, const void *restrict s2, size_t n);
 *
 * DESCRIPTION
 * The memcpy() function shall copy n bytes from the object pointed to by s2 into the object pointed to by s1. If copying
 * takes place between objects that overlap, the behavior is undefined.
 *
 * RETURNS
 *
 * The memcpy() function shall return s1; no return value is reserved to indicate an error.
 *
 */

void *memcpy(void *restrict dstptr, const void *restrict srcptr, size_t size) {
    unsigned char *dst = (unsigned char *) dstptr;
    const unsigned char *src = (const unsigned char *) srcptr;
    for (size_t i = 0; i < size; i++)
        dst[i] = src[i];
    return dstptr;
}