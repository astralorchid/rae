#include "../include/rae.h"
#include "../include/file.h"
//CHANGE SIZE DEFINES IN rae.h
char* KEYWORDS[] = {
	"null",
	"ubyte",
	"byte",
	"uword",
	"word",
	"for",
	"while",
	"goto",
	"asm",
	"if"
};
//CHANGE SIZE DEFINES IN rae.h
int KEYWORD_ENUMS[] = {
	0,
	TYPE,
	TYPE,
	TYPE,
	TYPE,
	FOR,
	WHILE,
	GOTO,
	ASM,
	IF
};
//CHANGE SIZE DEFINES IN rae.h
char SINGLE_OPERATORS[] = {
'=',
'!',
'[',
']',
'(',
')',
'{',
'}',
',',
'&',
'|',
CHAR_SINGLE_QUOTE,
';',
':'
};
char BINARY_OPERATORS[] = {
	CHAR_PLUS,
	CHAR_MINUS,
	CHAR_DIVIDE,
	CHAR_MULTIPLY,
	CHAR_MOD,
	CHAR_CARROT
};
char SINGLE_CMP_OPERATORS[] = {
	'>',
	'<'
};
//CHANGE SIZE DEFINES IN rae.h
char* DOUBLE_OPERATORS[] = {
	"==",
	"!=",
	"<=",
	">=",
	//"-=",
	//"+=",
	//"*=",
	//"/=",
	//"%=",

	//">>",
	//"<<",
};
char* BOOL_OPERATORS[] = {
		"&&",
	"||",
};
int BOOL_OPERATOR_ENUMS[] = {
	 DOUBLE_AND,
 DOUBLE_OR,
};
//CHANGE SIZE DEFINES IN rae.h
int DOUBLE_OPERATOR_ENUMS[] = {
 DOUBLE_EQUAL,
 NOT_EQUAL,
 LESS_THAN_EQUAL,
 GREATER_THAN_EQUAL,
 //MINUS_EQUAL,
 //PLUS_EQUAL,
 //MULTIPLY_EQUAL,
 //DIVIDE_EQUAL,
 //MOD_EQUAL,

 //SHIFT_RIGHT,
 //SHIFT_LEFT
};

bool isIdentifierChar(char _char) {
	if ((_char > 47 && _char < 58) ||
		(_char > 64 && _char < 91) ||
		(_char > 96 && _char < 123) ||
		_char == CHAR_UNDERSCORE) {
		return true;
	}
	return false;
}

bool isOperator(char _char) {
	bool state = false;
	switch (_char) {
	case CHAR_EQUAL:
	case CHAR_GREATER:
	case CHAR_LESS:
	case CHAR_NOT:
	case CHAR_PLUS:
	case CHAR_MINUS:
	case CHAR_DIVIDE:
	case CHAR_MULTIPLY:
	case CHAR_AND:
	case CHAR_OR:
	case CHAR_CARROT:
	case CHAR_MOD:state=true; break;
		default:break;
	}
	return state;
}

bool isFirstClass(char _char) {
	bool state = false;
	switch (_char) {
	case CHAR_COMMA:
	case CHAR_HASHTAG:
	case CHAR_OPEN_PAREN:
	case CHAR_CLOSE_PAREN:
	case CHAR_OPEN_CURLY:
	case CHAR_CLOSE_CURLY:state = true; break;
	default:break;
	}
	return state;
}

bool isNumeral(char _char) {
	bool state = false;
	if (_char > 47 && _char < 58) {
		state = true;
	}
	return state;
}

bool strcmp(char*s0, char*s1) {
	uint64_t i = 0;
	for (i;s0[i]!='\0';i++) 
	{if(s0[i]!=s1[i]){return false;}}
	if(s0[i]==s1[i]){return true;}
	else {return false;}
}

