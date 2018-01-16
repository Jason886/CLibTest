#ifndef _TEST_FILE_H_
#define _TEST_FILE_H_

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct {
            FILE *fp;
            void *readBuf;
            int bufSize;
            int nRead;
    } File_t;

    File_t *File_Load(char *path, char *mod);
    File_t *File_Open(char *path, char *mod, int bufSize);
    int File_Read(File_t *f);
    char *File_BufferToText(File_t *f);
    int File_Write(File_t *f, void *data, int nWrite);
    int File_WriteText(File_t *f, char *text);
    void File_Close(File_t *f);


#ifdef __cplusplus
}
#endif


#endif
