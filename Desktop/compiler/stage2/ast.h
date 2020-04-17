
#include "parser.h"
#include "lexer.h"

tree_node* create_ast(tree_node* parse_tree);
tree_node* keep_node(tree_node* parse_tree);
void addnoderef(tree_node* head, tree_node* grandchild);
void addgrandchild(tree_node* parse_tree);
void removechild(tree_node* parent, int i);
void handle_recursion(tree_node* parse_tree);
tree_node* keep_parent(tree_node* parse_tree);
tree_node* keep_child(tree_node* parse_tree);

listNode* getList(tree_node* root, SYMBOL_TABLE* enterST);
int get_width(TYPE_STRUCT temp);
void populateST(tree_node* root, SYMBOL_TABLE* curr_st);  

FUNCTION_TABLE* ft;
int outOfRange(int search, int lower, int upper);
STValue* returnIfPresentST(char* inputKey, SYMBOL_TABLE* stInput, tree_node* inputNode);
void extractType(tree_node* root, SYMBOL_TABLE* curr_st);

void generateAssembly(tree_node* ast, FILE* fp);

tree_node* ast_driver(char* filename, int ast_flag, int ef, int compress_flag, int printST, int printAR, int printarray, int codegenflag, FILE* fp);

int error_flag;

void printSymbolTable();
void helperSymTable(SYMBOL_TABLE* inputST, char* moduleName, int level, int outputEnd);
void printSymbol(STEntry* inp, char* moduleName, int level, int outputEnd);
void printActivationRecord();

void printarraysymbol(STEntry* inp, char* moduleName, int level, int outputEnd);
void helperarray(SYMBOL_TABLE* inputST, char* moduleName, int level, int outputEnd);
void printArray();

void generateData(FILE* fp);
