#ifndef _link_h
#define _link_h

#include <sys/cdefs.h>
#include <sys/types.h>
#include <elf.h>
#include <dlfcn.h>

#ifndef __cplusplus
extern "C" {
#endif

struct dl_phdr_info {
    ElfW(Addr) dlpi_addr;
    const char *dlpi_name;
    const ElfW(Phdr) *dlpi_phdr;
    ElfW(Half) dlpi_phnum;
    unsigned long long int dlpi_adds;
    unsigned long long int dlpi_subs;
    size_t dlpi_tls_modid;
    void *dlpi_tls_data;
};

struct link_map {
    ElfW(Addr) l_addr;
    char *l_name;
    ElfW(Dyn) *l_ld;
    struct link_map *l_next, *l_prev;
};

struct r_debug {
    int r_version;
    struct link_map *r_map;
    ElfW(Addr) r_brk;
    enum { RT_CONSISTENT, RT_ADD, RT_DELETE } r_state;
    ElfW(Addr) r_ldbase;
};

int dl_iterate_phdr(int (*callback) (struct dl_phdr_info *info, size_t size, void *data), void *data);

#ifdef __cplusplus
};
#endif

#endif