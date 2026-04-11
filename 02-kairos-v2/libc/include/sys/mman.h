#ifndef _sys_mman_h
#define _sys_mman_h 1

#include <sys/types.h>
#include <sys/cdefs.h>

#define MAP_SHARED 0x01
#define MAP_PRIVATE 0x02
#define MAP_ANON 0x20
#define MAP_ANONYMOUS MAP_ANON

#define PROT_NONE 0
#define PROT_READ 1
#define PROT_WRITE 2
#define PROT_EXEC 4

void *mmap(void *addr, size_t len, int prot, int flags, int fildes, off_t off);

#endif