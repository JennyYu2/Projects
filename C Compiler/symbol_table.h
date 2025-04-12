#ifndef __SYMBOL_TABLE__
#define __SYMBOL_TABLE__


struct stack {
    struct table* symbolTables;
    struct stack* up;
    struct stack* down;
};

struct table {
    char* name;
    char* type;
    int params;
    int mips;
    struct table* nextTable;
};


void addVariable(char* var, char* varType, struct table** curStack);
int checkForVariable(char* var, struct stack* curStack);
int findVariable(char* var, struct stack* curStack);
int checkForFunction(char* func, struct stack* curStack);
void popVariable(struct stack* curStack);
int checkType(char* func, struct stack* curStack);
void addFuncCount(char* func, int count, struct stack* curStack);
struct table* getTableEntry(char* name, struct stack* curStack);
int getCount(char* func, struct stack* curStack);


#endif