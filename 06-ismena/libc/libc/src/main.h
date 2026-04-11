#ifndef __ISMENAOS_LIBC_MAIN__
#define __ISMENAOS_LIBC_MAIN__

#include <libc/sys/cdefs.h>

__BEGIN_C_CODE;

int __ismenaos_main();

int main(int argc, char **argv);

void __ismenaos_init_libc();
void __ismenaos_fini_libc();

__END_C_CODE;

#endif