#ifndef _TEST_H_
#define _TEST_H_

#include <stdio.h>

int start(int argc, char **argv);
void LOG_I(char *text);
void LOG_W(char *text);
void LOG_E(char *text);
void LOG(char *text);


typedef struct {
	FILE *fp;
	void *readBuf;
	int bufSize;
	int nRead;
} File_t;

File_t *File_Open(char *path, char *mod, int bufSize);
void File_Close(File_t *f);
int File_Read(File_t *f, int nRead);
int File_Write(File_t *f, void *data, int nWrite);
int File_WriteText(File_t *f, char *text);


#endif

