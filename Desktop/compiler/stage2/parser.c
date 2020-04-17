//Group No. 7
//ANIRUDH GOYAL 2017A7PS0031P
//ANISHKUMAR SS 2017A7PS0069P
//ROHIT JAIN 2017A7PS0122P
//ADITYA SAXENA 2017A7PS0166P

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "parser.h"
#include "lexer.h"
Rule firstMap[NT_SIZE];
iterateRule followMap[NT_SIZE];

FILE* grammarFile;

// To populate first set mapping
void populateFirstMap(){
	for(int i=0;i<NT_SIZE;i++){
  	firstMap[i].head=NULL;
  	firstMap[i].tail=NULL;
  }

  for(int i=0;i<GRAMMAR_SIZE;i++){
		NON_TERMINAL index = (grammar[i]->head->data).nt_val;
		if(firstMap[index].head==NULL){
			firstMap[index].head = malloc(sizeof(Rule_node));
			firstMap[index].head->rule = i;
			firstMap[index].head->next = NULL;
			firstMap[index].tail = firstMap[index].head;
		}
		else{
			firstMap[index].tail->next = malloc(sizeof(Rule_node));
			firstMap[index].tail = firstMap[index].tail->next;
			firstMap[index].tail->rule = i;
			firstMap[index].tail->next = NULL;
		}
	}
}

// To populate follow set mapping
void populateFollowMap(){
	
	for(int i=0;i<NT_SIZE;i++){
	  	followMap[i].head=NULL;
	  	followMap[i].tail=NULL;
    }

    for(int i=0;i<GRAMMAR_SIZE;i++){
  		node* temp=grammar[i]->head->next;
  		int compareTag;
		NON_TERMINAL index;

		while(temp!=NULL){
			compareTag = temp->tag;
			if(compareTag==2){
				index = (temp->data).nt_val;
				if(followMap[index].head==NULL){
					followMap[index].head = malloc(sizeof(iterateNode));
					followMap[index].head->rule = i;
					followMap[index].head->position = temp;
					followMap[index].head->next = NULL;
					followMap[index].tail = followMap[index].head;
				}

				else{
					followMap[index].tail->next = malloc(sizeof(iterateNode));
					followMap[index].tail = followMap[index].tail->next;
					followMap[index].tail->rule = i;
					followMap[index].tail->position = temp;
					followMap[index].tail->next = NULL;
				}
			}
			temp=temp->next;
		}
	}
}

// To calculate first set
unsigned long int calculateFirst(NON_TERMINAL nt){
  	if(first[nt])
    	return first[nt];

	Rule_node* curr = firstMap[nt].head;
	while(curr!=NULL){
    node* symbol_node = grammar[curr->rule]->head->next ; //Symbol is union of NT and T
    unsigned long val = 0;
    while(symbol_node!=NULL) 
    {
			if(symbol_node->tag==1){
      	first[nt] = first[nt] | (1lu<<(symbol_node->data).t_val);
        break;
      }
    	else{
        val = calculateFirst((symbol_node->data).nt_val);
      	first[nt] = first[nt] | ((val&1)?(val-1):val);
      }
      if(first[(symbol_node->data).nt_val]&1){
      	symbol_node = symbol_node->next;
      }
      else
        break;
    }
    
    if(symbol_node==NULL)
      first[nt] = first[nt] | 1;
    
    curr = curr->next;
	}
  
  return first[nt];
}

// To calculate follow set
unsigned long int calculateFollow(NON_TERMINAL nt){
	if(follow[nt])
    	return follow[nt];

	iterateNode* curr = followMap[nt].head;
	if(firstMap[nt].head->rule==0)
		follow[nt] = 2;

	while(curr!=NULL){
	    node* symbol_node = curr->position->next;
	    unsigned long val = 0;
	    while(symbol_node!=NULL) 
	    {
		  if(symbol_node->tag==1){
	        follow[nt] = follow[nt] | (1lu<<(symbol_node->data).t_val);
	        break;
	      }
          val = first[(symbol_node->data).nt_val];
      	  follow[nt] = follow[nt] | ((val&1)?(val-1):val);
      	  if(first[(symbol_node->data).nt_val]&1){
      	 	symbol_node = symbol_node->next;
      	  }
      	  else
      	  	break;
	    }

	    if(symbol_node==NULL){
	      NON_TERMINAL temp_nt = (grammar[curr->rule]->head->data).nt_val;
	      if(nt != temp_nt){
	      	if(follow[temp_nt])
	      		follow[nt] = follow[nt] | follow[temp_nt];
	      	else
	      		follow[nt] = follow[nt] | calculateFollow(temp_nt);
	      }
		}
	    
	    curr = curr->next;
	}
  
  return follow[nt];
}

