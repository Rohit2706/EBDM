
#include "ast.h"

int isarithmeticOp(tree_node* root){
	switch((root->val).value.t_val){
		case PLUS:
		case MINUS:
		case MUL:
		case DIV:
					return 1;
		default: return 0;
	}
}

int islogicOp(tree_node* root){
	switch((root->val).value.t_val){
		case AND:
		case OR:
					return 1;
		default: return 0;
	}
}

int isrelationalOp(tree_node* root){
	switch((root->val).value.t_val){
		case LT:
		case LE:
		case EQ:
		case NE:
		case GE:
		case GT:
					return 1;
		default: return 0;
	}
}

int compareTypeStruct(TYPE_STRUCT a, TYPE_STRUCT b){
	if(a.dtype != b.dtype)
		return 0;
	if(a.isArray!=b.isArray)
		return 0;
	if(a.isStatic == 0 || b.isStatic == 0)
		return 1;
	if(a.begin!=b.begin)
		return 0;
	if(a.end!=b.end)
		return 0;
	return 1;
}
int checkparams(SYMBOL_TABLE* curr_st, tree_node* root, listNode* list){

	STValue* lookup;
  for(int i=0;i<root->no_child;i++){
    lookup = returnIfPresentST(root->child[i]->lexeme, curr_st, root->child[i]);
    if(lookup == NULL && list!=NULL); 
    else if(lookup==NULL)
    	return -2;
    else if(list==NULL)
      return -2;
    else if(compareTypeStruct(lookup->type, list->type)!=1)
      return -1;
    list = list->next;
  }

  if(list!=NULL)
    return -2;
  return 0;
}

