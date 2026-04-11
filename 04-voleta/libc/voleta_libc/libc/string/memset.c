#include <string.h>

/* FUNCTION
 * <<memset>>
 *
 * SYNOPSIS
 *      #include <string.h>
 *      void *memset(void *s, int c, size_t n);
 *
 * DESCRIPTION
 * The memset() function shall copy c (converted to an unsigned char) into each of the first n bytes of the object
 * pointed to by s.
 *
 * RETURNS
 *
 * The memset() function shall return s; no return value is reserved to indicate an error.
 *
 */

void *memset(void *bufptr, int value, size_t size) {
    unsigned char *buf = (unsigned char *) bufptr;
    for (size_t i = 0; i < size; i++)
        buf[i] = (unsigned char) value;
    return bufptr;
}