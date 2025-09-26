# C-- Compiler

Author: Jenny Yu

## Overview:

This project is a compiler that translates a subset of the C language (C--) into MIPS assembly code.
It is designed as a learning project to demonstrate the main phases of compilation: 
- lexical analysis
- parsing
- semantic analysis
- intermediate code generation
- target code generation

This compiler supports variable declarations, expressions, statements, loops, function calls, etc., producing equivalent MIPS assembly output.

---

## Features

- Lexical Analysis (Tokenizer)
- Recursive Descent Parser
- AST (Abstract Syntax Tree) construction
- Semantic Checking (e.g. type checking, scope validation)
- Code Generation (C --> MIPS Assembly)

---

## Pipeline

1. The global and local symbol tables are built in parser.c. scanner.c is called from parser.c to get tokens from input.
   - Checks if the input is a valid format.
2. parser.c recursively builds the AST (Abstract Syntax Tree) by creating nodes, attaching them together by calling the different methods.
   - Semantic checking is also done to ensure that the input is valid.
3. parser.c traverses the AST and builds three address code as a linked list.
4. parser.c traverses the three address code linked list and generates MIPS code.

  Source Code
     │
     v
  Scanner -----------> Tokens
     │
     v
  Parser ------------> Abstract Syntax Tree (AST)
     │
     v
 Semantic Analysis --> Checked AST + Symbol Table
     │
     v
 Intermediate Code --> Three Address Code (TAC)
     │
     v
 Code Generation ----> MIPS Assembly

(Everything is done in parser.c for now but I do plan to split up the work into different files so it's more organized!!)

---

## To run

- Use the Makefile: type make compiler
- run the executable directly with C code: ./compiler int x;
- or run the executable with a file that contains C code: ./compiler example.txt
  - example.txt: int x; x = 1 + 2 *3;

---

## Example functionalities
- 


---

## Files
- scanner.c / scanner.h --> Gets tokens from the input and returns the types
- parser.c / parser.h --> Main code. Recursive descent parser, builds the AST, TAC, generates MIPS
- AST_node.c / AST_node.h --> Data structure for AST nodes
- ast.c / ast.h --> Defines and returns AST node information
- ast-print.c --> Prints the AST (for debugging)
- symbol_table.c / symbol_table.h --> Defines symbol table and operations
- three_address.c / three_address.h --> Defines data structure and methods for three adress code 
- driver.c --> Entry point of the compiler
- Makefile --> Build the compiler

