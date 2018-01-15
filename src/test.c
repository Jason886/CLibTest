#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "tolua.h"
#include "lua_bind.h"
#include "test.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void LOG_I(char *text) {
    fprintf(stdout, "\033[32m%s\033[0m\n", text);
}

void LOG_W(char *text) {
    fprintf(stdout, "\033[33m%s\033[0m\n", text);
}

void LOG_E(char *text) {
    fprintf(stderr, "\033[31m%s\033[0m\n", text);
}

void LOG(char *text) {
    fprintf(stdout, "%s\n", text);
}

File_t *File_Load(char *path, char *mod) {
    int nLen = 0;

    FILE *fp = fopen(path, mod);
    if (!fp) return NULL;

    fseek(fp, 0, SEEK_END);
    nLen = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    void *readBuf = malloc(nLen+1);
    if (!readBuf) {
        fclose(fp);
        return NULL;
    }
    memset(readBuf, 0, nLen+1);
    fread(readBuf, 1, nLen, fp);
    fclose(fp);
    fp = NULL;

    File_t *f = malloc(sizeof *f);
    if (!f) {
        fclose(fp);
        free(readBuf);
        return NULL;
    }
    memset((void*)f, 0, sizeof *f);

    f->readBuf = readBuf;
    f->bufSize = nLen+1;
    f->nRead = nLen;

    return f;
}

File_t *File_Open(char *path, char *mod, int bufSize) {
    if (bufSize <= 0) return NULL;

    FILE *fp = fopen(path, mod);
    if (!fp) return NULL;

    void *readBuf = malloc(bufSize);
    if (!readBuf) {
        fclose(fp);
        return NULL;
    }
    memset(readBuf, 0, bufSize);

    File_t *f = malloc(sizeof *f);
    if (!f) {
        fclose(fp);
        free(readBuf);
        return NULL;
    }
    memset((void*)f, 0, sizeof *f);

    f->fp = fp;
    f->readBuf = readBuf;
    f->bufSize = bufSize;
    f->nRead = 0;

    return f;
}

void File_Close(File_t *f) {
    if (f) {
        if (f->readBuf) free(f->readBuf);
        if (f->fp) fclose(f->fp);
        free(f);
    }
}

int File_Read(File_t *f) {
    if (!f) return -1;
    f->nRead = -1;
    memset(f->readBuf, 0, f->bufSize);
    int rc = fread(f->readBuf, 1, f->bufSize, f->fp);
    f->nRead = rc;
    return rc;
}

int File_Write(File_t *f, void *data, int nWrite) {
    if (!f) return -1;
    return (int)fwrite(data, 1, nWrite, f->fp);
}

int File_WriteText(File_t *f, char *text) {
    return File_Write(f, text, strlen(text));
}