int64_t getTokenEnum(uint64_t tokenAddr) {
	token* _token;
	_token = tokenAddr;
	int64_t _enum = -1;
	uint64_t arraySize = 0;
	switch (_token->length) {
	case 1:
		arraySize = SINGLE_OPERATOR_AMOUNT;
		for (arraySize; arraySize > 0; arraySize--) {
			if (_token->string[0] == SINGLE_OPERATORS[arraySize - 1]) {
				_enum = SINGLE_OPERATORS[arraySize - 1];
			}
		}
		if (_enum == -1) {
			arraySize = BINARY_OPERATOR_AMOUNT;
			for (arraySize; arraySize > 0; arraySize--) {
				if (_token->string[0] == BINARY_OPERATORS[arraySize - 1]) {
					_enum = BINARY_OPERATOR;
					_token->value = BINARY_OPERATORS[arraySize - 1];
				}
			}
			if (_enum == -1) {
				arraySize = SINGLE_CMP_OPERATOR_AMOUNT;
				for (arraySize; arraySize > 0; arraySize--) {
					if (_token->string[0] == SINGLE_CMP_OPERATORS[arraySize - 1]) {
						_enum = CMP_OPERATOR;
						_token->value = SINGLE_CMP_OPERATORS[arraySize - 1];
					}
				}
			}
		}
		break;
	case 2:
		arraySize = DOUBLE_OPERATOR_AMOUNT;
		for (arraySize; arraySize > 0; arraySize--) {
			if (strcmp(_token->string, DOUBLE_OPERATORS[arraySize - 1])) {
				_enum = CMP_OPERATOR;
				_token->value = DOUBLE_OPERATOR_ENUMS[arraySize - 1];
			}
		}
		if (_enum == -1) {
			arraySize = BOOL_OPERATOR_AMOUNT;
			for (arraySize; arraySize > 0; arraySize--) {
				if (strcmp(_token->string, BOOL_OPERATORS[arraySize - 1])) {
					_enum = BOOL_OPERATOR;
					_token->value = BOOL_OPERATOR_ENUMS[arraySize - 1];
				}
			}
		}
		break;
	default:
		arraySize = KEYWORD_AMOUNT;
		for (arraySize; arraySize > 0; arraySize--) {
			if (strcmp(_token->string, KEYWORDS[arraySize - 1])) {
				_enum = KEYWORD_ENUMS[arraySize - 1];
			}
		}
		break;
	}
	if (_enum == -1) { 
		bool isNumberLiteral = isNumeral(_token->string[0]);
		if (isNumberLiteral) {
			if (_token->string[1] == 'x') {
				//convert hex string to int
			}
			else {
				//convert string to int
				_token->value = atoi(_token->string);
			}
			_enum = LIT;
		}else
		{_enum = IDENTIFIER; }
	};
	return _enum;
}

