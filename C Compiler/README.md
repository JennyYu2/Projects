# C-- Compiler

### Author: Jenny Yu *April 2024*

---
## Jump to:

[Overview](#overview) <br>
[Features](#features) <br>
[Pipeline](#pipeline) <br>
[Build and run](#build-and-run) <br>
[Examples](#examples) <br>
[Files](#files)

--- 

## Overview:

This project is a compiler that translates a subset of the C language (C--) into MIPS assembly code.
It is designed as a learning project to demonstrate the main phases of compilation:  
- Lexical analysis  
- Parsing  
- Semantic analysis  
- Intermediate code generation  
- Target code generation  
<br>

**Currently supports:** 
- Variable declarations  
- Expressions  
- Statements  
- Loops  
- Function calls

---

## Features

- **Lexical Analysis (Tokenizer)**: converts characters into tokens  
- **Recursive Descent Parser**: parses tokens into an AST  
- **AST (Abstract Syntax Tree)**: construction and traversal  
- **Semantic Checking**: type checking, scope validation  
- **Intermediate Code Generation**: Three Address Code (TAC)  
- **Target Code Generation**: MIPS assembly  

---

## Pipeline

1. **Lexical Analysis**: `scanner.c` tokenizes the input.  
2. **Parsing**:  `parser.c` recursively builds the **AST**.  
3. **Semantic Analysis**: symbol tables (global & local) are built, and type/scope checks are performed.  
4. **Intermediate Code Generation**: the AST is traversed to produce **Three Address Code** as a linked list.  
5. **Target Code Generation**: TAC is traversed and translated into **MIPS assembly**.

``` 
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
```

(Everything is done in parser.c for now but I do plan to split up the work into different files so it's more organized!!)

---

## Build and run

### 0. Setup:
Clone this repository or download all files

### 1. To build:
``` 
make compile
```

### 2. Run it directly from command line:
```
./compile int x;
```

### 3. Run it with a file:
```
./compile example.txt
```

```
example.txt

int x;
x = 1 + 2 * 3;
```
  
### 4. Run with options:

- --chk_decl: enable semantic checking

- --print_ast: print the AST

- --gen_code: generate MIPS code

Example:
``` 
./compile --chk_decl --print_ast --gen_code int x;
```
Output:
```
x

sw   $t0, x
```

---

## Examples

- Input: 

---

## Files
- `scanner.c` / `scanner.h` --> Gets tokens from the input and returns the types
- `parser.c` / `parser.h` --> Main code. Recursive descent parser, builds the AST, TAC, generates MIPS
- `AST_node.c` / `AST_node.h` --> Data structure for AST nodes
- `ast.c` / `ast.h` --> Defines and returns AST node information
- `ast-print.c` --> Prints the AST (for debugging)
- `symbol_table.c` / `symbol_table.h` --> Defines symbol table and operations
- `three_address.c` / `three_address.h` --> Defines data structure and methods for three adress code 
- `driver.c` --> Entry point of the compiler
- `Makefile` --> Build the compiler









