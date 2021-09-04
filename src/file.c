#include "../include/file.h"

uint32_t getFileSize(FILE* fptr) {
	char c;
	uint32_t fileSize = 0;
	c = getc(fptr);
	while (c != EOF) {
		fileSize += 1;
		c = getc(fptr);
	}
	rewind(fptr);
	return fileSize;
}

raeFile openFile(char* filename) {
	uint32_t nameLen = (uint32_t)strlen(filename);
	raeFile* newAsmFile = malloc(sizeof(raeFile));
	newAsmFile->fileName = malloc(nameLen + 1);
	for (uint32_t i = 0; i < nameLen; i++) {
		newAsmFile->fileName[i] = filename[i];
	}
	newAsmFile->fileName[nameLen] = '\0';
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Error opening file\n");
		newAsmFile->fileSize = 0;
		return *newAsmFile;
	}

	uint32_t fs = getFileSize(fp);
	if (fs > 0) { //if file size > 0
		newAsmFile->fileSize = fs+2;
		newAsmFile->buffer = malloc(sizeof(char) * fs + 2);

		if (newAsmFile->buffer != NULL) {
			newAsmFile->buffer[0] = 0x0A;
			newAsmFile->buffer[fs + 1] = 0x0A;
			newAsmFile->buffer[fs + 2] = 0;
			for (uint32_t i = 1; i < fs + 1; i++) {
				newAsmFile->buffer[i] = getc(fp);
			}
		}
	}
	fclose(fp);
	return *newAsmFile;
}