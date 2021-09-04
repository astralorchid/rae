#include "rae.h"

#ifndef ERROR_H
#define ERROR_H

typedef struct {
	uintmax_t code;
	char* message;
} error;

#endif