// To calculate both first and follow sets
void computeFirstAndFollowSets(){
	for(int i=0;i<NT_SIZE;i++){
		first[i] = 0;
		follow[i] = 0;
	}
	for(int i=0;i<NT_SIZE;i++)
 		calculateFirst((NON_TERMINAL)i);
 	for(int i=0;i<NT_SIZE;i++)
 		calculateFollow((NON_TERMINAL)i);
}

// To create the parse table for predictive parsing
void createParseTable(){
	for(int i=0;i<NT_SIZE;i++){
		for(int j=0;j<TOKEN_SIZE;j++)
			parseTable[i][j] = -1;
	}
	for(int i=0;i<GRAMMAR_SIZE;i++){
		node* temp = grammar[i]->head;

		NON_TERMINAL nt = (temp->data).nt_val;
		temp = temp->next;

		while(temp!=NULL){
			if(temp->tag==1){
				if((temp->data).t_val == EPSILON)
					temp = NULL;
				else
					parseTable[nt][(temp->data).t_val] = i;
				break;
			}
			else{
				int pos=1;
				unsigned long int val = first[(temp->data).nt_val];
				
				val>>=1;
				while(val){
					if(val&1){
						parseTable[nt][pos] = i;
					}
					val >>= 1;
					pos++;
				}

				if(first[(temp->data).nt_val]&1)
					temp = temp->next;
				else
					break;
			}
		}

		if(temp==NULL){
			unsigned long int val = follow[nt];
			int pos=1;
			val >>= 1;
			while(val){
				if(val&1){
					parseTable[nt][pos] = i;
				}
				val >>= 1;
				pos++;
			}
		}
	}

	for(int i=0;i<NT_SIZE;i++){
		unsigned long int val = follow[i];
			int pos=1;
			val>>=1;
			while(val){
				if(val&1 && parseTable[i][pos]==-1){
					parseTable[i][pos]=-2;
				}
				val >>= 1;
				pos++;
			}
	}
}

