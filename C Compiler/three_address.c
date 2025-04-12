#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "three_address.h"
#include "symbol_table.h"
#include "AST_node.h"



struct quad* newTemp(int count) {
    struct quad* newNode = malloc(sizeof(struct quad));
    

    return newNode;
}


struct quad* newInstruction(char* op) {
    struct quad* newNode = malloc(sizeof(struct quad));

    char* opName = strdup(op);
    newNode->op = opName;
    newNode->src1 = NULL;
    newNode->src2 = NULL;
    newNode->dest = NULL;
    newNode->next = NULL;
    
    return newNode;
}


struct operand* newOperand() {
    struct operand* newNode = malloc(sizeof(struct operand));

    newNode->intcon = 0;
    newNode->location = NULL;
    newNode->stmts = NULL;
    
    return newNode;
}


struct label* makeNewLabel() {
    struct label* label = malloc(sizeof(struct label));
    
    label->labelNum = 0;
    
    return label;
}


int getNewLabel(struct label* curLabel) {
    int num = curLabel->labelNum;
    curLabel->labelNum = curLabel->labelNum+1;
    
    return num;
}

