# C-- Compiler

Author: Jenny Yu

## Overview:

The compiler can take a subset of C code and convert it into MIPS assembly code. 

## Features

- Lexical Analysis (Tokenizer)
- Recursive Descent Parser
- AST (Abstract Syntax Tree) construction
- Semantic Checking (e.g. type checking, scope validation)
- Code Generation (C --> MIPS Assembly)

## To run

- Use the Makefile: type make compiler
- run the executable directly with C code: ./compiler int x;
- or run the executable with a file that contains C code: ./compiler example.txt
  - example.txt: int x; x = 1 + 2 *3;
