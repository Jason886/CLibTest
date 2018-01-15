#include "luaJson.h"
#include "cJSON.h"

#include <stdio.h>

static void _set_table_jsfield(lua_State *L, cJSON *json, int set_table) {
    if (!json) {
        lua_pushnil(L);
    }
    else if (json->type == cJSON_NULL) {
        lua_pushnil(L);
    } else if (json->type == cJSON_False) {
        lua_pushboolean(L, 0);
    } else if (json->type == cJSON_True) {
        lua_pushboolean(L, 1);
    } else if (json->type == cJSON_Number) {
        lua_pushnumber(L, json->valuedouble);
    } else if (json->type == cJSON_String) {
        lua_pushstring(L, json->valuestring);
    } else if (json->type == cJSON_Array) {
        lua_newtable(L);
        int size = cJSON_GetArraySize(json);
        int i = 0;
        for (i = 0; i < size; i++) { 
            lua_pushinteger(L, i+1);
            _set_table_jsfield(L, cJSON_GetArrayItem(json, i), 1);
        }
    } else if (json->type == cJSON_Object) {
        lua_newtable(L);
        cJSON *child = json->child;
        while(child) {
            lua_pushstring(L, child->string);
            _set_table_jsfield(L, child, 1);
            child = child->next;
        }
    } else {
        lua_pushnil(L);
    }

    if (set_table) {
        lua_settable(L, -3);
    }
}

static void push_cjson(lua_State *L, void *json) {
    _set_table_jsfield(L, json, 0);
}


static int _json_parse(lua_State *L) {
	if (!lua_isstring(L, -1) && !lua_islightuserdata(L, -1)) {
		fprintf(stderr, "Json_Parse failed: arg 1 not string\n");
		return 0;
	}
	cJSON *j_root = NULL;
	if (lua_isstring(L, -1)) {
		const char * str = lua_tostring(L, -1);
		j_root = cJSON_Parse(str);
	} else {
		void *data = lua_touserdata(L, -1);
		j_root = cJSON_Parse(data);
	}
	if (!j_root) {
		fprintf(stderr, "Json_Parse failed: json format error\n");
		return 0;
	}

	push_cjson(L, j_root);
	return 1;
}

void lua_open_json(lua_State* L) {
	lua_register(L, "Json_Parse", _json_parse);
}