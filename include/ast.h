#include "rae.h"

#ifndef AST_H
#define AST_H

#define IDENTIFIER_NODE IDENTIFIER
#define DECLARE_NODE TYPE
#define BLOCK_NODE CHAR_OPEN_CURLY
#define END_OF_BLOCK CHAR_CLOSE_CURLY
#define END_OF_LINE CHAR_SEMICOLON
#define END_OF_POINTER CHAR_CLOSE_SQUARE
#define POINTER_NODE CHAR_OPEN_SQUARE
#define ASSIGN_NODE CHAR_EQUAL
#define LITERAL_NODE LIT
#define STR_LIT_NODE S_LIT
#define GROUP_NODE CHAR_OPEN_PAREN
#define END_OF_GROUP CHAR_CLOSE_PAREN
#define FUNCTION_NODE 6
typedef struct _node {
	uintmax_t type;
	uintptr_t* data;
	uintptr_t* children;
	uintptr_t parent;
	uintptr_t token;
	uintmax_t totalChildren;
} node;

typedef struct {
	uintptr_t gotoNode;
	uintptr_t returnNode;
} GroupNode;

typedef struct {
	uintptr_t* stack;
	uintmax_t size;
} NodeStack;

void pushNode(NodeStack* _stack, node* _node);
node* popNode(NodeStack* _stack);
node* peekNode(NodeStack* _stack, uintmax_t i);
void clearNodeStack(NodeStack* _stack);
node* createAST(tokens* _tokens);
node* exprAST(tokens* _tokens, uintmax_t i, NodeStack* operatorStack, NodeStack* outputStack, uintmax_t end);
#endif