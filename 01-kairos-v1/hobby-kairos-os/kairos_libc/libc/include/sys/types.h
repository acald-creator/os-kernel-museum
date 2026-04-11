#ifndef _sys_types_h
#define _sys_types_h 1

#include <stddef.h>

#define __need_size_t

#include <_types/__typedef_size_t.h>

#include <_types/__typedef_int8_t.h>
#include <_types/__typedef_int16_t.h>
#include <_types/__typedef_int32_t.h>
#include <_types/__typedef_int64_t.h>

#include <_types/__typedef_uint8_t.h>
#include <_types/__typedef_uint16_t.h>
#include <_types/__typedef_uint32_t.h>
#include <_types/__typedef_uint64_t.h>

#include <_types/__typedef_intptr_t.h>
#include <_types/__typedef_uintptr_t.h>

#include <_types/__typedef_intmax_t.h>
#include <_types/__typedef_uintmax_t.h>

#include <_types/__typedef_blkcnt_t.h>
#include <_types/__typedef_blksize_t.h>
#include <_types/__typedef_dev_t.h>
#include <_types/__typedef_gid_t.h>
#include <_types/__typedef_ino_t.h>
#include <_types/__typedef_mode_t.h>
#include <_types/__typedef_nlink_t.h>
#include <_types/__typedef_off_t.h>
#include <_types/__typedef_uid_t.h>
#include <_types/__typedef_pid_t.h>
#include <__struct_timespec.h>

typedef struct { union { int __i[sizeof(long)==8?14:8]; volatile int __vi[sizeof(long)==8?14:8]; void *__p[sizeof(long)==8?7:8]; } __u; } pthread_rwlock_t;
#endif