tree_node* parseInputSourceCode(int perror_flag){

    // Initialising every variable for the Parse tree
    TOKEN term;
    tagged_union  stackval;

    stack* st = makeStack();

    stackval.tag = 1; 
    stackval.value.t_val =  DOLLAR;
    tree_node* dollarStack=makenode(stackval);
    push(st,dollarStack);

    stackval.tag = 2; 
    stackval.value.nt_val =  PROGRAM_NT;    
    tree_node* Root = makenode(stackval); 
    push(st,Root);

    int rule_no;
    int error_flag=1;
    // End of initializing

    TokenInfo tokeninfo = getNextToken();
    term = tokeninfo.token; 

    while(term!=DOLLAR){      
        Symbol s2;
        s2.t_val = term;
        stackval = top(st)->val;
        tree_node* head = top(st);

        if(stackval.tag==1 && stackval.value.t_val == term ){

            tree_node* poppedNode=pop(st);
            strcpy(poppedNode->lexeme,tokeninfo.lexeme);
    		poppedNode->line_no=tokeninfo.line_no;
   			poppedNode->tag=tokeninfo.tag;
    		poppedNode->value=tokeninfo.value;

            tokeninfo = getNextToken();
            term = tokeninfo.token;
            continue;
        }
        else if (stackval.tag==1 && stackval.value.t_val != term ){
        		if(perror_flag){
            		printf("Line %d: syntax error  - expected token '%s' got '%s'\n",tokeninfo.line_no, 
            			convert_token_lexer(stackval.value.t_val),convert_token_lexer(term));
                    error_flag = 0;
        		}

            tree_node* next_sval = pop(st);
            if((top(st)->val).tag==1){
            	if((top(st)->val).value.t_val == term)
	            	pop(st);
	            else
	            	push(st,next_sval);
	            
	            tokeninfo = getNextToken();
	            term = tokeninfo.token;
	            continue;
            }

            if((top(st)->val).tag==2 && parseTable[(top(st)->val).value.nt_val][term]>=0)
            	continue;
            else{
                push(st,next_sval);
            }
            
            tokeninfo = getNextToken();
            term = tokeninfo.token;
        }
        else {

            rule_no = parseTable[stackval.value.nt_val][term];
            
            if(rule_no==-1){
            	
            	if(perror_flag){
            		printf("Line %d: syntax error  - unexpected token received '%s'\n",tokeninfo.line_no, convert_token_lexer(term));   
                    error_flag = 0; 
            	}
            	while(rule_no==-1){
                	tokeninfo = getNextToken();
                	term=tokeninfo.token;
                	rule_no = parseTable[stackval.value.nt_val][term];
               	}

            }
            else if(rule_no==-2){
                pop(st);
            }
            else{

                node* temp = grammar[rule_no]->head->next;
                while(temp){
                    tagged_union t;
                    t.value = temp->data;
                    t.tag = temp->tag;
                    addsinglenode(head,t);
                    temp = temp->next;
                }

                pop(st);
                for(int i= head->no_child-1;i>=0;i--){
                    if((head->child[i]->val).tag==1 && (head->child[i]->val.value).t_val==EPSILON)
                        continue;
                    push(st,head->child[i]);
                }
            }
        }
    }

    stackval = top(st)->val;

    while(term==DOLLAR){
    	if(stackval.tag==1 && stackval.value.t_val == term){
    		break;
    	}

    	else if(stackval.tag==1 && stackval.value.t_val != term){
    		if(perror_flag)
        		printf("SYNTAX ERROR 'UNEXPECTED TOKEN(DOLLAR)' at line: %d '%s'\n",tokeninfo.line_no, convert_token_lexer(term)); 
                error_flag = 0;   
        	break;
    	}

    	else{
    		rule_no = parseTable[stackval.value.nt_val][term];
    		

    		if(rule_no==-1){
            	
            		if(perror_flag)
            			printf("SYNTAX ERROR type 2(DOLLAR) at line %d: '%s'\n",tokeninfo.line_no, convert_token_lexer(term));
                        error_flag = 0;       
	           		
            	break;
            }

            else if(rule_no==-2){
                pop(st);
                if(perror_flag)
                	printf("SYNTAX ERROR type 3 at line(DOLLAR) %d: '%s'\n",tokeninfo.line_no, convert_token_lexer(term));
                    error_flag = 0;
                
                break;
            }

            else{
            	tree_node* head = top(st);
            	stackval = top(st)->val;
            	
                node* temp = grammar[rule_no]->head->next;
                while(temp){
                    tagged_union t;
                    t.value = temp->data;
                    t.tag = temp->tag;
                    addsinglenode(head,t);
                    temp = temp->next;
                }

                pop(st);
                for(int i= head->no_child-1;i>=0;i--){
                    if((head->child[i]->val).tag==1 && (head->child[i]->val.value).t_val==EPSILON)
                        continue;
                    push(st,head->child[i]);
                }
            }
    	}
    }
    return Root;
}

// Utility Functions

// To convert from terminals/ non-terminal to strings for better printing results

