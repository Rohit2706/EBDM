#include "SymbolTable.h"

// Data Structure for Function Table 

// Enum for storing the status of the Module
typedef enum{DECLARED, DEFINED, DECANDDEF} status;

// Structure for nodes in input and output lists
typedef struct listNode{                   
  char lexeme[25];                   
  TYPE_STRUCT type;              
  struct listNode* next;
}listNode;

// To encapsulate the data stored in function table
typedef struct FTValue{
  status functionState;
  int flag;           
  listNode* inputList;
  listNode* outputList;
  int outputEnd;
  TYPE_STRUCT type;
  SYMBOL_TABLE* localSymbolTable;
  SYMBOL_TABLE* inputSymbolTable;
}FTValue;

// Structure for a Function Table Entry (implemented as Hash Table)
typedef struct FTEntry{
  char* key;
  FTValue* value;
  struct FTEntry* next;
}FTEntry;

// Hash Table Structure for Function Table
typedef struct FUNCTION_TABLE{
  int size;
  int capacity;
  FTEntry** table;
}FUNCTION_TABLE;

// Function Prototypes

FUNCTION_TABLE* ft_create(int size);
int ft_hash_func(FUNCTION_TABLE *ht, char* key );
FTEntry* ft_create_pair(char* key, FTValue* val);
void insert_FTEntry(FUNCTION_TABLE *ht, char* key, FTValue* val);
FTValue* get_ftvalue(FUNCTION_TABLE *ht, char* key);