#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "symbol_table.h"


void addVariable(char* var, char* varType, struct table** curStack) {
    int i; 

    // Make new table
    struct table* newVariable = malloc(sizeof(struct table));
    newVariable->name = NULL;
    newVariable->nextTable = NULL;
    newVariable->type = NULL;
    newVariable->params = 0;
    newVariable->mips = 0;

    // Copy the name
    char* addVar = malloc(sizeof(char)*strlen(var)+1);
    for(i = 0; var[i] != '\0'; i++) {
        addVar[i] = var[i];
    }
    addVar[i] = '\0';
    newVariable->name = addVar;

    // Copy the type
    char* addType = malloc(sizeof(char)*strlen(varType)+1);
    for(i = 0; varType[i] != '\0'; i++) {
        addType[i] = varType[i];
    }
    addType[i] = '\0';
    newVariable->type = addType;

    // Add new table to the back of the list of tables
    struct table* cur = *curStack;
    if(*curStack == NULL) {
        *curStack = newVariable;
    }
    else {
        while(cur->nextTable != NULL) {
            cur = cur->nextTable;
        }
        cur->nextTable = newVariable;
    }   
}


int checkForVariable(char* var, struct stack* curStack) {
    struct table* searchVar = curStack->symbolTables;

    while(searchVar != NULL) {
        // Variable was found
        if(strcmp(var, searchVar->name) == 0) {
            return 1;
        }
        searchVar = searchVar->nextTable;
    }
    return 0;
}


int findVariable(char* var, struct stack* curStack) {
    struct table* searchVar = curStack->symbolTables;

    while(searchVar != NULL) {
        // Variable was found
        if(strcmp(var, searchVar->name) == 0 && strcmp("int", searchVar->type) == 0) {
            return 1;
        }
        searchVar = searchVar->nextTable;
    }
    return 0;
}


int checkForFunction(char* func, struct stack* curStack) {
    struct table* searchVar = curStack->symbolTables;
    
    while(searchVar != NULL) {
        // Variable was found
        if(strcmp(func, searchVar->name) == 0 && strcmp("func", searchVar->type) == 0) {
            return 1;
        }
        searchVar = searchVar->nextTable;
    }
    return 0;
}


int checkType(char* func, struct stack* curStack) {
    struct table* searchVar = curStack->symbolTables;
    
    while(searchVar != NULL) {
        // Variable was found
        if(strcmp(func, searchVar->name) == 0 && strcmp("int", searchVar->type) == 0) {
            return 1;
        }
        searchVar = searchVar->nextTable;
    }
    return 0;
}


void addFuncCount(char* func, int count, struct stack* curStack) {
    struct table* searchVar = curStack->symbolTables;

    while(searchVar != NULL) {
        // Variable was found
        if(strcmp(func, searchVar->name) == 0) {
            searchVar->params = count;
            return;
        }
        searchVar = searchVar->nextTable;
    }
}


int getCount(char* func, struct stack* curStack) {
    struct table* searchVar = curStack->symbolTables;

    while(searchVar != NULL) {
        // Variable was found
        if(strcmp(func, searchVar->name) == 0) {
            return searchVar->params;
        }
        searchVar = searchVar->nextTable;
    }

    return 0;
}


struct table* getTableEntry(char* name, struct stack* curStack) {
    struct table* searchVar = curStack->symbolTables;

    while(searchVar != NULL) {
        // Variable was found
        if(strcmp(name, searchVar->name) == 0) {
            return searchVar;
        }
        searchVar = searchVar->nextTable;
    }

    return NULL;
}


/*
 * Free the variables in the given stack
*/
void popVariable(struct stack* curStack) {
    struct table* tableOne = curStack->symbolTables;
    struct table* tableTwo;

    while(tableOne != NULL) {
        tableTwo = tableOne->nextTable;
        free(tableOne);
        tableOne = tableTwo;
    }
    curStack->symbolTables = NULL;
}




