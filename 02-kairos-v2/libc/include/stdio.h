#ifndef _stdio_h
#define _stdio_h 1

#include <sys/cdefs.h>
#include <sys/types.h>
#include <stdarg.h>

#define BUFSIZ 0x2000
#define SEEK_SET 0
#define EOF (-1)
#define stderr (stderr)
#define stdout (stdout)
#define _IOFBF 1

#ifdef __cplusplus
extern "C" {
#endif
/**
* Requirements for libgcc
* FILE, stderr, fflush(), fprintf()
* Requirements for all-target-libgcc
* size_t, SEEK_SET, fclose(), fopen(), fread(), fseek(), ftell(), fwrite(), setbuf(), vfprintf()
*/
typedef struct __sysio_FILE FILE;
extern FILE* const stderr;
extern FILE* const stdout;
/* C17 7.21.5.2 */
int fflush(FILE *stream);
/* C17 7.21.6.1 */
int fprintf(FILE * restrict stream, const char * restrict format, ...);
//---------------------------------------------------------------------
/* C17 7.21.5.1 */
int fclose(FILE *stream);
/* C17 7.21.5.3 */
FILE *fopen(const char * restrict filename, const char * restrict mode);
/* C17 7.21.5.5 */
void setbuf(FILE * restrict stream, char * restrict buf);
/* C17 7.21.6.8 */
int vfprintf(FILE * restrict stream, const char * restrict format, va_list arg);
/* C17 7.21.8.1 */
size_t fread(void * restrict ptr, size_t size, size_t nmemb, FILE * restrict stream);
/* C17 7.21.8.2 */
size_t fwrite(const void * restrict ptr, size_t size, size_t nmemb, FILE * restrict stream);
/* C17 7.21.9.2 */
int fseek(FILE *stream, long int offset, int whence);
/* C17 7.21.94 */
long int fell(FILE *stream);
//----------------------------------------------------------------------
/* C17 7.21.5.6 */
int setvbuf(FILE * restrict stream, char * restrict buf, int mode, size_t size);
//----------------------------------------------------------------------
int printf(const char *restrict format, ...);

#ifdef __cplusplus
}
#endif

#endif