
#include "ast.h"
int inpoffset = 0;
void addnoderef(tree_node* head, tree_node* grandchild){
	head->child = realloc(head->child, (head->no_child+1)*(sizeof(tree_node)));
    head->child[head->no_child] = grandchild; 
    head->no_child++;
}
void addgrandchild(tree_node* parse_tree){
	tree_node* curr_child = parse_tree->child[parse_tree->no_child-1];
	int n = curr_child->no_child;
	tree_node** grandchild = curr_child->child;
	free(curr_child);
	parse_tree->no_child--;
	parse_tree->child = realloc(parse_tree->child, (parse_tree->no_child)*(sizeof(tree_node)));

	for(int i=0;i<n;i++)
		addnoderef(parse_tree, grandchild[i]);
}

void removechild(tree_node* parent, int i){
	free(parent->child[i]);
	while(i+1<parent->no_child){
		parent->child[i] = parent->child[i+1];
		i++;
	}
	parent->no_child--;
	parent->child = realloc(parent->child, (parent->no_child)*(sizeof(tree_node *)));
}

void handle_recursion(tree_node* parse_tree){

	tree_node* curr = parse_tree->child[parse_tree->no_child-1];
	tree_node* temp;
	for(int i=0;i<parse_tree->no_child-1;i++){
		parse_tree->child[i] = create_ast(parse_tree->child[i]);
		if(parse_tree->child[i] == NULL){
			removechild(parse_tree, i);
			i--;
		}
	}
	parse_tree->no_child--;
	parse_tree->child = realloc(parse_tree->child, (parse_tree->no_child)*(sizeof(tree_node)));

	while(curr->no_child!=1){
		for(int i=0;i<curr->no_child-1;i++){
			curr->child[i] = create_ast(curr->child[i]);
			if(curr->child[i]!=NULL)
				addnoderef(parse_tree, curr->child[i]);
		}
		temp = curr;
		curr = curr->child[curr->no_child-1];
		free(temp);
	}
	free(curr->child);
	free(curr);
}

tree_node* keep_node(tree_node* parse_tree){
	for(int i=0;i<parse_tree->no_child;i++){
		parse_tree->child[i] = create_ast(parse_tree->child[i]);
		if(parse_tree->child[i] == NULL){
			removechild(parse_tree, i);
			i--;
		}
	}

	return parse_tree;
}

tree_node* keep_parent(tree_node* parse_tree){
	parse_tree = keep_node(parse_tree);
	tree_node* childptr = parse_tree->child[0];
	parse_tree->no_child = childptr->no_child;
	parse_tree->child = childptr->child;
	free(childptr);
	return parse_tree;
}

tree_node* keep_child(tree_node* parse_tree){
	parse_tree = keep_node(parse_tree);
	tree_node* childptr = parse_tree->child[0];
	free(parse_tree);
	return childptr;
}

