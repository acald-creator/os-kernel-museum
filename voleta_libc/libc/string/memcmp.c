#include <string.h>

/* FUNCTION
 * <<memcmp>>
 *
 * SYNOPSIS
 *      #include <string.h>
 *      int memcmp(const void *s1, const void *s2, size_t n);
 *
 * DESCRIPTION
 * The memcmp() function shall compare the first n bytes (each interpreted as unsigned char) of the object pointed to by
 * s1 to the first n bytes of the object pointed to by s2.
 *
 * The sign of a non-zero return value shall be determined by the sign of the difference between the values of the first
 * pair of bytes (both interpreted as type unsigned char) that differ in the objects being compared.
 *
 * RETURNS
 *
 * The memcmp() function shall return an integer greater than, equal to, or less than 0, if the object pointed to by s1
 * is greater than, equal to, or less than the object pointed to by s2, respectively.
 *
 */

int memcmp(const void *a1, const void *a2, size_t size) {
    const unsigned char *a = (const unsigned char *) a1;
    const unsigned char *b = (const unsigned char *) a2;

    for (size_t i = 0; i < size; i++) {
        if (a[i] < b[i])
            return -1;
        else if (b[i] < a[i])
            return 1;
    }
    return 0;
}