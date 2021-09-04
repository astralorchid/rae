#ifndef RAE_H
#define RAE_H
#include <stdint.h>
#include "file.h"
/*
	Legal identifier chars: 48-57, 65-90, 97-122
*/
typedef unsigned char bool;
#define true 1
#define false 0

//token enums
#define TYPE 1
#define IDENTIFIER 2
#define IF 3 //identifier pointer
#define LIT 4 //integer literal
#define S_LIT 5 //string literal
#define PROC 6 //procedure
#define CONTROL_START 7 // parenthesis
#define CONTROL_END 8
#define BLOCK_START 9 // curly brackets
#define BLOCK_END 10
#define FOR 11
#define WHILE 12
#define GOTO 13
#define LABEL 14

#define DOUBLE_EQUAL 15 //"==",
#define NOT_EQUAL 16 //"!=",
#define LESS_THAN_EQUAL 17 //"<=",
#define GREATER_THAN_EQUAL 18 //">=",
#define MINUS_EQUAL 19 //"-=",
#define PLUS_EQUAL 20 //"+=",
#define MULTIPLY_EQUAL 21 //"*=",
#define DIVIDE_EQUAL 22 //"/=",
#define MOD_EQUAL 23 //"%=",
#define DOUBLE_AND 24 //"&&",
#define DOUBLE_OR 25 //"||",
#define SHIFT_RIGHT 26 //">>",
#define SHIFT_LEFT 27 //"<<",

#define ASM 28
#define BINARY_OPERATOR 29
#define CMP_OPERATOR 30
#define BOOL_OPERATOR 256
//char enums
// 
//second-class:
#define CHAR_GREATER '>'
#define CHAR_LESS '<'
#define CHAR_EQUAL '='
#define CHAR_NOT '!'
#define CHAR_PLUS '+'
#define CHAR_MINUS '-'
#define CHAR_DIVIDE '/'
#define CHAR_MULTIPLY '*'
#define CHAR_MOD '%'
#define CHAR_OPEN_SQUARE '['
#define CHAR_CLOSE_SQUARE ']'
#define CHAR_AND '&'
#define CHAR_OR '|'
#define CHAR_CARROT '^'
//first-class:
#define CHAR_OPEN_PAREN '('
#define CHAR_CLOSE_PAREN ')'
#define CHAR_OPEN_CURLY '{'
#define CHAR_CLOSE_CURLY '}'
#define CHAR_COMMA ','
#define CHAR_HASHTAG '#'
//string literal
#define CHAR_SINGLE_QUOTE '\''
#define CHAR_SPACE ' '
#define CHAR_BACKSLASH 0x92
//end of operation:
#define CHAR_SEMICOLON ';'
//label
#define CHAR_COLON ':'
#define TOKEN_SKIP -2
#define CHAR_UNDERSCORE '_'

#define SINGLE_OPERATOR_AMOUNT 14
#define BINARY_OPERATOR_AMOUNT 6
#define SINGLE_CMP_OPERATOR_AMOUNT 2
#define DOUBLE_CMP_OPERATOR_AMOUNT
#define DOUBLE_OPERATOR_AMOUNT 4
#define BOOL_OPERATOR_AMOUNT 2
#define KEYWORD_AMOUNT 10


//TYPES:
#define TYPE_UBYTE 1
#define TYPE_BYTE 2
#define TYPE_UWORD 3
#define TYPE_WORD 4

typedef struct {
	char* string;
	int64_t Enum;
	uint64_t length;
	uint64_t line_number;
	uint64_t value;
} token;

typedef struct {
	uintptr_t* tokens; //tokens in the operation
	uint64_t opcode, length;
	uintptr_t* next;
	uintptr_t* last;
} operation;

typedef struct {
	char* buffer;
	uintptr_t* tokens;
	uint64_t total_tokens;
	uint64_t total_operations;
	uintptr_t* operations; //null entry if no operation
} tokens;

bool isIdentifierChar(char _char);
bool isOperator(char _char);
bool isFirstClass(char _char);
tokens* tokenize(raeFile _file);
#endif