tree_node* create_ast(tree_node* parse_tree){
	if((parse_tree->val).tag==1){
		switch((parse_tree->val).value.t_val){
			case ASSIGNOP:
	        case ID: 
	        case NUM: 
	        case RNUM: 
	        case INTEGER: 
	        case REAL: 
	        case BOOLEAN: 
	        case GET_VALUE: 
	        case PRINT: 
	        case TRUE: 
	        case FALSE:  
	        			return parse_tree; 
	        			break;
	        default: return NULL; 
	        		 break;
		}
	}

	switch((parse_tree->val).value.nt_val){
			case PROGRAM_NT: 
			case DRIVERMODULE:
			case MODULE_NT:
			case IOSTMT:
			case LVALUEIDSTMT:
			case LVALUEARRSTMT:
			case MODULEREUSESTMT:
			case DECLARESTMT:
			case RANGE_ARRAYS:
			case RANGE:
								keep_node(parse_tree); 
								return parse_tree; break;

	        case MODULEDECLARATIONS: 
	        case OTHERMODULES:
	        case STATEMENTS:	if(parse_tree->no_child==1)
								return parse_tree;

	        case INPUT_PLIST_1:
	        case OUTPUT_PLIST_1:
	        case IDLIST_1:
	        case CASESTMT_1:	if(parse_tree->no_child==1){
	        						removechild(parse_tree,0);
	        						return parse_tree;
	        					}	
								handle_recursion(parse_tree);
							 	return parse_tree;
							 	break;

	        case MODULEDECLARATION: 
	        case TYPE:
	        case STATEMENT:
	        case BOOLCONSTT:
	        case WHICHID:
	        case SIMPLESTMT:
	        case WHICHSTMT:
	        case INDEX:
	        case VALUE_NT:
	        case VAR:
	        						 return keep_child(parse_tree); break;

	        case MODULEDEF: parse_tree->scope[0] = parse_tree->child[0]->line_no;
	        				parse_tree->scope[1] = parse_tree->child[2]->line_no;
	        				return keep_node(parse_tree); break;
	        				
	        case DATATYPE:  if(parse_tree->no_child==1)
	        					return keep_child(parse_tree);
	        				parse_tree->val = parse_tree->child[0]->val;
	        				parse_tree->line_no = parse_tree->child[0]->line_no;
	        				return keep_node(parse_tree); break;

	        case RET:	if(parse_tree->no_child==1)
	        				return parse_tree;
	        			return keep_parent(parse_tree); break;

	        case U_1: 
	        case FACTOR:  if(parse_tree->no_child==1)
	        			  	return keep_node(parse_tree);
	        			  return keep_parent(parse_tree);
	        			  break;

	 
	        case VAR_ID_NUM: if(parse_tree->no_child==1)
	        					return keep_child(parse_tree);
	        				 if(parse_tree->child[1]->no_child==1){
	        				 	removechild(parse_tree,1);
	        				 	return keep_child(parse_tree);
	        				 }
	        				 (parse_tree->val).value.t_val = ARRAY;
	        				 (parse_tree->val).tag = 1;
	        				 return keep_node(parse_tree); break;

	        case INPUT_PLIST:
			case OUTPUT_PLIST:
	        case IDLIST:
	        case ASSIGNMENTSTMT: parse_tree = keep_node(parse_tree);
	        					 addgrandchild(parse_tree);

	        					 return parse_tree; break;

	        case OPTIONAL:  if(parse_tree->no_child==1)
	        					return parse_tree;
	        				return keep_node(parse_tree); break;

	        case EXPRESSION: if((parse_tree->child[0]->val).value.nt_val == ARMORBOOL)
	        					return keep_parent(parse_tree); 
	        				 return keep_node(parse_tree); break;

	        case U: parse_tree->val = parse_tree->child[0]->val;
	        		parse_tree->line_no = parse_tree->child[0]->line_no;
	        		return keep_parent(parse_tree); break;
	         
	        case ARMORBOOL:
	        case ANYTERM:
	        case ARITHMETICEXPR:
	        case TERM:
	        		if(parse_tree->no_child==1) 
	        			return keep_node(parse_tree);

    				if(parse_tree->child[1]->no_child==1){
    					removechild(parse_tree,1);
    					return keep_parent(parse_tree);
    				}
    				keep_node(parse_tree);
    				tree_node* childptr = parse_tree->child[0];
    				tree_node* opptr = parse_tree->child[1];
    				opptr->childLeft = childptr->child;
    				opptr->no_leftchild = childptr->no_child;
    				removechild(parse_tree,0);
    				/*parse_tree->child = childptr->child;
    				addnoderef(parse_tree, opptr);
    				free(childptr);*/
    				return parse_tree;
    				break;
	        				

	        case N7:
	        case ARITHMETICEXPR_1:
	        case TERM_1:
	        		 parse_tree->val = parse_tree->child[0]->child[0]->val;
	        		 parse_tree->line_no = parse_tree->child[0]->child[0]->line_no;
	        		 removechild(parse_tree,0);
	        		 childptr = create_ast(parse_tree->child[0]);
    				 opptr = parse_tree->child[1];

    				 
    				 if(opptr->no_child==1){
    				 	free(opptr->child[0]);
    				 	free(opptr);
    				 	parse_tree->no_child = childptr->no_child;
    				 	parse_tree->child = childptr->child;
    				 	free(childptr);

    				 }
    				 else{
    				 	opptr = create_ast(opptr);
    				 	opptr->childLeft = childptr->child;
    				 	opptr->no_leftchild = childptr->no_child;
    				 	//free(childptr);
    				 	removechild(parse_tree,0);
    				 }
    				 return parse_tree;
    				 break;
	         
	        case N8: parse_tree->val = parse_tree->child[0]->child[0]->val;
	        		 parse_tree->line_no = parse_tree->child[0]->child[0]->line_no;
	        		 removechild(parse_tree,0);
	        		 return keep_parent(parse_tree);
	        		 break;
	        
	        case OP1:
	        case OP2:
	        case LOGICALOP:
	        case RELATIONALOP:	parse_tree->val = parse_tree->child[0]->val;
	        					parse_tree->line_no = parse_tree->child[0]->line_no;
	        					removechild(parse_tree,0);
	        					return parse_tree; break;

	        case CONDITIONALSTMT: parse_tree->val = parse_tree->child[0]->val;
	        					  parse_tree->line_no = parse_tree->child[0]->line_no;
	        					  parse_tree->scope[0] = parse_tree->child[4]->line_no;
	        					  parse_tree->scope[1] = parse_tree->child[7]->line_no;
	        					  return keep_node(parse_tree); break; 

	        case CASESTMT:  keep_node(parse_tree);
	        				addgrandchild(parse_tree);

	        				return parse_tree; break;

	        case DEFAULT_NT: if(parse_tree->no_child==1)
	        					return parse_tree;
	        				 return keep_node(parse_tree); break;
	        case ITERATIVESTMT: parse_tree->val = parse_tree->child[0]->val;
	        					parse_tree->line_no = parse_tree->child[0]->line_no;
	        					if((parse_tree->val).value.t_val == FOR){
	        						parse_tree->scope[0] = parse_tree->child[6]->line_no;
	        					  	parse_tree->scope[1] = parse_tree->child[8]->line_no;
	        					}
	        					else{
	        						parse_tree->scope[0] = parse_tree->child[4]->line_no;
	        					  	parse_tree->scope[1] = parse_tree->child[6]->line_no;
	        					}

	        					return keep_node(parse_tree); break; 

	       	default: return NULL; break;
	}
}


