// This file implements function prototypes needed for the syntax analyser(parser.c)

#include "parserDef.h"

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