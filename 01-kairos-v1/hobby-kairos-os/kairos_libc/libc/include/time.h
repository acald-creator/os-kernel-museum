#ifndef _time_h
#define _time_h 1

#include <sys/cdefs.h>
#include <sys/types.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CLOCK_REALTIME           0
#define CLOCK_MONOTONIC          1
#define CLOCK_PROCESS_CPUTIME_ID 2
#define CLOCK_THREAD_CPUTIME_ID  3
#define CLOCK_MONOTONIC_RAW      4
#define CLOCK_REALTIME_COARSE    5
#define CLOCK_MONOTONIC_COARSE   6
#define CLOCK_BOOTTIME           7
#define CLOCK_REALTIME_ALARM     8
#define CLOCK_BOOTTIME_ALARM     9
#define CLOCK_SGI_CYCLE         10
#define CLOCK_TAI               11
#define CLOCKS_PER_SEC 1000

typedef long int clock_t;

struct tm {
    int tm_sec;   /* Seconds. [0-60]      */
    int tm_min;   /* Minutes. [0-59]      */
    int tm_hour;  /* Hours.   [0-23]      */
    int tm_mday;  /* Day.     [1-31]      */
    int tm_mon;   /* Month.   [0-11]      */
    int tm_year;  /* Year - 1900.         */
    int tm_wday;  /* Day of week. [0-6]   */
    int tm_yday;  /* Days in year.[0-365] */
    int tm_isdst; /* DST.     [-1/0/1]    */
};

time_t time(time_t *timer);

clock_t clock(void);

struct tm *gmtime(const time_t *timer);

struct tm *localtime(const time_t *timer);

size_t strftime(char *s, size_t n, const char *format, const struct tm *tptr);

time_t mktime(struct tm *ptm);

double difftime(time_t timer2, time_t timer1);

char *asctime(const struct tm *pTime);

char *ctime(const time_t *pTime);

#ifdef __cplusplus
}
#endif

#endif