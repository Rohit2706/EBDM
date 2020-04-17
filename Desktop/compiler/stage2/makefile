output: ast.o mappingTable.o lexer.o Hash_table.o stack.c arrayOfLinkedList.c parser.o FunctionTable.o SymbolTable.o stpopulate.o typeextraction.o codegeneration.o driver.o
	gcc -g -o stage1exe ast.o stack.c arrayOfLinkedList.c parser.o mappingTable.o lexer.o Hash_table.o FunctionTable.o SymbolTable.o stpopulate.o typeextraction.o codegeneration.o driver.o
driver.o: driver.c
	gcc -c -g driver.c -I. 
codegeneration.o: codegeneration.c
	gcc -c -g codegeneration.c -I. 
ast.o : ast.c
	gcc -c -g ast.c -I.
typeextraction.o: typeextraction.c
	gcc -c -g typeextraction.c -I. 
stpopulate.o: stpopulate.c
	gcc -c -g stpopulate.c -I. 
FunctionTable.o: FunctionTable.c
	gcc -c -g FunctionTable.c -I.
SymbolTable.o : SymbolTable.c
	gcc -c -g SymbolTable.c -I.
parser.o : stack.c arrayOfLinkedList.c parser.c 
	gcc -c -g stack.c parser.c arrayOfLinkedList.c -I.
mappingTable.o : mappingTable.c
	gcc -c -g mappingTable.c mappingTable.h
lexer.o : lexer.c
	gcc -c -g lexer.c -I.
Hash_table.o : Hash_table.c
	gcc -c -g Hash_table.c
clean:
	rm *.o
	rm *.h.gch
	rm stage1exe