const char* convert_to_string(Symbol sym, int tag){
    if(tag==2){
    	switch(sym.nt_val){
	    	case PROGRAM_NT: return "program" ; break;
	        case MODULEDECLARATIONS: return "moduledeclarations" ; break;
	        case MODULEDECLARATION: return "moduledeclaration" ; break;
	        case OTHERMODULES: return "othermodules" ; break;
	        case DRIVERMODULE: return "drivermodule" ; break;
	        case MODULE_NT: return "module" ; break;
	        case RET: return "ret" ; break;
	        case INPUT_PLIST: return "input_plist" ; break;
	        case INPUT_PLIST_1: return "input_plist_1" ; break;
	        case OUTPUT_PLIST: return "output_plist" ; break;
	        case OUTPUT_PLIST_1: return "output_plist_1" ; break;
	        case DATATYPE: return "datatype" ; break;
	        case TYPE: return "type" ; break;
	        case MODULEDEF: return "moduledef" ; break;
	        case STATEMENTS: return "statements" ; break;
	        case STATEMENT: return "statement" ; break;
	        case IOSTMT: return "iostmt" ; break;
	        case VAR: return "var" ; break;
	        case VAR_ID_NUM: return "var_id_num" ; break;
	        case BOOLCONSTT: return "boolconstt" ; break;
	        case WHICHID: return "whichid" ; break;
	        case SIMPLESTMT: return "simplestmt" ; break;
	        case ASSIGNMENTSTMT: return "assignmentstmt" ; break;
	        case WHICHSTMT: return "whichstmt" ; break;
	        case LVALUEIDSTMT: return "lvalueidstmt" ; break;
	        case LVALUEARRSTMT: return "lvaluearrstmt" ; break;
	        case INDEX: return "index" ; break;
	        case MODULEREUSESTMT: return "modulereusestmt" ; break;
	        case OPTIONAL: return "optional" ; break;
	        case IDLIST: return "idlist" ; break;
	        case IDLIST_1: return "idlist_1" ; break;
	        case EXPRESSION: return "expression" ; break;
	        case U: return "u" ; break;
	        case U_1: return "u_1" ; break;
	        case ARMORBOOL: return "armorbool" ; break;
	        case N7: return "n7" ; break;
	        case ANYTERM: return "anyterm" ; break;
	        case N8: return "n8" ; break;
	        case ARITHMETICEXPR: return "arithmeticexpr" ; break;
	        case ARITHMETICEXPR_1: return "arithmeticexpr_1" ; break;
	        case TERM: return "term" ; break;
	        case TERM_1: return "term_1" ; break;
	        case FACTOR: return "factor" ; break;
	        case OP1: return "op1" ; break;
	        case OP2: return "op2" ; break;
	        case LOGICALOP: return "logicalop" ; break;
	        case RELATIONALOP: return "relationalop" ; break;
	        case DECLARESTMT: return "declarestmt" ; break;
	        case CONDITIONALSTMT: return "conditionalstmt" ; break;
	        case CASESTMT: return "casestmt" ; break;
	        case CASESTMT_1: return "casestmt_1" ; break;
	        case VALUE_NT: return "value" ; break;
	        case DEFAULT_NT: return "default" ; break;
	        case ITERATIVESTMT: return "iterativestmt" ; break;
	        case RANGE_ARRAYS: return "range_arrays" ; break;
	        case RANGE: return "range" ; break;
	       	default: return "Unrecognized NT"; break;
    	}
    }

    switch(sym.t_val)
    {
        case PLUS: return "PLUS" ; break;
        case MINUS: return "MINUS" ; break;
        case MUL: return "MUL" ; break;
        case DIV: return "DIV" ; break;
        case LT: return "LT" ; break;
        case LE: return "LE" ; break;
        case GE: return "GE" ; break;
        case GT: return "GT" ; break;
        case EQ: return "EQ" ; break;
        case NE: return "NE" ; break;
        case DEF: return "DEF" ; break;
        case ENDDEF: return "ENDDEF" ; break;
        case DRIVERDEF: return "DRIVERDEF" ; break;
        case DRIVERENDDEF: return "DRIVERENDDEF" ; break;
        case COLON: return "COLON" ; break;
        case RANGEOP: return "RANGEOP" ; break;
        case SEMICOL: return "SEMICOL" ; break;
        case COMMA: return "COMMA" ; break;
        case ASSIGNOP: return "ASSIGNOP" ; break;
        case SQBO: return "SQBO" ; break;
        case SQBC: return "SQBC" ; break;
        case BO: return "BO" ; break;
        case BC: return "BC" ; break;
        case ID: return "ID" ; break;
        case NUM: return "NUM" ; break;
        case RNUM: return "RNUM" ; break;
        case INTEGER: return "INTEGER" ; break;
        case REAL: return "REAL" ; break;
        case BOOLEAN: return "BOOLEAN" ; break;
        case OF: return "OF" ; break;
        case ARRAY: return "ARRAY" ; break;
        case START: return "START" ; break;
        case END: return "END" ; break;
        case DECLARE: return "DECLARE" ; break;
        case MODULE: return "MODULE" ; break;
        case DRIVER: return "DRIVER" ; break;
        case PROGRAM: return "PROGRAM" ; break;
        case GET_VALUE: return "GET_VALUE" ; break;
        case PRINT: return "PRINT" ; break;
        case USE: return "USE" ; break;
        case WITH: return "WITH" ; break;
        case PARAMETERS: return "PARAMETERS" ; break;
        case TRUE: return "TRUE" ; break;
        case FALSE: return "FALSE" ; break;
        case TAKES: return "TAKES" ; break;
        case INPUT: return "INPUT" ; break;
        case RETURNS: return "RETURNS" ; break;
        case AND: return "AND" ; break;
        case OR: return "OR" ; break;
        case FOR: return "FOR" ; break;
        case IN: return "IN" ; break;
        case WHILE: return "WHILE"; break;
        case SWITCH: return "SWITCH" ; break;
        case CASE: return "CASE" ; break;
        case BREAK: return "BREAK" ; break;
        case DEFAULT: return "DEFAULT" ; break;
        case EPSILON: return "EPSILON"; break;
        case DOLLAR: return "$"; break;
        default: return "UNRECOGNIZED TOKEN"; break;
    }
}
// To convert from bit representation of sets to individual terminals and print
void convertSet(unsigned long int val){
	int pos = 0;
	Symbol s;
	while(val){
		if(val&1){
			s.t_val = (TOKEN)pos;
			printf("%s, ",convert_to_string(s,1));
		}
		val >>=1;
		pos++;
	}
}

