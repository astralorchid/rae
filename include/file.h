#ifndef FILE_H
#define FILE_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char* buffer;
	char* fileName;
	uint32_t fileSize;
}raeFile;

uint32_t getFileSize(FILE* fptr);
raeFile openFile(char* filename);

#endif
