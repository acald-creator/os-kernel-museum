#ifndef _pthread_h
#define _pthread_h 1

#include <sys/cdefs.h>
#include <sys/types.h>

#define __NEED_time_t
#define __NEED_clockid_t
#define __NEED_struct_timespec
#define __NEED_sigset_t
#define __NEED_pthread_t
#define __NEED_pthread_attr_t
#define __NEED_pthread_mutexattr_t
#define __NEED_pthread_condattr_t
#define __NEED_pthread_rwlockattr_t
#define __NEED_pthread_barrierattr_t
#define __NEED_pthread_mutex_t
#define __NEED_pthread_cond_t
#define __NEED_pthread_rwlock_t
#define __NEED_pthread_barrier_t
#define __NEED_pthread_spinlock_t
#define __NEED_pthread_key_t
#define __NEED_pthread_once_t
#define __NEED_size_t

#define PTHREAD_CREATE_JOINABLE 0
#define PTHREAD_CREATE_DETACHED 1
#define PTHREAD_MUTEX_NORMAL 0
#define PTHREAD_MUTEX_DEFAULT 0
#define PTHREAD_MUTEX_RECURSIVE 1
#define PTHREAD_MUTEX_ERRORCHECK 2
#define PTHREAD_MUTEX_STALLED 0
#define PTHREAD_MUTEX_ROBUST 1
#define PTHREAD_PRIO_NONE 0
#define PTHREAD_PRIO_INHERIT 1
#define PTHREAD_PRIO_PROTECT 2
#define PTHREAD_INHERIT_SCHED 0
#define PTHREAD_EXPLICIT_SCHED 1
#define PTHREAD_SCOPE_SYSTEM 0
#define PTHREAD_SCOPE_PROCESS 1
#define PTHREAD_PROCESS_PRIVATE 0
#define PTHREAD_PROCESS_SHARED 1
#define PTHREAD_MUTEX_INITIALIZER {{{0}}}
#define PTHREAD_RWLOCK_INITIALIZER {{{0}}}
#define PTHREAD_COND_INITIALIZER {{{0}}}
#define PTHREAD_ONCE_INIT 0
#define PTHREAD_CANCEL_ENABLE 0
#define PTHREAD_CANCEL_DISABLE 1
#define PTHREAD_CANCEL_MASKED 2
#define PTHREAD_CANCEL_DEFERRED 0
#define PTHREAD_CANCEL_ASYNCHRONOUS 1
#define PTHREAD_CANCELED ((void *)-1)
#define PTHREAD_BARRIER_SERIAL_THREAD (-1)
#define PTHREAD_NULL ((pthread_t)0)

#ifdef __cplusplus
extern "C" {
#endif

int pthread_create(pthread_t *__restrict, const pthread_attr_t *__restrict, void *(*)(void *), void *__restrict);
int pthread_detach(pthread_t);
_Noreturn void pthread_exit(void *);
int pthread_join(pthread_t, void **);

int pthread_create(pthread_t *restrict, const pthread_attr_t *restrict, void *(*)(void *), void *restrict);
int pthread_rwlock_init(pthread_rwlock_t *restrict, const pthread_rwlockattr_t *restrict);
int pthread_rwlock_destroy(pthread_rwlock_t *);
int pthread_rwlock_rdlock(pthread_rwlock_t *);
int pthread_rwlock_tryrdlock(pthread_rwlock_t *);
int pthread_rwlock_timedrdlock(pthread_rwlock_t *restrict, const struct timespec *restrict);
int pthread_rwlock_wrlock(pthread_rwlock_t *);
int pthread_rwlock_trywrlock(pthread_rwlock_t *);
int pthread_rwlock_timedwrlock(pthread_rwlock_t *restrict, const struct timespec *restrict);
int pthread_rwlock_unlock(pthread_rwlock_t *);

hidden int __pthread_once(pthread_once_t *, void (*)(void));
hidden void __pthread_testcancel(void);
hidden int __pthread_setcancelstate(int, int *);
hidden int __pthread_create(pthread_t *restrict, const pthread_attr_t *restrict, void *(*)(void *), void *restrict);
hidden _Noreturn void __pthread_exit(void *);
hidden int __pthread_join(pthread_t, void **);
hidden int __pthread_mutex_lock(pthread_mutex_t *);
hidden int __pthread_mutex_trylock(pthread_mutex_t *);
hidden int __pthread_mutex_trylock_owner(pthread_mutex_t *);
hidden int __pthread_mutex_timedlock(pthread_mutex_t *restrict, const struct timespec *restrict);
hidden int __pthread_mutex_unlock(pthread_mutex_t *);
hidden int __private_cond_signal(pthread_cond_t *, int);
hidden int __pthread_cond_timedwait(pthread_cond_t *restrict, pthread_mutex_t *restrict, const struct timespec *restrict);
hidden int __pthread_key_create(pthread_key_t *, void (*)(void *));
hidden int __pthread_key_delete(pthread_key_t);
hidden int __pthread_rwlock_rdlock(pthread_rwlock_t *);
hidden int __pthread_rwlock_tryrdlock(pthread_rwlock_t *);
hidden int __pthread_rwlock_timedrdlock(pthread_rwlock_t *__restrict, const struct timespec *__restrict);
hidden int __pthread_rwlock_wrlock(pthread_rwlock_t *);
hidden int __pthread_rwlock_trywrlock(pthread_rwlock_t *);
hidden int __pthread_rwlock_timedwrlock(pthread_rwlock_t *__restrict, const struct timespec *__restrict);
hidden int __pthread_rwlock_unlock(pthread_rwlock_t *);

#ifdef __cplusplus
}
#endif

#endif