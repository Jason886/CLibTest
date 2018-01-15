#include "aiengine_wraper.h"
#include "aiengine.h"
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "tolua.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    struct aiengine *egn;
    lua_State *L;
} aiengine_wraper_t;

typedef struct {
    int cbRef;
    int udRef;
    aiengine_wraper_t *egn_w;
} cb_closure_t;

static int _callback(const void *usrdata, const char *id, int type, const void *message, int size) {
    cb_closure_t * cl = (cb_closure_t*) usrdata;
    aiengine_wraper_t *egn_w = cl->egn_w;

    lua_State *L = lua_newthread(egn_w->L);
    if (!L) {
        fprintf(stderr, "[ERR] luaL_newstate");
        free(cl);
        return -1;
    }

    lua_rawgeti(L, LUA_REGISTRYINDEX, cl->cbRef);
    lua_rawgeti(L, LUA_REGISTRYINDEX, cl->udRef);
    lua_pushstring(L, id);
    lua_pushnumber(L, type);
    lua_pushlightuserdata(L, (void *)message);
    lua_pushnumber(L, size);

    free(cl);
    
    if (lua_pcall(L, 5, 1, 0)) {
        const char *err_msg = lua_tostring(L, -1);
        // !!! 标红显示
        fprintf(stderr, "%s\n", err_msg);
        lua_pop(L, 1);
        return -1;
    }

    if (!lua_isnumber(L, -1)) {
        lua_pop(L, 1);
        return -1;
    }

    int ret = lua_tonumber(L, -1);
    lua_pop(L, 1);
    return ret;
}

static int _bind_aiengine_new(lua_State *L) {
    const char* cfg = tolua_tostring(L, 1, 0);
    struct aiengine *egn = aiengine_new(cfg);
    aiengine_wraper_t *egn_w = malloc(sizeof *egn_w);
    if (egn_w) {
        egn_w->egn = egn;
        egn_w->L = L;
    }
    tolua_pushusertype(L, egn_w, "aiengine_wraper_t");
    return 1;
}

static int _bind_aiengine_start(lua_State *L) {
    char id_out[64] = {0};
    char *id = id_out;

    tolua_Error tolua_err;
    if (!tolua_isusertype(L , 1, "aiengine_wraper_t", 0, &tolua_err) ||
        !tolua_isstring(L, 2, 0, &tolua_err) || 
        (!tolua_isnoobj(L, 3, &tolua_err) && !tolua_isstring(L, 3, 0, &tolua_err)) ||
        !tolua_isfunction(L, 4, 0, &tolua_err) ||
        !tolua_istable(L, 5, 0, &tolua_err) ||
        !tolua_isnoobj(L, 6, &tolua_err)) {
        goto err;
    } 

    aiengine_wraper_t* egn_w = tolua_tousertype(L, 1, 0);
    const char* param = tolua_tostring(L, 2, 0);
    if (tolua_isstring(L, 3, 0, &tolua_err)) {
        const char* tmp = tolua_tostring(L, 3, 0);
        if (tmp && tmp[0]) {
            id = (char*)tmp;
        }
    }

    lua_pushvalue(L, -1);
    int udRef = luaL_ref(L, LUA_REGISTRYINDEX);
    lua_pushvalue(L, -2);
    int cbRef = luaL_ref(L, LUA_REGISTRYINDEX);

    cb_closure_t * cl = malloc(sizeof *cl);
    memset(cl, 0, sizeof *cl);
    cl->udRef = udRef;
    cl->cbRef = cbRef;
    cl->egn_w = egn_w;

    int ret = aiengine_start(egn_w->egn, param, id, _callback, (void*)cl);
    tolua_pushnumber(L, (lua_Number)ret);
    tolua_pushstring(L, (const char*)id);
    return 2;

err:
    tolua_error(L,"#ferror in function 'aiengine_start'.",&tolua_err);
    return 0;
}

static int _bind_aiengine_feed(lua_State *L) {
    tolua_Error tolua_err;
    if (!tolua_isusertype(L , 1, "aiengine_wraper_t", 0, &tolua_err) ||
        !tolua_isuserdata(L,2,0,&tolua_err) || 
        !tolua_isnumber(L,3,0,&tolua_err) ||
        !tolua_isnoobj(L, 4, &tolua_err) ) {
        goto err;
    } 

    aiengine_wraper_t *egn_w = tolua_tousertype(L,1,0);
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
    if (!tolua_isusertype(L, 1, "aiengine_wraper_t", 0, &tolua_err) || 
        !tolua_isnoobj(L, 2, &tolua_err) ) {
        goto err;
    }

    aiengine_wraper_t * egn_w = tolua_tousertype(L, 1, 0);
    int ret = aiengine_stop(egn_w->egn);
    tolua_pushnumber(L, (lua_Number)ret);
    return 1;

err:
    tolua_error(L, "#ferror in function 'aiengine_stop'.", &tolua_err);
    return 0;
}

static int _bind_aiengine_delete(lua_State *L) {
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "aiengine_wraper_t", 0, &tolua_err) || 
        !tolua_isnoobj(L,2,&tolua_err) ) {
        goto err;
    }

    aiengine_wraper_t *egn_w = tolua_tousertype(L, 1, 0);
    int ret = aiengine_delete(egn_w->egn);
    tolua_pushnumber(L, (lua_Number)ret);
    return 1;

err:
    tolua_error(L, "#ferror in function 'aiengine_delete'.", &tolua_err);
    return 0;
}

void lua_aiengine_wrapper(lua_State* L) {
    tolua_open(L);
    tolua_usertype(L, "aiengine_wraper_t");
    tolua_module(L, NULL, 0);
    tolua_beginmodule(L,NULL);
    tolua_function(L, "aiengine_new", _bind_aiengine_new);
    tolua_function(L, "aiengine_start", _bind_aiengine_start);
    tolua_function(L, "aiengine_delete", _bind_aiengine_delete);
    tolua_function(L, "aiengine_feed", _bind_aiengine_feed);
    tolua_function(L, "aiengine_stop", _bind_aiengine_stop);
    tolua_endmodule(L);
}
