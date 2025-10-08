# C-- Compiler

<div align="center">  
  <img src="C--%20Compiler/images/C.png" alt="C logo" width="250" height="276">
</div>

### Author: Jenny Yu 
*April 2024*

---

## Table of Contents

- [Overview](#overview) <br>
- [Features](#features) <br>
- [Pipeline](#pipeline) <br>
- [Build and run](#build-and-run) <br>
- [Examples](#examples) <br>
- [Files](#files)

--- 

## Overview
[Back to top](#table-of-contents)

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
[Back to top](#table-of-contents)

- **Lexical Analysis (Tokenizer)**: converts characters into tokens  
- **Recursive Descent Parser**: parses tokens into an AST  
- **AST (Abstract Syntax Tree)**: construction and traversal  
- **Semantic Checking**: type checking, scope validation  
- **Intermediate Code Generation**: Three Address Code (TAC)  
- **Target Code Generation**: MIPS assembly  

---

## Pipeline
[Back to top](#table-of-contents)

1. **Lexical Analysis**: `scanner.c` tokenizes the input.  
2. **Parsing**:  `parser.c` recursively builds the **AST**.  
3. **Semantic Analysis**: symbol tables (global & local) are built, and type/scope checks are performed.  
4. **Intermediate Code Generation**: the AST is traversed to produce **Three Address Code** as a linked list.  
5. **Target Code Generation**: TAC is traversed and translated into **MIPS assembly**.

``` 
Source Code → Scanner → Tokens → Parser → AST → Semantic Analysis → TAC → MIPS
```

(Everything is done in parser.c for now but I do plan to split up the work into different files so it's more organized!!)

---

## Build and run
[Back to top](#table-of-contents)

### 0. Setup:
- Must have C installed
- Clone this repository or download all files

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
a. ./compile --chk_decl --gen_code int x;

b. ./compile --print_ast int y;
```

Output:
```
a. 
sw   $t0, x

b.
y
```

---

## Examples
[Back to top](#table-of-contents)

<details>
<summary><h3>Expressions</h3></summary>
	
i. Expressions containing multiple occurrences of an operator

**Input:**
```c
int u, v, w;

int main() {
    int x, y, z;

    x = 1; y = 2; z = 3; u = 4; w = 10;

    v = x + y + z + u;
    println(v);

    v = x - y - z - u;
    println(v);

    v = x * y * z * u;
    println(v);

    v = w / y / z / x;
    println(v);

    v = - - -w;
    println(v);
}
```

**Output:**
```
Output code here
```
</details>

<details>
<summary><h3>Function calls</h3></summary>

i. expressions containing function calls

**Input:**
```c
int x, y, z;

int one() { z = 1; }

int two() { z = 2; }

int add(int x, int y) { z = x + y; }

int sub(int x, int y) { z = x - y; }

int main() {
    int u, v;

    one();
    println(z);
    
    two();
    println(z);

    x = 1;
    y = 2;
    add(x, y );
    println(z);
    
    sub(x, y);
    println(z);

}
```

**Output:**
```
Output code here
```

ii. IF statements containing function calls

**Input:**
```c
int f(int x) { return -1+x+3; }
int g(int x) { return x+2; }
int h(int x, int y) { return x*2 + y*3; }

int main() {
    int x, y;

    x = 1;
    y = 2;

    if (f(g(y)) == g(f(x)))
        println(4);
    else
        println(7);

    if ( h(x, y) < h(y, x) )
        println(19);
    else
        println(23);
}
```

**Output:**
```
Output code here
```
</details>

<details>
<summary><h3>Loops</h3></summary>

i. WHILE loop

**Input:**
```c
int x;

int increment(int n) {
    x = x + n;
    println(x);
    return x;
}

int main() {
    x = 5;
    while (x == 0 && increment(-1) != 0 || increment(-1) != 0) {
        println(x);
    }
}
```

**Output:**
```
Output here
```
</details>

<details>
<summary><h3>Return statements</h3></summary>

i. RETURN statements containing several different operators

**Input:**
```c
int f1(int x, int y, int z, int w) {
    return x + y + z + w;
}

int f2(int x, int y, int z, int w) {
    return x - y * z / w;
}

int f3(int x, int y, int z, int w) {
    return x * z / y + w;
}

int f4(int x, int y, int z, int w) {
    return x / y + z - w;
}

int f5(int x, int y, int z, int w) {
    return -x + -y - -z * -w;
}

int main() {
    int x;

    x = f1(2,3,4,5);
    println(x);

    x = f2(2,3,4,5);
    println(x);

    x = f3(2,3,4,5);
    println(x);

    x = f4(8,2,3,1);
    println(x);

    x = f5(1,2,3,4);
    println(x);

}
```

**Output:**
```
Output here
```
</details>

<details>
<summary><h3>Recursion</h3></summary>

i. Recursive functions

**Input:**
```c
int factorial(int n) {
    if (n <= 0) {
        return 1;
    }
    else {
        return n * factorial(n-1);
    }
}

int fib(int n) {
    if (n <= 0) {
        return 1;
    }
    else {
        return fib(n-1) + fib(n-2);
    }
}

int main() {
    int n;
    int i, x;

    n = 7;
    
    i = 0;
    while (i <= n) {
        x = factorial(i);
	println(x);
	i = i + 1;
    }

    i = 0;
    while (i <= n) {
        x = fib(i);
	println(x);
	i = i + 1;
    }
}
```

**Output:**
```
Output here
```
</details>

---

## Files
[Back to top](#table-of-contents)

- `scanner.c` / `scanner.h` --> Gets tokens from the input and returns the types
- `parser.c` / `parser.h` --> Main code. Recursive descent parser, builds the AST, TAC, generates MIPS
- `AST_node.c` / `AST_node.h` --> Data structure for AST nodes
- `ast.c` / `ast.h` --> Defines and returns AST node information
- `ast-print.c` --> Prints the AST (for debugging)
- `symbol_table.c` / `symbol_table.h` --> Defines symbol table and operations
- `three_address.c` / `three_address.h` --> Defines data structure and methods for three adress code 
- `driver.c` --> Entry point of the compiler
- `Makefile` --> Build the compiler