void printExpression(tree_node* temp, tagged_union parent, FILE* fp){
    
    if(temp->childLeft!=NULL){
        for(int i=0;i<temp->no_leftchild;i++)
            printExpression(temp->childLeft[i],temp->val,fp);
    }

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
    for(int i=0;i<temp->no_child;i++)
        printExpression(temp->child[i],temp->val,fp);
}


void printAST(tree_node* temp, tagged_union parent, FILE* fp){

    if((temp->val).value.nt_val == EXPRESSION){
        printExpression(temp,parent,fp);
        return;
    }

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

	printAST(temp->child[0],temp->val, fp);

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
		printAST(temp->child[i], temp->val, fp);
}


int traverseTree(tree_node* root){
	int count = 1;
	for(int i=0;i<root->no_leftchild;i++)
		count += traverseTree(root->childLeft[i]);
	for(int i=0;i<root->no_child;i++)
		count += traverseTree(root->child[i]);

	return count;
}


void printCompressionRatio(long ptcount, long astcount){

	printf("\nParse tree:\n");
	printf("Number of nodes: %ld\n",ptcount);
	printf("Total Memory allocated: %ld\n",ptcount*sizeof(tree_node));

	printf("\nAbstract Syntax tree:\n");
	printf("Number of nodes: %ld\n",astcount);
	printf("Total Memory allocated: %ld\n",astcount*sizeof(tree_node));

	printf("\nCompression Percentage = %0.4lf \n\n",((double)(ptcount - astcount)/ptcount)*100.0);
}


tree_node* ast_driver(char* filename, int ast_flag, int ef, int compress_flag, int printST, int printAR, int printarray, int codegenflag, FILE* fp){
	error_flag = ef;
	tree_node* parse_tree = run_lexer_parser(filename,0,1);
	long ptcount = 0, astcount = 0;
	if(compress_flag)
		ptcount = traverseTree(parse_tree);
	tree_node* ast =create_ast(parse_tree);
	if(compress_flag)
		astcount = traverseTree(ast);

	tagged_union t;
	t.value.t_val = DOLLAR;
	t.tag = 1;

	
	if(ast_flag){
		FILE* fp = NULL;
		fp = stdout;

		fprintf(fp,"\n\nPrinting Abstract Syntax Tree:\n\n");
		fprintf(fp,"Lexeme_Current_Node \t\tLine\t\tCurrent_Token       \t");
		fprintf(fp,"Value   ");
		fprintf(fp,"Parent_Symbol       \tisLeafNode");
		fprintf(fp,"\tCurrent_non_terminal\n\n"); 
		printAST(ast,t,fp);
		return ast;
	}

	if(compress_flag){
		printCompressionRatio(ptcount, astcount);
		return ast;
	}
	
	populateST(ast, NULL);
	extractType(ast,NULL);
	printf("\nCode Compiled Successfully\n\n");
	if(printST){
		printSymbolTable();
	}
	else if(printAR){
		printActivationRecord();
	}
	else if(printarray){
		printArray();
	}
	//else if(codegenflag)
		//generateData(fp);
	parser_enddriver();
	return ast;
}


