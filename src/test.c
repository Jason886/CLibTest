#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "tolua.h"
#define TOLUA_RELEASE
#include "lua_bind.h"
#include "luaJson.h"

#include "aiengine_wraper.h"

int start(int argc, char **argv) {
    int rc = 0;

    (void)argc;
    (void)argv;

    lua_State *L = luaL_newstate();
    if (!L) {
            fprintf(stderr, "[ERR] luaL_newstate");
            rc = -1;
            goto end;
    }
        
    luaL_openlibs(L);
    luaopen_lua_bind(L);
    lua_open_json(L);

    lua_aiengine_wrapper(L);

    if (luaL_loadfile(L, "test.lua") || lua_pcall(L, 0, 0, 0)) {
            const char *error = lua_tostring(L, -1);
        fprintf(stderr, "[ERR] load test.lua: %s\n", error);
        lua_pop(L, 1);
        rc = -1;
            goto end;
    }

end:
    lua_close(L);
    return rc;
}


void SleepMs(int ms) {
    usleep(ms*1000);
}
