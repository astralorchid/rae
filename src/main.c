#include "../include/file.h"
#include "../include/rae.h"
#include "../include/ast.h"
#include "../include/error.h"

//#include "operations.h"

int main(int argc, char* argv[]) {
	raeFile _raeFile = openFile(argv[1]);
	printf("%s", _raeFile.buffer);
	tokens* _tokens = tokenize(_raeFile);
	printf("\n"); printf("Total tokens: %I64u", _tokens->total_tokens); printf("\n");

	printf("%s", "Done");

	return 0;
}