#include "File.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

char *File_BufferToText(File_t *f) {
   if (f) {
       return f->readBuf;
   }
   return "";
}