// To print first sets for all non-terminals
void printFirst(){
	Symbol s;
	printf("\n\nFIRST SET\n\n");
	for(int i=0;i<NT_SIZE;i++){
		s.nt_val = (NON_TERMINAL)i;
	  	printf("NT= %-25s\t First= {",convert_to_string(s,2));
	  	convertSet(first[i]);
	  	printf("}\n");
	}

	printf("\n\n");
}

// To print follow sets for all non-terminals
void printFollow(){
	Symbol s;
	printf("\n\nFOLLOW SET\n\n");
	for(int i=0;i<NT_SIZE;i++){
	 	s.nt_val = (NON_TERMINAL)i;
	  	printf("NT= %-25s\t Follow= {",convert_to_string(s,2));
	  	convertSet(follow[i]);
	  	printf("}\n");
	}

	printf("\n\n");
}

void parser_driver(char* filename, int error_flag){
	lexer_driver(filename, error_flag);

	ht_symbols = mappingtable_create(MAPTABLE_SIZE);
	add_terminals(ht_symbols);   
    add_nonterminals(ht_symbols);

    grammarFile = NULL;
	grammarFile = fopen("grammar.txt","r");

	if (grammarFile == NULL) {
	    printf("Grammar File Not Found \n");
	    return;
	}

	for(int i=0;i<GRAMMAR_SIZE;i++){
	    grammar[i] = createLinkedList();
	}

  	readIntoArr(grammarFile, grammar);

  	populateFirstMap();
	populateFollowMap();
	computeFirstAndFollowSets();
	createParseTable();

    fclose(grammarFile);
}

void parser_enddriver(){
	lexer_enddriver();
    ht_symbols = NULL;
    for(int i=0;i<GRAMMAR_SIZE;i++)
        grammar[i] = NULL;
}

void printParseTree(tree_node* temp, tagged_union parent, FILE* fp){

    if(temp->no_child==0){
        fprintf(fp, "%-20s\t\t%-4d\t\t%-20s\t",temp->lexeme,temp->line_no, convert_to_string( (temp->val).value,1));
        if(temp->tag==1)
            fprintf(fp, "%-8d",(temp->value).num_value);
        else if(temp->tag==2)
            fprintf(fp, "%-8f",(temp->value).rnum_value);
        else
            fprintf(fp, "None    ");

        fprintf(fp, "%-20s\tYes       \n",convert_to_string(parent.value,parent.tag));
        return;
    }

    printParseTree(temp->child[0],temp->val, fp);

    if((temp->val).tag==1){
        fprintf(fp, "%-20s\t\t%-4d\t\t%-20s\t",temp->lexeme,temp->line_no, convert_to_string( (temp->val).value,1));
        if(temp->tag==1)
            fprintf(fp, "%-8d",(temp->value).num_value);
        else if(temp->tag==2)
            fprintf(fp, "%-8f",(temp->value).rnum_value);
        else
            fprintf(fp, "None    ");

        fprintf(fp, "%-20s\tNo        \n",convert_to_string(parent.value,parent.tag));
    }
    else{
        fprintf(fp, "--------------------\t\t-   \t\t%-20s\t", convert_to_string((temp->val).value,2));
        fprintf(fp, "None    ");
        fprintf(fp, "%-20s\tNo        ",convert_to_string(parent.value,parent.tag));
        fprintf(fp, "\t%-20s\n",convert_to_string((temp->val).value,2));
    }
    for(int i=1;i<temp->no_child;i++)
        printParseTree(temp->child[i], temp->val, fp);
}


tree_node* run_lexer_parser(char* filename, int tree_flag, int error_flag){
	parser_driver(filename, error_flag);

	tree_node* Root = parseInputSourceCode(error_flag);
	tagged_union t;
	t.value.t_val = DOLLAR;
	t.tag = 1;
	if(tree_flag){

		FILE* fp = NULL;
		fp = stdout;

        fprintf(fp,"\n\nPrinting Parse Tree:\n\n");
		fprintf(fp,"Lexeme_Current_Node \t\tLine\t\tCurrent_Token       \t");
		fprintf(fp,"Value   ");
		fprintf(fp,"Parent_Symbol       \tisLeafNode");
		fprintf(fp,"\tCurrent_non_terminal\n\n"); 
		printParseTree(Root,t,fp);
	}
    return Root;
}