void printSymbolTable(){
    FTEntry* currFunc;
    char* moduleName;
    FTValue* currFuncDets;

    printf("\n\n");

    printf("%-20s  %-20s  %-9s  ", "Variable Name", "Module Name","Scope");
    printf("%5s  %-7s  %-20s  %-11s\t", "Width", "isArray", "Static or Dynamic", "Range");
    printf("%-10s  %-6s  %s", "Datatype", "Offset", "Nesting level");

    printf("\n");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");
    int size = ft->size;
    for(int i=0;i<size;i++){
        currFunc = ft->table[i];
        
        while(currFunc!=NULL){
            moduleName = currFunc->key;
            currFuncDets = currFunc->value;
            int outputEnd = currFuncDets ->outputEnd;
            if(currFuncDets->inputSymbolTable!=NULL){
            	helperSymTable(currFuncDets->inputSymbolTable, moduleName, 0, 0);
            	inpoffset = currFuncDets->inputSymbolTable->curr_offset;
            }
            else
            	inpoffset = 0;
            helperSymTable(currFuncDets->localSymbolTable, moduleName, 1, outputEnd);
            currFunc = currFunc->next;
        }
        
    }
    
    printf("\n\n");
}


void helperSymTable(SYMBOL_TABLE* inputST, char* moduleName, int level, int outputEnd){

	if(level>1)
        strcat(strcat(inputST->name,"_"),moduleName);
    for(int i=0;i<inputST->size;i++){
        STEntry* currSym = inputST->table[i];
        while(currSym!=NULL && currSym!=(STEntry*)(0x20)){
        	if(level>1)
        		printSymbol(currSym,inputST->name, level, outputEnd);
        	else
            	printSymbol(currSym, moduleName, level, outputEnd);
            currSym = currSym->next;
        }

    }

    for(int i=0;i<inputST->no_child;i++){
        helperSymTable(inputST->child[i], moduleName, level+1, 0);
    }

}

void printSymbol(STEntry* inp, char* moduleName, int level, int outputEnd){
    STValue* inpValue = inp->value;
    if(inp->value==NULL)
    	return;
    if(inpValue->offset < outputEnd){
        level = 0;
        inpValue->offset += inpoffset;
    }

    else{
        inpValue->offset -= outputEnd;
    }
    FILE* fp;
    fp = stdout;
    fprintf(fp,"%-20s  %-20s  %-4d-%4d  ", inp->key, moduleName, (inpValue->scope)[0], (inpValue->scope)[1]);
    
    TYPE_STRUCT inpType = inpValue->type;

    if(inpType.isArray == 1){
    	
        if(inpType.isStatic == 1){
            fprintf(fp,"%-5d  %-7s  %-20s  [%-4d-%4d]\t", inpValue->width, "yes", "Static Array", (inpType.begin), (inpType.end));
            fprintf(fp,"%-10s  %-6d  %-3d", convert_token_lexer(inpType.dtype), inpValue->offset, level);
        }
        else if(inpType.isStatic == 0){
            fprintf(fp,"%-5d  %-7s  %-20s  [%-4s-%4s]\t", inpValue->width, "yes", "Dynamic Array", inpType.begins, inpType.ends);
            fprintf(fp,"%-10s  %-6d  %-3d", convert_token_lexer(inpType.dtype), inpValue->offset, level);
        }
    }

    else{
        fprintf(fp,"%-5d  %-7s  %-20s  %-11s\t", inpValue->width , "no ", "---", "---");
        fprintf(fp,"%-10s  %-6d  %-3d", convert_token_lexer(inpType.dtype), inpValue->offset, level);
    }
    fprintf(fp,"\n");

    if(level == 0 && inpValue->offset> inpoffset){
        inpValue->offset -= inpoffset;
    }
}

