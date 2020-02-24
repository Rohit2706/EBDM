// This file lists the function prototypes for the lexical analyser (lexer.c)

#include "lexerDef.h"

// Functions declarations for lexer
void getStream(char* buffer);
TokenInfo getNextToken();
void removeComments(char *testcaseFile);

// Utility Function declarations
void lexer_driver();
void lexer_enddriver();

char getNextChar(char* lexeme, int* length);
TokenInfo tokenGen(TokenInfo newToken, TOKEN token_name);
TokenInfo failure(TokenInfo newToken, char ch);
void retract(char* lexeme, int* length);

const char* convert_token_lexer(TOKEN sym);