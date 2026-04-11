#include <string.h>

/* FUNCTION
 * <<strlen>>
 *
 * SYNOPSIS
 *      #include <string.h>
 *      size_t strlen(const char *s);
 *
 * DESCRIPTION
 * The strlen() function shall compute the number of bytes in the string to which s points, not including the
 * terminating NUL character.
 *
 * RETURNS
 *
 * The strlen() function shall return the length of s; no return value shall be reserved to indicate an error.
 *
 */

size_t strlen(const char *str) {
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}
