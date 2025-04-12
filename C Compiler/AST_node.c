#include <stdlib.h>
#include <string.h>
#include "AST_node.h"


struct node* makeEmptyIntcon(int val, NodeType addType) {
    // Make new node
    struct node* newNode = malloc(sizeof(struct node));
    newNode->name = NULL;
    newNode->numParams = 0;
    newNode->type = addType;
    newNode->val = val; 
    newNode->stmts = NULL;
    newNode->location = NULL;
    newNode->childOne = NULL;
    newNode->childTwo = NULL;
    newNode->childThree = NULL;
    newNode->next = NULL;
    newNode->threeAddr = NULL;
    return newNode;

}


struct node* makeEmptyNode(char* addName, NodeType addType) {
    int i; 

    // Make new node
    struct node* newNode = malloc(sizeof(struct node));
    newNode->name = NULL;
    newNode->numParams = 0;
    newNode->type = addType;
    newNode->val = 0; 
    newNode->stmts = NULL;
    newNode->location = NULL;
    newNode->childOne = NULL;
    newNode->childTwo = NULL;
    newNode->childThree = NULL;
    newNode->next = NULL;
    newNode->threeAddr = NULL;

    // Copy the name
    char* getName = malloc(sizeof(char)*strlen(addName)+1);
    for(i = 0; addName[i] != '\0'; i++) {
        getName[i] = addName[i];
    }
    getName[i] = '\0';
    newNode->name = getName;
    
    newNode->type = addType;

    return newNode;
}


struct node* makeEmptyParam(NodeType addType) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode->name = NULL;
    newNode->numParams = 0;
    newNode->type = 0;
    newNode->val = 0; 
    newNode->stmts = NULL;
    newNode->location = NULL;
    newNode->childOne = NULL;
    newNode->childTwo = NULL;
    newNode->childThree = NULL;
    newNode->next = NULL;
    newNode->threeAddr = NULL;

    newNode->type = addType;
    return newNode;
}


void addEmptyFuncDef(char* addName, NodeType addType, struct node* root) {
    int i; 

    // Make new node
    struct node* newNode = malloc(sizeof(struct node));
    newNode->name = NULL;
    newNode->numParams = 0;
    newNode->type = 0;
    newNode->val = 0; 
    newNode->stmts = NULL;
    newNode->location = NULL;
    newNode->childOne = NULL;
    newNode->childTwo = NULL;
    newNode->childThree = NULL;
    newNode->next = NULL;
    newNode->threeAddr = NULL;

    // Copy the name
    char* getName = malloc(sizeof(char)*strlen(addName)+1);
    for(i = 0; addName[i] != '\0'; i++) {
        getName[i] = addName[i];
    }
    getName[i] = '\0';
    newNode->name = getName;

    newNode->type = addType;

    root = newNode;
}
