#include <unistd.h>
#include "terra.h"

#ifdef NO_CHDIR
#define chdir(p) (-1)
#define chdir_error "Function 'chdir' not provided by system"
#else
#define chdir_error strerror(errno)
#endif

#define LOCAL_FILESYSTEM_EXPORT

#ifdef __cplusplus
extern "C" {
#endif

LOCAL_FILESYSTEM_EXPORT int luaopen_lfs(lua_State *L);

#ifdef  __cplusplus
}
#endif