#include "aiengine_wraper.h"
#include "tolua.h"
#include "aiengine.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    struct aiengine *egn;
    lua_State *L;
} aiengine_wraper;

static int _bind_aiengine_new(lua_State *L) {
    const char* cfg = tolua_tostring(L, 1, 0);
    struct aiengine *egn = aiengine_new(cfg);
    aiengine_wraper *egn_w = malloc(sizeof *egn_w);
    if (egn_w) {
        egn_w->egn = egn;
        egn_w->L = L;
    }
    tolua_pushusertype(L, egn_w, "aiengine_wraper");
    return 1;
}

/*
static int _bind_aiengine_start(lua_State *L) {
    tolua_Error tolua_err;
    if (!tolua_isusertype(L , 1, "aiengine_wraper", 0, &tolua_err)) {
        goto err;
    } 
    aiengine_wraper* egn_w = tolua_tousertype(L, 1, 0);
    int ret = aiengine_delete(egn_w->egn);
    tolua_pushnumber(L, (lua_Number)ret);
    return 1;
err:
    tolua_error(L,"#ferror in function 'aiengine_start'.",&tolua_err);
    return 0;
}
*/

static int _bind_aiengine_feed(lua_State *L) {
    tolua_Error tolua_err;
    if (!tolua_isusertype(L , 1, "aiengine_wraper", 0, &tolua_err) ||
        !tolua_isuserdata(L,2,0,&tolua_err) || 
        !tolua_isnumber(L,3,0,&tolua_err) ||
        !tolua_isnoobj(L, 4, &tolua_err) ) {
        goto err;
    } 

    aiengine_wraper* egn_w = tolua_tousertype(L,1,0);
    const void* data = tolua_touserdata(L,2,0);
    int size = tolua_tonumber(L,3,0);
    int ret = aiengine_feed(egn_w->egn, data, size);
    tolua_pushnumber(L, (lua_Number)ret);
    return 1;

err:
    tolua_error(L, "#ferror in function 'aiengine_feed'.",&tolua_err);
    return 0;
}

static int _bind_aiengine_stop(lua_State *L) {
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "aiengine_wraper", 0, &tolua_err) || 
        !tolua_isnoobj(L, 2, &tolua_err) ) {
        goto err;
    }

    aiengine_wraper* egn_w = tolua_tousertype(L, 1, 0);
    int ret = aiengine_stop(egn_w->egn);
    tolua_pushnumber(L, (lua_Number)ret);
    return 1;

err:
    tolua_error(L, "#ferror in function 'aiengine_stop'.", &tolua_err);
    return 0;
}

static int _bind_aiengine_delete(lua_State *L) {
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "aiengine_wraper", 0, &tolua_err) || 
        !tolua_isnoobj(L,2,&tolua_err) ) {
        goto err;
    }

    aiengine_wraper* egn_w = tolua_tousertype(L, 1, 0);
    int ret = aiengine_delete(egn_w->egn);
    tolua_pushnumber(L, (lua_Number)ret);
    return 1;

err:
    tolua_error(L, "#ferror in function 'aiengine_delete'.", &tolua_err);
    return 0;
}

void lua_bind_aiengine(lua_State* L) {
    tolua_open(L);
    tolua_usertype(L, "aiengine_wraper");
    tolua_module(L, NULL, 0);
    tolua_beginmodule(L,NULL);
    tolua_function(L, "aiengine_new", _bind_aiengine_new);
    tolua_function(L, "aiengine_delete", _bind_aiengine_delete);
    tolua_function(L, "aiengine_feed", _bind_aiengine_feed);
    tolua_function(L, "aiengine_stop", _bind_aiengine_stop);
    tolua_endmodule(L);
}