void extractType(tree_node* root, SYMBOL_TABLE* curr_st){

	tree_node* caseStmts;
  TYPE_STRUCT compareType;
  TYPE_STRUCT idType;
  STValue* find;
  tagged_union temp_val;
  FTValue* calledfunc;
	if((root->val).tag==1){

  	switch((root->val).value.t_val){
  		case PLUS:
			case MINUS:
			case MUL:
			case DIV:
  		case AND:
			case OR:
	  	case LT:
			case LE:
			case EQ:
			case NE:
			case GE:
			case GT:
  					if(root->no_leftchild == 1)
    					extractType(root->childLeft[0],curr_st);
    				
  					extractType(root->child[0],curr_st);

    				if(root->no_leftchild != 1){
    					root->type = root->child[0]->type;
    					return;
    				}

    				idType = root->childLeft[0]->type;
    				compareType = root->child[0]->type;

    				if(idType.dtype == EPSILON || compareType.dtype == EPSILON){
    					root->type.dtype = EPSILON;
    					return;
    				}
    				
    				if(idType.dtype != compareType.dtype){
              if(error_flag)
    					printf("Line %d: semantic error - incompatible types for operands\n",root->line_no);
    					return;
    				}

    				if(idType.isArray==1 || compareType.isArray==1){
              if(error_flag)
    					printf("Line %d: semantic error - operations are not allowed on array constructs\n",root->line_no);
    					return;
    				}

    				if(isarithmeticOp(root)){
    					if(idType.dtype == INTEGER || idType.dtype == REAL){
    						root->type = idType;
    						return;
    					}
              if(error_flag)
    					printf("Line %d: semantic error - invalid types for aritmetic operator\n",root->line_no);
    					return;
    				}

    				if(islogicOp(root)){
							if(idType.dtype == BOOLEAN){
    						root->type = idType;
    						return;
    					}
              if(error_flag)
							printf("Line %d: semantic error - invalid types for logical operator\n",root->line_no);
    					return;    					
    				}

    				if(isrelationalOp(root)){
							if(idType.dtype == INTEGER || idType.dtype == REAL){
								idType.dtype = BOOLEAN;
    						(root->type) = idType;
    						return;
    					}
              if(error_flag)
    					printf("Line %d: semantic error - invalid types for relational operator\n",root->line_no);
    					return;				
    				}

    				return; break;

  		case NUM:
  				(root->type).dtype = INTEGER;
  				(root->type).begin = -1;
  				(root->type).end = -1;
  				(root->type).isArray = 0;
  				(root->type).isStatic = 1;
  				return; break;

  		case RNUM:
  				(root->type).dtype = REAL;
  				(root->type).begin = -1;
  				(root->type).end = -1;
  				(root->type).isArray = 0;
  				(root->type).isStatic = 1;

  				return; break;

  		case TRUE:
  		case FALSE:
  				(root->type).dtype = BOOLEAN;
  				(root->type).begin = -1;
  				(root->type).end = -1;
  				(root->type).isArray = 0;
  				(root->type).isStatic = 1;

  				return; break;

  		case ID:
					find = returnIfPresentST(root->lexeme, curr_st, root);
					if(find == NULL)
						return;

					idType = find->type;
					root->type = idType;

					return; break;


			case ARRAY:
					extractType(root->child[0],curr_st);
					extractType(root->child[1],curr_st);
					if((root->child[0]->type).dtype == EPSILON)
						return;

					if((root->child[1]->type).dtype != INTEGER){
            if(error_flag)
						printf("Line %d: semantic error - invalid index type for array\n",root->child[0]->line_no);
						return;					
					}
					root->type = root->child[0]->type;
          if((root->type).isStatic == 1 && (root->child[1]->val).value.t_val == NUM &&
            outOfRange((root->child[1]->value).num_value,(root->type).begin,(root->type).end)==-1){
            if(error_flag)
            printf("Line %d: semantic error - array index out of bounds\n",root->child[0]->line_no);
          }
					(root->type).isArray = 0;
					return; break;

  		case SWITCH:
        	
        	find = returnIfPresentST(root->child[0]->lexeme, curr_st, root->child[0]);
        	caseStmts = root->child[1];
        	if(find != NULL){
        		
	        	idType = (find->type);

	        	if(idType.dtype != INTEGER && idType.dtype != BOOLEAN){
              if(error_flag)
	        		printf("Line %d: semantic error - invalid type for switch\n",root->child[0]->line_no);
	        	}
	        	else{

		        	if(idType.dtype == INTEGER){

		        		for(int i=0;i<caseStmts->no_child;i=i+2){
		          		compareType.dtype = (caseStmts->child[i]->val).value.t_val;

		          		if(compareType.dtype != NUM){
                    if(error_flag)
		          			printf("Line %d: semantic error - type mismatch, expected 'integer' for case\n",caseStmts->child[i]->line_no);
		          			break;
		          		}
		          	}

		          	if((root->child[2]->child[0]->val).value.t_val == EPSILON){
                  if(error_flag)
		          		printf("Line %d: semantic error - expected 'default' statement\n",root->line_no);
                }
		        	}
		        	else{

		        		if(caseStmts->no_child != 4){
                  if(error_flag)
		        			printf("Line %d: semantic error - switch must contain only true and false\n",root->line_no);
                }
		        		else{
		        			if((caseStmts->child[0]->val).value.t_val == TRUE && (caseStmts->child[2]->val).value.t_val == FALSE);
		        			else if((caseStmts->child[0]->val).value.t_val == FALSE && (caseStmts->child[2]->val).value.t_val == TRUE);
		        			else{
                    if(error_flag)
		        				printf("Line %d: semantic error - type mismatch, expected 'true' && 'false' cases\n",root->line_no);
                  }
		        		}

		        		if((root->child[2]->child[0]->val).value.t_val != EPSILON){
                  if(error_flag)
		          		printf("Line %d: semantic error - switch for 'boolean' cannot contain 'default' statement\n",root->line_no);	
                }
		          }
		        }
		      }

	        for(int i=1;i<caseStmts->no_child;i=i+2)
	        	extractType(caseStmts->child[i], root->stptr);

	        if((root->child[2]->child[0]->val).value.t_val != EPSILON)
	        	extractType(root->child[2]->child[0], root->stptr);
	        return;	break;

	    case FOR:
	    		
	    		find = returnIfPresentST(root->child[0]->lexeme, curr_st, root->child[0]);
	    		if(find != NULL){
	    			idType = (find->type);
	    			if(idType.dtype != INTEGER){
              if(error_flag)
	    				printf("Line %d: semantic error - type mismatch, expected 'integer' in 'for'\n",root->child[0]->line_no);
            }
	    			if((root->child[1]->child[0]->value).num_value>=(root->child[1]->child[1]->value).num_value){
              if(error_flag)
	    				printf("Line %d: semantic error - invalid range in 'for'\n",root->child[1]->child[0]->line_no);
            }
	    		}

					extractType(root->child[2], root->stptr);	    
					
					return;	break;

			case WHILE:

					extractType(root->child[0], root->stptr);

	    		idType = root->child[0]->type;
	    		if(idType.dtype != BOOLEAN && idType.dtype != EPSILON){
            if(error_flag)
	    				printf("Line %d: semantic error - type mismatch, expected 'boolean' expression in 'while'\n",root->line_no);
	    		}
	    		extractType(root->child[1], root->stptr);
						    
					return;	break;
    }
  }

  tree_node* temp_expr;
	switch((root->val).value.nt_val){
		
		case DRIVERMODULE:	
					extractType(root->child[0]->child[0], root->stptr);
					return; break;

		case MODULE_NT:
					if(root->stptr !=NULL)
						extractType(root->child[3]->child[0], root->stptr);
					return; break;

		case ARMORBOOL:
		case EXPRESSION:

    				if(root->no_leftchild == 1)
    					extractType(root->childLeft[0],curr_st);
    				
  					extractType(root->child[0],curr_st);

    				if(root->no_leftchild != 1){
    					root->type = root->child[0]->type;
    					return;
    				}

    				idType = root->childLeft[0]->type;
    				compareType = root->child[0]->type;

    				if(idType.dtype == EPSILON || compareType.dtype == EPSILON){
    					root->type.dtype = EPSILON;
    					return;
    				}
    				
    				if(idType.dtype != compareType.dtype){
              if(error_flag)
    					printf("Line %d: semantic error - incompatible types for operands\n",root->line_no);
    					return;
    				}

    				if(isarithmeticOp(root)){
    					if(idType.dtype == INTEGER || idType.dtype == REAL){
    						root->type = idType;
    						return;
    					}
              if(error_flag)
    					printf("Line %d: semantic error - invalid types for aritmetic operator\n",root->line_no);
    					return;
    				}

    				if(islogicOp(root)){
							if(idType.dtype == BOOLEAN){
    						root->type = idType;
    						return;
    					}
              if(error_flag)
							printf("Line %d: semantic error - invalid types for logical operator\n",root->line_no);
    					return;    					
    				}

    				if(isrelationalOp(root)){
							if(idType.dtype == INTEGER || idType.dtype == REAL){
								idType.dtype = BOOLEAN;
    						(root->type) = idType;
    						return;
    					}
              if(error_flag)
    					printf("Line %d: semantic error - invalid types for relational operator\n",root->line_no);
    					return;				
    				}

    				return; break;

    case MODULEDECLARATIONS:
    case IOSTMT:
    case DECLARESTMT:	return; break;

    case MODULEREUSESTMT:

    			calledfunc = get_ftvalue(ft, root->child[1]->lexeme);

    			switch(checkparams(curr_st, root->child[0]->child[0], calledfunc->outputList)){
    				case -1:	if(error_flag)
                      printf("Line %d: semantic error - expected and returned argument types do not match\n", root->child[1]->line_no);
    									return; break;
    				case -2:	if(error_flag)
                      printf("Line %d: semantic error - expected and returned argument numbers do not match\n", root->child[1]->line_no);
    									return; break;
    				default:	break;
          	
        	}
      		
      		switch(checkparams(curr_st, root->child[2], calledfunc->inputList)){
    				case -1:	if(error_flag)
                      printf("Line %d: semantic error - expected and passed argument types do not match\n", root->child[1]->line_no);
    									return; break;
    				case -2:	if(error_flag)
                      printf("Line %d: semantic error - expected and passed argument numbers do not match\n", root->child[1]->line_no);
    									return; break;
    				default:	break;
          	
        	}

        	return; break;

    case ASSIGNMENTSTMT:
    			extractType(root->child[0], curr_st);
    			if(root->no_child == 4){
            extractType(root->child[1], curr_st);

            if((root->child[1]->type).dtype != INTEGER){
              if(error_flag)
              printf("Line %d: semantic error - invalid index type for array\n",root->child[0]->line_no);
              return;         
            }
            if((root->child[0]->type).isStatic == 1 && outOfRange((root->child[1]->value).num_value,(root->child[0]->type).begin,(root->child[0]->type).end)==-1){
                if(error_flag)
                printf("Line %d: semantic error - array index out of bounds\n",root->child[0]->line_no);
            }
            
    				(root->child[0]->type).isArray = 0;
          }
    			extractType(root->child[root->no_child-1], curr_st);
    			idType = root->child[0]->type;
    			compareType = root->child[root->no_child-1]->type;

    			if(idType.dtype == EPSILON || compareType.dtype == EPSILON){
  					root->type.dtype = EPSILON;
  					return;
  				}
  				
  				if(idType.dtype != compareType.dtype){
            if(error_flag)
  					printf("Line %d: semantic error - incompatible types for assignment\n",root->child[0]->line_no);
  					return;
  				}

  				if(idType.isArray==1){
  					if(compareType.isArray!=1){
              if(error_flag)
  						printf("Line %d: semantic error - incompatible types for assignment\n",root->child[0]->line_no);
  						return;
  					}
  					if(idType.isStatic==0 || compareType.isStatic==0);
  					else if((idType.begin!=compareType.begin) || (compareType.end != idType.end)){
              if(error_flag)
  							printf("Line %d: semantic error - incompatible array types for assignment\n",root->child[0]->line_no);
  							return;
  					}
  				}
  					return; break;

    default:
    		if((root->child[0]->val).value.t_val==EPSILON)
          return;

        for(int i=0;i<root->no_child;i++)
          extractType(root->child[i], curr_st);

        return; break;				
	}
}