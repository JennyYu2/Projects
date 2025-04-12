#ifndef __AST_NODE__
#define __AST_NODE__

#include "ast.h"
#include "three_address.h"


struct node {
    char* name;
    NodeType type;
    int numParams;
    int val;
    struct node* stmts;
    struct node* childOne;
    struct node* childTwo;
    struct node* childThree;
    struct node* next;
    struct table* location;
    struct quad* threeAddr;
};

struct param {
    struct table* nodeParam;
    int val;
    struct param* next;
};


struct node* makeEmptyIntcon(int val, NodeType addType);
struct node* makeEmptyNode(char* addName, NodeType addType);
void addEmptyFuncDef(char* addName, NodeType addType, struct node* root);
struct node* makeEmptyParam(NodeType addType);

#endif