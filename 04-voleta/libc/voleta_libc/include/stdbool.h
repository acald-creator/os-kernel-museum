#ifndef VOLETA_LIBC_STDBOOL_H
#define VOLETA_LIBC_STDBOOL_H 1

#ifdef  __cplusplus
extern "C" {
#endif

#ifndef __cplusplus

#define bool _Bool

#define true 1
#define false 0

#define __bool_true_false_are_defined 1

#ifdef  __cplusplus
}
#endif

#endif

#endif //VOLETA_LIBC_STDBOOL_H
