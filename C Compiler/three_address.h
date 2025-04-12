#ifndef __THREE_ADDRESS__
#define __THREE_ADDRESS__

#include "ast.h"
#include "symbol_table.h"


struct operand {
    int intcon;
    struct table* location;
    struct node* stmts;
};

struct quad {
    char* op;
    struct operand* src1;
    struct operand* src2;
    struct operand* dest;
    struct quad* next;
};


struct label {
    int labelNum;
};


struct quad* newTemp(int count);
struct quad* newInstruction(char* op);
struct operand* newOperand();
struct label* makeNewLabel();
int getNewLabel(struct label* curLabel);

#endif