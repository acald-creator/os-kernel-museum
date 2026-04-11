#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include "fs.h"
#include "terra.h"
#include <errno.h>

static int pusherror(lua_State *L, const char *info)
{
    terra_init(L);

    lua_pushnil(L);
    if (info == NULL)
        lua_pushstring(L, strerror(errno));
    else
        lua_pushfstring(L, "%s: %s", info, strerror(errno));
    lua_pushinteger(L, errno);
    return 3;
}

static int pushresult(lua_State * L, int res, const char *info)
{
    terra_init(L);

    if(res == -1) {
        return pusherror(L, info);
    } else {
        lua_pushboolean(L, 1);
        return 1;
    }
}

static int change_dir(lua_State * L)
{
    const char *path = luaL_checkstring(L, 1);
    if(chdir(path)){
        lua_pushnil(L);
        lua_pushfstring(L, "Unable to change working directory to '%s'\n%s\n", path, chdir_error);
        return 2;
    } else {
        lua_pushboolean(L, 1);
        return 1;
    }
}

