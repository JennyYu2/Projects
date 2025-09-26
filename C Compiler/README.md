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

(Everything is done in parser.c for now but I do plan to split up the work into different files so it's more organized T-T)

---

## To run

- Use the Makefile: type make compiler
- run the executable directly with C code: ./compiler int x;
- or run the executable with a file that contains C code: ./compiler example.txt
  - example.txt: int x; x = 1 + 2 *3;

---

## Examples


---

## Files

