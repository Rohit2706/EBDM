//Group No. 7
//ANIRUDH GOYAL 2017A7PS0031P
//ANISHKUMAR SS 2017A7PS0069P
//ROHIT JAIN 2017A7PS0122P
//ADITYA SAXENA 2017A7PS0166P

// This file implements function prototypes needed for the syntax analyser(parser.c)

#include "parserDef.h"

// To calculate first and follow sets
unsigned long int calculateFirst(NON_TERMINAL nt);
unsigned long int calculateFollow(NON_TERMINAL nt);
void computeFirstAndFollowSets();


void createParseTable();

void parser_driver();

// Utility Function Declarations
const char* convert_to_string(Symbol sym, int tag);
void convertSet(unsigned long int val);
void printFirst();
void printFollow();

void printParseTree(tree_node* temp, tagged_union parent, FILE* fp);
tree_node* run_lexer_parser(char* filename, int tree_flag, int error_flag);
void parser_enddriver();