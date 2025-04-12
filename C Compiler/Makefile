.PHONY: clean

compile : scanner.o driver.o parser.o symbol_table.o AST_node.o ast.o ast-print.o three_address.o
	gcc -g -Wall scanner.o driver.o parser.o symbol_table.o AST_node.o ast.o ast-print.o three_address.o -o compile

parser.o : parser.c parser.h scanner.h symbol_table.h AST_node.h three_address.h
	gcc -g -Wall -c parser.c

scanner.o : scanner.c scanner.h
	gcc -g -Wall -c scanner.c

driver.o : driver.c
	gcc -g -Wall -c driver.c

symbol_table.o : symbol_table.c symbol_table.h
	gcc -g -Wall -c symbol_table.c 

AST_node.o : AST_node.c AST_node.h
	gcc -g -Wall -c AST_node.c

ast.o : ast.c ast.h AST_node.h symbol_table.h
	gcc -g -Wall -c ast.c

ast-print.o : ast-print.c ast.h
	gcc -g -Wall -c ast-print.c

three_address.o : three_address.c three_address.h symbol_table.h AST_node.h
	gcc -g -Wall -c three_address.c

clean :
	rm -rf compile
	rm -rf *.o