void printActivationRecord(){
    FTEntry* currFunc;
    char* moduleName;
    FTValue* currFuncDets;

    printf("\n\n");

    printf("%-20s\t\tActivation Record Size", "Module Name");

    printf("\n");
    printf("-----------------------------------------------\n");
    int size = ft->size;
    for(int i=0;i<size;i++){
        currFunc = ft->table[i];
        
        while(currFunc!=NULL){
            moduleName = currFunc->key;
            currFuncDets = currFunc->value;
            int recordSize = currFuncDets->localSymbolTable->curr_offset;
            if(currFuncDets->inputSymbolTable!=NULL)
            	recordSize += currFuncDets->inputSymbolTable->curr_offset;
            currFunc = currFunc->next;
            printf("%-20s\t\t%d\n",moduleName, recordSize);
        }
        
    }
    
    printf("\n\n");
}


void printArray(){
    FTEntry* currFunc;
    char* moduleName;
    FTValue* currFuncDets;

    printf("\n\n");

    printf("%-20s  %-20s  %-9s  ", "Variable Name", "Module Name","Scope");
    printf("%5s  %-7s  %-20s  %-11s\t", "Width", "isArray", "Static or Dynamic", "Range");
    printf("%-10s  %-6s  %s", "Datatype", "Offset", "Nesting level");

    printf("\n");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");
    int size = ft->size;
    for(int i=0;i<size;i++){
        currFunc = ft->table[i];
        
        while(currFunc!=NULL){
            moduleName = currFunc->key;
            currFuncDets = currFunc->value;
            int outputEnd = currFuncDets ->outputEnd;
            if(currFuncDets->inputSymbolTable!=NULL)
            	helperarray(currFuncDets->inputSymbolTable, moduleName, 0, 0);
            helperarray(currFuncDets->localSymbolTable, moduleName, 1, outputEnd);
            currFunc = currFunc->next;
        }
        
    }
    
    printf("\n\n");
}


void helperarray(SYMBOL_TABLE* inputST, char* moduleName, int level, int outputEnd){

	if(level>1)
        strcat(strcat(inputST->name,"_"),moduleName);
    for(int i=0;i<inputST->size;i++){
        STEntry* currSym = inputST->table[i];
        while(currSym!=NULL && currSym!=(STEntry*)(0x20)){
        	if(level>1)
        		printarraysymbol(currSym,inputST->name, level, outputEnd);
        	else
            	printarraysymbol(currSym, moduleName, level, outputEnd);
            currSym = currSym->next;
        }

    }

    for(int i=0;i<inputST->no_child;i++){
        helperarray(inputST->child[i], moduleName, level+1, 0);
    }

}

void printarraysymbol(STEntry* inp, char* moduleName, int level, int outputEnd){
    STValue* inpValue = inp->value;
    if(inp->value==NULL)
    	return;
    if(inpValue->offset < outputEnd){
        level = 0;
    }

    else{
        inpValue->offset -= outputEnd;
    }
    FILE* fp;
    fp = stdout;
    
    TYPE_STRUCT inpType = inpValue->type;

    if(inpType.isArray == 1){
    	fprintf(fp,"%-20s  %-20s  %-4d-%4d  ", inp->key, moduleName, (inpValue->scope)[0], (inpValue->scope)[1]);
        if(inpType.isStatic == 1){
            fprintf(fp,"%-5d  %-7s  %-20s  [%-4d-%4d]\t", inpValue->width + 1, "yes", "Static Array", (inpType.begin), (inpType.end));
            fprintf(fp,"%-10s  %-6d  %-3d", convert_token_lexer(inpType.dtype), inpValue->offset, level);
        }
        else if(inpType.isStatic == 0){
            fprintf(fp,"%-5d  %-7s  %-20s  [%-4s-%4s]\t", inpValue->width + 1, "yes", "Dynamic Array", inpType.begins, inpType.ends);
            fprintf(fp,"%-10s  %-6d  %-3d", convert_token_lexer(inpType.dtype), inpValue->offset, level);
        }
        fprintf(fp,"\n");
    }

}
