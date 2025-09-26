# C-- Compiler

Author: Jenny Yu

## Overview:

This project is a compiler that translates a subset of the C language (C--) into MIPS assembly code.
It is designed as a learning project to demonstrate the main phases of compilation: lexical analysis, parsing, semantic analysis, intermediate code generation, and target code generation.

The compiler supports variable declarations, expressions, and statements, producing equivalent MIPS assembly output.

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

