#ifndef _AIENGINE_WRAPER_H_
#define _AIENGINE_WRAPER_H_

#ifdef __cplusplus
extern "C" {
#endif

    #include "lua.h"

    void lua_bind_aiengine(lua_State* L);

#ifdef __cplusplus
}
#endif

#endif