/*
	Splits the file's text buffer into literal tokens.
later to be turned into enumerated tokens.
Literal tokens can be used to create identifiers
and to check for syntax errors.

	These while loops look ahead in the text,
detecting potential identifiers/keywords and
detecting their byte size to be stored.

*/
tokens* tokenize(raeFile _file) {
	tokens* _tokens = malloc(sizeof(tokens));
	_tokens->tokens = malloc(sizeof(uint64_t));
	uint64_t totalTokens = 0;
	uint64_t totalOperations = 0;
	bool string_literal = false;
	bool asm_block = false;
	uint64_t error = 0;
	uint64_t lineNumber = 1;

	for (uint64_t i = 1; i < _file.fileSize; i++) {
		char current = _file.buffer[i];
		uint64_t tokenEnd = 0;
		uint64_t ahead = 0; //the length of the token, also used to look ahead of current
		uint64_t _i = i; //save original index
		while(isIdentifierChar(current) == true) {
			ahead++; 
			current = _file.buffer[i + ahead];
		}
		if (ahead > 0) {
			totalTokens++;
			i += ahead-1;
			//printf("\n");
			//printf("%u", ahead); printf("%c", ' ');
		}
		else {
			while (isIdentifierChar(current) == false) {
				if (isOperator(current)) {
					ahead++;
					current = _file.buffer[i + ahead];
					if (current == CHAR_SINGLE_QUOTE || current == CHAR_OPEN_PAREN) { break; }
				}
				else if (isFirstClass(current)) {
					if ((current == CHAR_OPEN_CURLY || current == CHAR_CLOSE_CURLY) && !string_literal) { totalOperations++; }
					ahead++;
					current = _file.buffer[i + ahead];
					break;
				}
				else if (current == CHAR_OPEN_SQUARE || current == CHAR_CLOSE_SQUARE) { //condense this into isFirstClass eventually
					ahead++;
					current = _file.buffer[i + ahead];
					break;
				}
				else if(current==CHAR_SEMICOLON || current==CHAR_COLON){
					ahead++;
					current = _file.buffer[i + ahead];

					if (!string_literal) { totalOperations++; }
					break;
				}
				else if (current == CHAR_SINGLE_QUOTE) { //creates literal string token
					if (string_literal){
						string_literal = false;
					}
					else{
						string_literal = true;
						uint64_t nextDelimiter = i + 1;
						bool stringCloses = false;
						//sLitSemicolon:
						for (nextDelimiter; _file.buffer[nextDelimiter] != 0x0D && _file.buffer[nextDelimiter] != CHAR_SEMICOLON; nextDelimiter++) {
							if (_file.buffer[nextDelimiter] == CHAR_SINGLE_QUOTE) {
								stringCloses = true;
							}
						}

						/*if (_file.buffer[nextDelimiter] == CHAR_SEMICOLON) {
							nextDelimiter++;
							goto sLitSemicolon;
						}*/

						if (stringCloses==false) {
							error = 1; //unclosed string literal
						}
					}
					ahead++;
					current = _file.buffer[i + ahead];
					break;
				}
				else if (current == CHAR_SPACE) {
					if (string_literal) {
						ahead++;
						current = _file.buffer[i + ahead];
						break;
					}
					else {
						break;
					}

				}
				else if (current == 0x0A) {
					lineNumber++;
					break;
				}
				else{
					error = 2; //invalid symbol
					break;
				}
			}
			if (ahead > 0) {
				totalTokens++;
				i += ahead-1;
				//printf("\n");
				//printf("%u", ahead); printf("%c", ' ');
			}
		}
		
if (ahead > 0) {
	token* newToken = malloc(sizeof(token));
	newToken->string = malloc(sizeof(char) * (ahead + 1));
	newToken->string[ahead] = '\0';
	newToken->length = ahead;
	newToken->line_number = lineNumber;
	ahead--;

	for (ahead; ahead > 0; ahead--) {
		newToken->string[ahead] = _file.buffer[_i + ahead];
	}

	newToken->string[0] = _file.buffer[_i];
	uint64_t* newTokenArray = realloc(_tokens->tokens, sizeof(uint64_t) * totalTokens);
	_tokens->tokens = newTokenArray;
	_tokens->tokens[totalTokens - 1] = &newToken->string;
}

		if (error != 0) {
			printf("Line %u:", lineNumber); printf("Error code %u", error);
			break;
		}
	}

	if (error != 0) {
		_tokens = 0;
		return _tokens;
	}

	_tokens->total_tokens = totalTokens;
	_tokens->total_operations = totalOperations;
	for (totalTokens; totalTokens > 0; totalTokens--) {
		uint64_t tokenAddr = _tokens->tokens[totalTokens - 1];
		token* _token;
		_token = tokenAddr;
		_token->Enum = getTokenEnum(tokenAddr);
	}

	printf("\n"); printf("Total operations: %u", totalOperations); printf("\n");
	//Split tokens into operations
	//Format string literals

	_tokens->operations = malloc(sizeof(uint64_t)*totalOperations);
	uint64_t tokenIndex = 0; //the index of the token array to start the operation at

	for (uint64_t i = 0; i < totalOperations; i++) {

		int64_t operationSize = 0; //the amount of tokens in an operation
		uint64_t operationStart = tokenIndex;
		uint64_t currentIndex = tokenIndex;

		for (currentIndex; currentIndex < _tokens->total_tokens; currentIndex++) {
			bool endOfOperation = false;

			token* _token;
			_token = _tokens->tokens[currentIndex];

			if (_token->Enum == CHAR_SEMICOLON) {
				endOfOperation = true;
				tokenIndex = currentIndex + 1;
				//operationSize++;
			}
			else if (_token->Enum == CHAR_CLOSE_CURLY || _token->Enum == CHAR_OPEN_CURLY) {
				endOfOperation = true;
				tokenIndex = currentIndex + 1;
				operationSize++;
			}
			else if (_token->Enum == CHAR_SINGLE_QUOTE) {
				uint64_t sLitLength = 0;
				int64_t sLitTokenCount = 0;
				int64_t sLitTokenCount2 = 0;
				uint64_t sLitStart = 0;

				_token->Enum = S_LIT;
				operationSize++;
				currentIndex++;
				sLitStart = currentIndex;
				_token = _tokens->tokens[currentIndex];

				while (_token->Enum != CHAR_SINGLE_QUOTE) {
					_token->Enum = TOKEN_SKIP;
					currentIndex++;
					_token = _tokens->tokens[currentIndex];
				}
				_token->Enum = TOKEN_SKIP;

				sLitTokenCount = currentIndex - sLitStart;
				sLitTokenCount2 = sLitTokenCount;

				for (sLitTokenCount; sLitTokenCount >= 0; sLitTokenCount--) {
					token* sLitToken;
					sLitToken = _tokens->tokens[sLitStart + sLitTokenCount];
					sLitLength += sLitToken->length;
				}

				_token = _tokens->tokens[sLitStart - 1];
				
				char* newSLitString = realloc(_token->string, sizeof(char) * (sLitLength + 1)); //concat token strings into one s_lit token string
				uint64_t newSLitStringIndex = 0;
				for (int64_t j = 0;j < sLitTokenCount2; j++) {
					token* sLitToken;
					sLitToken = _tokens->tokens[sLitStart + j];
					for (uint64_t tokenStringIndex = 0; tokenStringIndex < sLitToken->length; tokenStringIndex++) {
						newSLitString[newSLitStringIndex] = sLitToken->string[tokenStringIndex];
						newSLitStringIndex++;

						if (isFirstClass(sLitToken->string[tokenStringIndex]) == true) {
							_tokens->total_tokens--;
						}
					}
					newSLitString[newSLitStringIndex] = '\0';
				}
				_token->string = newSLitString;
				printf("New string: %s", _token->string);
			}
			else if (_token->Enum == CHAR_COLON) {
				endOfOperation = true;
				tokenIndex = currentIndex + 1;
				if ((int64_t)currentIndex - 1 > 0) {
					_token = _tokens->tokens[currentIndex - 1];
					_token->Enum = LABEL;
				}
			}
			else{
				tokenIndex = currentIndex;
				operationSize++;
			}

			if (endOfOperation) {
				operation* newOperation = malloc(sizeof(operation));
				newOperation->tokens = malloc(sizeof(token) * operationSize);

				uint64_t operationStartOffset = 0;

				for (uint64_t tokenIndex = 0; tokenIndex < operationSize; tokenIndex++) {
					token* _tokenForOperation;
					_tokenForOperation = _tokens->tokens[(operationStart+tokenIndex+operationStartOffset)];
					if (_tokenForOperation->Enum != -2) {
						newOperation->tokens[tokenIndex] = _tokenForOperation;
						printf("%s ", _tokenForOperation->string);
					}
					else {
						operationStartOffset++;
						tokenIndex--;
					}
				}
				printf("\n");
				_tokens->operations[i] = newOperation;
				newOperation->length = operationSize;
				printf("Line %u: ", _token->line_number); printf("Operation size: %u", operationSize); printf("Operation start: %u ", operationStart); printf("\n");
				break;
			}
		}
	}

	return _tokens;
}
