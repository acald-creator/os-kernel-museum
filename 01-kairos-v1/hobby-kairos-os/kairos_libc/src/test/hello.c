#include <stdio.h>
#include "terra.h"

int main(int argc, char **argv) {

    // Create a plain Lua state
    // and initialize its libraries
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    // Initialize the terra state in Lua
    terra_init(L);

    char *code = "print('Hello, World')";

    if (terra_loadstring(L, code) == LUA_OK) {
        if (lua_pcall(L, 0, 0, 0) == LUA_OK) {
            lua_pop(L, lua_gettop(L));
        }
    }

//    lua_close(L);
    return 0;
}