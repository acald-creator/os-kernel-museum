#ifndef _ctype_h
#define _ctype_h 1

#include <sys/cdefs.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

int isalnum(int);

int isalpha(int);

int isblank(int);

int iscntrl(int);

int isdigit(int);

int isgraph(int);

int islower(int);

int isprint(int);

int ispunct(int);

int isspace(int);

int isupper(int);

int isxdigit(int);

int tolower(int);

int toupper(int);

#ifdef __cplusplus
}
#endif

#endif