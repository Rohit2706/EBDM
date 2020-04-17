//Group No. 7
//ANIRUDH GOYAL 2017A7PS0031P
//ANISHKUMAR SS 2017A7PS0069P
//ROHIT JAIN 2017A7PS0122P
//ADITYA SAXENA 2017A7PS0166P

// This file lists the function prototypes for the lexical analyser (lexer.c)

#include "lexerDef.h"

// Functions declarations for lexer
void getStream(char* buffer);
TokenInfo getNextToken();
void removeComments(char *testcaseFile);

// Driver Functions
void lexer_driver(char* filename, int error_flag);
void lexer_enddriver();

// Utility Function declarations
char getNextChar(char* lexeme, int* length);
TokenInfo tokenGen(int* len, TokenInfo newToken, TOKEN token_name);
TokenInfo failure(int* len, TokenInfo newToken, char ch);
void retract(char* lexeme, int* length);

const char* convert_token_lexer(TOKEN sym);
void printTokens(char* filename);