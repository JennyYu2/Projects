#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"
#include "symbol_table.h"
#include "parser.h"
#include "AST_node.h"
#include "three_address.h"


extern int get_token();
extern int line;
extern int chk_decl_flag;
extern int print_ast_flag;
extern int gen_code_flag;
int cur_token;

struct stack* cur_table = NULL;
struct stack* local_table;

extern char* lexeme;
char* cur_variable;
int vars = 0;
int count_formals = 0;
char* save_var;
char* save_call;

struct node* root;
struct node* curNode;
struct label* newLabel;
int stmt_list = 0;
int cur_const;
int matchedINTCON;
int count = 0;

//struct quad* linkedList = NULL;
//struct quad* ifStmtList = NULL;


void checkInTable() {
    // Check if already in the table
    int errorVal = checkForVariable(cur_variable, cur_table);

    if(chk_decl_flag == 1) {
        if(errorVal == 1) {
            fprintf(stderr, "7 ERROR on LINE %d, sixth exit status = 1\n", line);
            exit(1);
        }
        else {
            addVariable(cur_variable, "int", &cur_table->symbolTables);
        }
    }
    
    else {
        // Put the variable in the table
        addVariable(cur_variable, "int", &cur_table->symbolTables);
    }
}


/* 
 * Params: expected - Token
 * 
 * Takes in the expected Token and if the 
 * cur_token matches the expected Token, get the
 * next token. 
 * If not, print error and exit.
*/
void match(Token expected) {
    if(cur_token == expected) {
        if(cur_token == ID) {
            cur_variable = lexeme;
        }

        if(cur_token == INTCON) {
            char* temp = lexeme;
            cur_const = atoi(temp);
        }

        cur_token = get_token();
    }

    else {
        //printf("ERROR on LINE %d, exit status = 1\n", line);
        fprintf(stderr, "%s ERROR on LINE %d when it should be %d, exit status = 1\n", lexeme, line, expected);
        exit(1);
    }
}


void type() {
    match(kwINT);
}


void id_check() {
    if(cur_token == COMMA) {
        vars = 1;
        checkInTable();
        match(COMMA);
        id_list();
    }

    else {
        return;
    }
}


void id_list() {
    match(ID);
    id_check();   
}


void var_decl() {
    type();
    id_list();
    checkInTable();
    match(SEMI);
}


void more_formals() {
    if(cur_token == COMMA) {
        match(COMMA);
        formals();
    }

    else {
        return;
    }
}


void formals() {
    type();
    match(ID);

    // Check if already in the table
    int errorVal = checkForVariable(cur_variable, cur_table);

    if(chk_decl_flag == 1) {
        if(errorVal == 1) {
            fprintf(stderr, "ERROR on LINE %d, formals exit status = 1\n", line);
            exit(1);
        }
    }

    // Put the variable in the table
    count_formals++;
    addVariable(cur_variable, "int", &cur_table->symbolTables); // Add to symbol table
    struct table* tableEntry = getTableEntry(cur_variable, cur_table);
    struct node* newParam = makeEmptyParam(IDENTIFIER); // New param
    newParam->location = tableEntry;

    if(curNode->stmts == NULL) {
        curNode->stmts = newParam;
    }
    else {
        struct node* temp = curNode->stmts;
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newParam;
    }
    
    more_formals();
}


void opt_var_decls() {
    if(cur_token == kwINT) {
        var_decl();
        vars = 0;
        opt_var_decls();
    }

    else {
        return;
    }
}


void opt_formals() {
    if(cur_token == kwINT) {
        formals();
    }
    
    else {
        return;
    }
}


void addToLocalStmtList() {
    struct table* getTable = getTableEntry(cur_variable, cur_table);
    struct node* start = makeEmptyParam(EXPR_LIST); // Make new expr_list node
    struct node* newParam = makeEmptyNode(cur_variable, IDENTIFIER); // New param
    newParam->location = getTable;
    start->childOne = newParam;

    if(curNode->stmts == NULL) {
        curNode->stmts = start;
    }
            
    else {
        struct node* temp = curNode->stmts;
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = start;
    }
}


void addToGlobalStmtList() {
    struct table* getTable = getTableEntry(cur_variable, cur_table->up);
    struct node* start = makeEmptyParam(EXPR_LIST); // Make new expr_list node
    struct node* newParam = makeEmptyNode(cur_variable, IDENTIFIER); // New param
    newParam->location = getTable;
    start->childOne = newParam;

    if(curNode->stmts == NULL) {
        curNode->stmts = start;
    }
            
    else {
        struct node* temp = curNode->stmts;
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = start;
    }
}


void addIntConst() {
    struct node* start = makeEmptyParam(EXPR_LIST); // Make new expr_list node
    struct node* newParam = makeEmptyParam(INTCONST); // New param
    newParam->val = cur_const;
    start->childOne = newParam;

    if(curNode->stmts == NULL) {
        curNode->stmts = start;
    }

    else {
        struct node* temp = curNode->stmts;
        while(temp->next != NULL) {
            temp = temp->next;
        }
                
        temp->next = start;
    }
}



int countFuncCallParams(struct node* params) {
    struct node* temp = params;
    int count = 0;

    while(temp != NULL) {
        count++;
        temp = temp->next;
    }

    return count;
}


struct node* fn_call_or_id() {
    // fn_call
    if(cur_token == LPAREN) {
        stmt_list = 1; // Needs the list of params
        char* save_call;
        struct node* newFnCall = makeEmptyNode(cur_variable, FUNC_CALL);
        curNode = newFnCall;
        save_call = strdup(cur_variable);

        int localVal = checkForVariable(cur_variable, cur_table);
        int globalVal = checkForVariable(cur_variable, cur_table->up);

        if(chk_decl_flag == 1) {
            if(globalVal == 0) {
                fprintf(stderr, "ERROR on LINE %d, fn_call_or_id1 exit status = 1\n", line);
                exit(1);
            }
            else if(localVal == 1) {
                fprintf(stderr, "ERROR on LINE %d, fn_call_or_id2 exit status = 1\n", line);
                exit(1);
            }
        }
        struct table* getTable = getTableEntry(save_call, cur_table->up);
        newFnCall->location = getTable;

        match(LPAREN);
        count_formals = 0;
        struct node* params = opt_expr_list(); // Making expr_list

        int numParams = countFuncCallParams(params);

        struct node* paramsList = makeParamExprList(params);
        newFnCall->childOne = paramsList;

        if(chk_decl_flag == 1) {
            int count = getCount(save_call, cur_table->up);
            if(globalVal == 1 &&  count != numParams) {
                fprintf(stderr, "ERROR on LINE %d, fn_call_or_id3 exit status = 1\n", line);
                exit(1);
            }
        }
        newFnCall->numParams = count_formals;

        match(RPAREN);
        return newFnCall;
    }

    else {
        struct node* newAssg = makeEmptyNode(cur_variable, IDENTIFIER);

        int localVal = checkForVariable(cur_variable, cur_table);
        int globalVal = checkForVariable(cur_variable, cur_table->up);
        int localType = checkType(cur_variable, cur_table);
        int globalType = checkType(cur_variable, cur_table->up);
       
        if(chk_decl_flag == 1) {
            // Variable not in the table
            if(globalVal == 0 && localVal == 0) {
                fprintf(stderr, "ERROR on LINE %d, fn_call_or_id1 exit status = 1\n", line);
                exit(1);
            }
            // Variable is not type bool
            else if(localType == 0 && globalType == 0) {
                fprintf(stderr, "ERROR on LINE %d, fn_call_or_id2 exit status = 1\n", line);
                exit(1);
            }
        }

        struct table* getTable = NULL;
        if(localVal == 1) {
            getTable = getTableEntry(cur_variable, cur_table);
        }
        else {
            getTable = getTableEntry(cur_variable, cur_table->up);
        }
        newAssg->location = getTable;

        return newAssg;
    }

}


struct node* arith_op() {
    if(cur_token == opSUB) {
        match(opSUB);
        struct node* newNode = makeEmptyNode("sub", SUB);
        return newNode;
    }

    else if(cur_token == opADD) {
        match(opADD);
        struct node* newNode = makeEmptyNode("add", ADD);
        return newNode;
    }

    else if(cur_token == opMUL) {
        match(opMUL);
        struct node* newNode = makeEmptyNode("mul", MUL);
        return newNode;
    }

    else if(cur_token == opDIV) {
        match(opDIV);
        struct node* newNode = makeEmptyNode("div", DIV);
        return newNode;
    }

    return NULL;
}


struct node* arith_exp3() {
    struct node* newNode = NULL;

    if(cur_token == ID) {
        match(ID);
        count_formals++;

        newNode = fn_call_or_id();
    }

    else if(cur_token == INTCON) {
        match(INTCON);
        newNode = makeEmptyIntcon(cur_const, INTCONST);
        matchedINTCON = 1;
        
        if(stmt_list == 1) {
            addIntConst();
        }
        count_formals++;
    }

    else if(cur_token == LPAREN) {
        match(LPAREN);
        newNode = arith_exp();
        match(RPAREN);
    }

    else {
        match(opSUB);
        newNode = makeEmptyNode("uminus", UMINUS);
        struct node* body = arith_exp3();

        newNode->childOne = body;
    }

    return newNode;
}


struct node* mul_or_div(struct node* leftTree) {
    if(cur_token == opMUL || cur_token == opDIV) {
        struct node* opNode = arith_op();
        opNode->childOne = leftTree;

        struct node* rightTree = arith_exp3();
        opNode->childTwo = rightTree; 
        
        struct node* newNode = mul_or_div(opNode);

        return newNode;
    }
    else {
        return leftTree;
    }
}


struct node* add_or_sub(struct node* leftTree) {
    if(cur_token == opADD || cur_token == opSUB) {
        struct node* opNode = arith_op();
        opNode->childOne = leftTree;

        struct node* rightTree = arith_exp2();
        opNode->childTwo = rightTree;

        struct node* newNode = add_or_sub(opNode);

        return newNode;
    }
    else {
        return leftTree;
    }
}


struct node* arith_exp2() {
    struct node* newNode = arith_exp3();
    struct node* opNode = mul_or_div(newNode);

    return opNode;
}


struct node* arith_exp() {
    struct node* newNode = arith_exp2();
    struct node* opNode = add_or_sub(newNode);

    return opNode;
}


struct node* logical_op() {
    if(cur_token == opAND) {
        match(opAND);
        struct node* newNode = makeEmptyNode("and", AND);
        return newNode;
    }

    else if(cur_token == opOR) {
        match(opOR);
        struct node* newNode = makeEmptyNode("or", OR);
        return newNode;
    }

    return NULL;
}


struct node* more_expr_list() {
    if(cur_token == COMMA) {
        match(COMMA);
        struct node* newNode = expr_list();
        return newNode;
    }

    else {
        return NULL;
    }
}


struct node* expr_list() {
    struct node* newNode = arith_exp();
    struct node* moreNodes = more_expr_list();

    newNode->next = moreNodes;

    return newNode;
}


struct node* opt_expr_list() {
    if(cur_token == ID || cur_token == INTCON || cur_token == LPAREN || cur_token == opSUB) {
        struct node* newNode = expr_list();

        return newNode;
    }
   
    else {
        return NULL;
    }
}


struct node* makeParamExprList(struct node* params) {
    struct node* temp = params;
    struct node* newList = NULL;

    while(temp != NULL) {
        if(newList == NULL) {
            struct node* exprNode = makeEmptyNode("expr", EXPR_LIST);
            exprNode->childOne = temp;
            newList = exprNode;
            temp = temp->next;
        }
        else {
            struct node* exprNode = makeEmptyNode("expr", EXPR_LIST);
            exprNode->childOne = temp;

            struct node* traverse = newList;
            while(traverse->next != NULL) {
                traverse = traverse->next;
            }
            traverse->next = exprNode;

            temp = temp->next;
        }   
    }

    return newList;
}


struct node* fn_call_or_assg() {
    // fn_call
    if(cur_token == LPAREN) {
        stmt_list = 1; // Needs the list of params
        char* save_call;

        struct node* newFnCall = makeEmptyNode(cur_variable, FUNC_CALL);
        curNode = newFnCall;
        save_call = strdup(cur_variable);

        // Check if function already in table
        int localVal = checkForVariable(cur_variable, cur_table);
        int globalVal = checkForFunction(cur_variable, cur_table->up);

        if(chk_decl_flag == 1) {
            if(globalVal == 0) {
                fprintf(stderr, "ERROR on LINE %d, fn_call_or_assg1 exit status = 1\n", line);
                exit(1);
            }
            else if(localVal == 1) {
                fprintf(stderr, "ERROR on LINE %d, fn_call_or_assg2 exit status = 1\n", line);
                exit(1);
            }
        }
        struct table* getTable = getTableEntry(save_call, cur_table->up);
        newFnCall->location = getTable;

        match(LPAREN);
        count_formals = 0;

        struct node* params = opt_expr_list(); // Making expr_list

        int numParams = countFuncCallParams(params);

        struct node* paramsList = makeParamExprList(params);
        newFnCall->childOne = paramsList;

        if(chk_decl_flag == 1) {
            int count = getCount(save_call, cur_table->up);
            if(globalVal == 1 &&  count != numParams) {
                fprintf(stderr, "ERROR on LINE %d, fn_call_or_assg3 exit status = 1\n", line);
                exit(1);
            }
        }
        newFnCall->numParams = count_formals;

        match(RPAREN);
        match(SEMI);
        return newFnCall;
    }

    // assg
    else {
        stmt_list = 0;
        // Check if variable is in the table
        int localVal = findVariable(cur_variable, cur_table);
        int globalVal = findVariable(cur_variable, cur_table->up);
        //int globalFunc = checkForFunction(cur_variable, cur_table->up);

        if(chk_decl_flag == 1) {
            if(globalVal == 0 && localVal == 0) {
                fprintf(stderr, "ERROR on LINE %d, fn_call_or_assg4 exit status = 1\n", line);
                exit(1);
            }

            // else if(globalVal == 1) {
            //     if(globalFunc == 1) {
            //         fprintf(stderr, "ERROR on LINE %d, fn_call_or_assg5 exit status = 1\n", line);
            //         exit(1);
            //     }
            // }
        }

        struct node* newAssg = makeEmptyNode("assg", ASSG);   
        curNode = newAssg;

        struct node* lhs = makeEmptyNode(cur_variable, IDENTIFIER);
        curNode->childOne = lhs;

        // Check local table first
        if(localVal == 1) {
            struct table* getTable = getTableEntry(cur_variable, cur_table);
            curNode->childOne->location = getTable;
        }
        else if(globalVal == 1) {
            struct table* getTable = getTableEntry(cur_variable, cur_table->up);
            curNode->childOne->location = getTable;
        }

        match(opASSG);
        matchedINTCON = 0;
        struct node* ch2 = arith_exp();

        newAssg->childTwo = ch2;

        matchedINTCON = 0;
        
        match(SEMI);
        return newAssg;
    }
}


struct node* relop() {
    if(cur_token == opEQ) {        
        match(opEQ);
        struct node* exprNode = makeEmptyNode("equal", EQ);
        return exprNode;
    }

    else if(cur_token == opNE) {
        match(opNE);
        struct node* exprNode = makeEmptyNode("notEqual", NE);
        return exprNode;
    }

    else if(cur_token == opLE) {
        match(opLE);
        struct node* exprNode = makeEmptyNode("lessEqual", LE);
        return exprNode;
    }

    else if(cur_token == opLT) {
        match(opLT);
        struct node* exprNode = makeEmptyNode("less", LT);
        return exprNode;
    }

    else if(cur_token == opGE) {
        match(opGE);
        struct node* exprNode = makeEmptyNode("greaterEqual", GE);
        return exprNode;
    }

    else {
        match(opGT);
        struct node* exprNode = makeEmptyNode("greater", GT);
        return exprNode;
    }
}


struct node* bool_exp3() {
    stmt_list = 0;
    matchedINTCON = 0;
    struct node* exprChildOne = arith_exp(); 

    struct node* op = relop(); // Make the expr node
    op->childOne = exprChildOne;
        
    struct node* exprChildTwo = arith_exp();

    op->childTwo = exprChildTwo;
    return op;
}


struct node* match_and(struct node* leftTree) {
    if(cur_token == opAND) {
        struct node* opNode = logical_op();
        opNode->childOne = leftTree;
        
        struct node* rightTree = bool_exp3();
        opNode->childTwo = rightTree;
        
        struct node* newNode = match_and(opNode);

        return newNode;
    }
    else {
        return leftTree;
    }
}


struct node* match_or(struct node* leftTree) {
    if(cur_token == opOR) {
        struct node* opNode = logical_op();
        opNode->childOne = leftTree;

        struct node* rightTree = bool_exp2();
        opNode->childTwo = rightTree;

        struct node* newNode = match_or(opNode);

        return newNode;
    }
    else {
        return leftTree;
    }
}


struct node* bool_exp2() {
    struct node* newNode = bool_exp3();
    struct node* opNode = match_and(newNode);
    
    return opNode;
}


struct node* bool_exp() {
    struct node* newNode = bool_exp2();
    struct node* opNode = match_or(newNode);

    return opNode;
}


struct node* while_stmt() {
    match(kwWHILE);
    struct node* newWhile = makeEmptyNode("while", WHILE);
    curNode = newWhile;
    
    match(LPAREN);
    struct node* ch1 = bool_exp(); // condition subtree
    newWhile->childOne = ch1;

    match(RPAREN);
    struct node* ch2 = stmt(); // body subtree
    newWhile->childTwo = ch2;

    return newWhile;
}


struct node* opt_if_stmt() {
    if(cur_token == kwELSE) {
        match(kwELSE);
        struct node* elseNode = stmt();       
        return elseNode;
    }

    else {
        return NULL;
    }
}


struct node* if_stmt() {
    match(kwIF);
    struct node* newIf = makeEmptyNode("if", IF);
    curNode = newIf;
    match(LPAREN);
    
    struct node* ch1 = bool_exp(); // condition subtree
    newIf->childOne = ch1;

    match(RPAREN);
    struct node* body = stmt(); // body subtree
    newIf->childTwo = body;

    struct node* bodyTwo = opt_if_stmt(); // else subtree
    newIf->childThree = bodyTwo;

    return newIf;
}


struct node* opt_return() {
    if(cur_token == SEMI) {
        match(SEMI);
        return NULL;
    }

    else {
        stmt_list = 0;
        matchedINTCON = 0;
        
        struct node* newNode = arith_exp();

        struct node* expr = NULL;

        if(matchedINTCON == 1) {
            expr = makeEmptyIntcon(cur_const, INTCONST);
        }
        else {
            expr = makeEmptyNode(cur_variable, IDENTIFIER);
            int localVal = checkForVariable(cur_variable, cur_table);
            int globalVal = checkForVariable(cur_variable, cur_table->up);

            if(localVal == 1) {
                struct table* getTable = getTableEntry(cur_variable, cur_table);
                expr->location = getTable;
            }
            else if(globalVal == 1) {
                struct table* getTable = getTableEntry(cur_variable, cur_table->up);
                expr->location = getTable;
            }
        }
        match(SEMI);
        return newNode;
    }
}


struct node* return_stmt() {
    match(kwRETURN);
    struct node* newReturn = makeEmptyNode("return", RETURN);
    curNode = newReturn;

    struct node* body = opt_return();
    newReturn->childOne = body;
    return newReturn;
}


void fn_call() {
    match(ID);
    stmt_list = 1; // Needs the list of params
        
    struct node* newNode = makeEmptyNode(cur_variable, FUNC_CALL);
    if(root->childOne == NULL) {
        root->childOne = newNode;
        curNode = newNode;
    }
    else {
        struct node* temp = root->childOne;
        while(temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = newNode;
        curNode = newNode;
    }

    //save_call = strdup(cur_variable);
    save_call = malloc(sizeof(char)*strlen(cur_variable)+1);
    int i;
    for(i = 0; cur_variable[i] != '\0'; i++) {
        save_call[i] = cur_variable[i];
    }
    save_call[i] = '\0';

    // Check if function already in table
    int localVal = checkForVariable(cur_variable, cur_table);
    int globalVal = checkForFunction(cur_variable, cur_table->up);

    if(chk_decl_flag == 1) {
        if(globalVal == 0) {
            fprintf(stderr, "ERROR on LINE %d, fn_call1 exit status = 1\n", line);
            exit(1);
        }
        else if(localVal == 1) {
            fprintf(stderr, "ERROR on LINE %d, fn_call2 exit status = 1\n", line);
            exit(1);
        }
    }
    struct table* getTable = getTableEntry(save_call, cur_table->up);
    curNode->location = getTable;

    match(LPAREN);
    count_formals = 0;
    opt_expr_list();
    if(chk_decl_flag == 1) {
        int count = getCount(save_call, cur_table->up);
        if(globalVal == 1 &&  count != count_formals) {
            fprintf(stderr, "ERROR on LINE %d, fn_call3 exit status = 1\n", line);
            exit(1);
        }
    }
    curNode->numParams = count_formals;

    count_formals = 0;
    opt_expr_list();
    if(chk_decl_flag == 1) {
        if(globalVal == 1 && getCount(cur_variable, cur_table->up) != count_formals) {
            fprintf(stderr, "ERROR on LINE %d, fn_call4 exit status = 1\n", line);
            exit(1);
        }

    }
           
    match(RPAREN);
}


struct node* stmt() {
    struct node* newNode = NULL;

    if(cur_token == ID) {
        match(ID);
        newNode = fn_call_or_assg();
        return newNode;
    }

    else if(cur_token == kwWHILE) {
        newNode = while_stmt();
    }

    else if(cur_token == kwIF) {
        newNode = if_stmt();
    }

    else if(cur_token == kwRETURN) {
        newNode = return_stmt();
        return newNode;
    }

    else if(cur_token == LBRACE) {
        match(LBRACE);
        newNode = opt_stmt_list();
        match(RBRACE);
    }

    else {
        match(SEMI);
    }

    return newNode;
}


struct node* opt_stmt_list() {
    struct node* newNode = NULL;

    while(cur_token == ID || cur_token == kwWHILE || cur_token == kwIF || cur_token == kwRETURN ||
          cur_token == LBRACE || cur_token == SEMI) {
        
        struct node* stmtNode = stmt();

        // Add stmtNode to the back of the list
        if(newNode == NULL) {
            struct node* start = makeEmptyParam(STMT_LIST);
            start->childOne = stmtNode;
            newNode = start;
        }

        else {
            struct node* temp = newNode;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            struct node* start = makeEmptyParam(STMT_LIST);
            start->childOne = stmtNode;
            temp->next = start;
        }
    }
    return newNode;
}


struct quad* reverseList(struct quad* funcCallList) {
    struct quad* prev = NULL;
    struct quad* curr = funcCallList;
    struct quad* next = NULL;

    while(curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    return(prev);
}


int lableCount = 0;
struct quad* traverse(struct node* start, int trueLabel, int falseLabel) {
    if(start == NULL) {
        return NULL;
    }

    else if(start->type == FUNC_DEF) {
        struct quad* enter = newInstruction("ENTER");
        struct operand* op1 = newOperand();
        struct operand* op2 = newOperand();
        struct table* getTable = getTableEntry(start->name, cur_table->up);
        op1->location = getTable;
        op1->stmts = start->stmts;
        op2->intcon = start->numParams;
        
        enter->src1 = op1;
        enter->src2 = op2;

        struct quad* leave = newInstruction("LEAVE");
        
        struct quad* body = traverse(start->childOne, 0, 0);
        start->threeAddr = enter;
        enter->next = body;
        
        struct quad* temp = enter;
        if(temp == NULL) {
            return leave;
        }
        else {
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = leave;
        }

        return(enter);
    }


    else if(start->type == STMT_LIST) {
        struct quad* nextStmt = traverse(start->next, 0, 0); 
        struct quad* children = traverse(start->childOne, 0, 0);
        
        start->threeAddr = children;
        
        struct quad* temp = children;
        if(temp == NULL) {
            children = nextStmt;
        }
        else {
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = nextStmt;
        }

        return(children);
    }

    
    else if(start->type == ASSG) {
        traverse(start->childOne, 0, 0);
        struct quad* ch2 = traverse(start->childTwo, 0, 0);
        
        struct quad* threeAdd = newInstruction("ASSG");
        struct operand* op = newOperand();
        struct operand* destination = newOperand();

        start->threeAddr = threeAdd;

        if(start->childTwo->type == INTCONST) {
            op->location = start->childTwo->threeAddr->dest->location;
            threeAdd->src1 = op;
            destination->location = start->childOne->location;
            threeAdd->dest = destination;
            ch2->next = threeAdd;
            threeAdd = ch2;
        }
        else if(start->childTwo->type == IDENTIFIER) {
            op->location = start->childTwo->location;
            threeAdd->src1 = op;
            destination->location = start->childOne->location;
            threeAdd->dest = destination;
        }
        else if(start->childTwo->type == ADD || start->childTwo->type == SUB || start->childTwo->type == MUL || start->childTwo->type == DIV || start->childTwo->type == UMINUS || start->childTwo->type == FUNC_CALL) {
            op->location = start->childTwo->threeAddr->dest->location;
            threeAdd->src1 = op;
            destination->location = start->childOne->location;
            threeAdd->dest = destination;

            struct quad* temp = ch2;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;

            threeAdd = ch2;
        }

        return(threeAdd);
    }


    else if(start->type == IDENTIFIER) {
        return NULL;
    }


    else if(start->type == INTCONST) {
        char newBuf[7];
        snprintf(newBuf, sizeof(newBuf), "%s%d", "temp", count);
        count++;

        addVariable(newBuf, "INTCON", &cur_table->symbolTables);        
        struct table* tempNode = getTableEntry(newBuf, cur_table);

        struct quad* threeAdd = newInstruction("ASSG");
        struct operand* newOp = newOperand();
        struct operand* destination = newOperand();
        newOp->intcon = start->val;
        destination->location = tempNode;
        
        threeAdd->src1 = newOp;
        threeAdd->dest = destination;
        start->threeAddr = threeAdd;

        return(threeAdd);
    }


    else if(start->type == EXPR_LIST) {
        struct quad* nextStmt = traverse(start->next, 0, 0);
        struct quad* child = traverse(start->childOne, 0, 0);   

        struct quad* threeAdd = newInstruction("PARAM");
        struct operand* op = newOperand();
        start->threeAddr = threeAdd;

        if(start->childOne->type == INTCONST) {
            op->location = start->childOne->threeAddr->dest->location;
        }
        else if(start->childOne->type == IDENTIFIER) {
            op->location = start->childOne->location;
        }
        else if(start->childOne->type == ADD || start->childOne->type == SUB || start->childOne->type == MUL || start->childOne->type == DIV || start->childOne->type == UMINUS || start->childOne->type == FUNC_CALL) {
            op->location = start->childOne->threeAddr->dest->location;
        }

        threeAdd->src1 = op;

        if(child != NULL && nextStmt != NULL) {
            struct quad* temp = nextStmt;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = child;

            temp = child;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;

            threeAdd = nextStmt;
        }
        else if(child != NULL && nextStmt == NULL) {
            struct quad* temp = child;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;

            threeAdd = child;
        }
        else if(child == NULL && nextStmt != NULL) {
            struct quad* temp = nextStmt;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;

            threeAdd = nextStmt;
        }

        return(threeAdd);     
    }


    else if(start->type == FUNC_CALL) {
        struct quad* exprList = traverse(start->childOne, 0, 0);

        struct quad* fnCall = newInstruction("CALL");
        struct table* funcName = getTableEntry(start->name, cur_table->up);
        struct operand* op1 = newOperand();
        op1->location = funcName;
        fnCall->src1 = op1;

        struct operand* op2 = newOperand();
        op2->intcon = start->numParams;
        fnCall->src2 = op2;

        char newBuf[7];
        snprintf(newBuf, sizeof(newBuf), "%s%d", "temp", count);
        count++;

        addVariable(newBuf, "INTCON", &cur_table->symbolTables);        
        struct table* tempNode = getTableEntry(newBuf, cur_table);

        struct quad* threeAdd = newInstruction("RETRIEVE");
        struct operand* destination = newOperand();
        destination->location = tempNode;
        threeAdd->dest = destination;

        fnCall->next = threeAdd;
        start->threeAddr = threeAdd;

        if(exprList != NULL) {
            struct quad* temp = exprList;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = fnCall;

            fnCall = exprList;
        }

        return(fnCall);
    }


    else if(start->type == IF) {
        struct quad* body = traverse(start->childTwo, 0, 0);
        struct quad* elseStmt = traverse(start->childThree, 0, 0);

        int trueLabelVal = getNewLabel(newLabel);
        int falseLabelVal = getNewLabel(newLabel);
        int afterVal = getNewLabel(newLabel);

        struct quad* goto1 = newInstruction("GOTO");
        struct operand* goto1Dest = newOperand();
        goto1Dest->intcon = falseLabelVal;
        goto1->dest = goto1Dest;

        struct quad* label1 = newInstruction("LABEL");
        struct operand* labelName = newOperand();
        labelName->intcon = trueLabelVal;
        label1->src1 = labelName;

        goto1->next = label1;
        lableCount++;

        struct quad* goto2 = newInstruction("GOTO");
        struct operand* goto2Dest = newOperand();
        goto2Dest->intcon = afterVal;
        goto2->dest = goto2Dest;

        struct quad* label2 = newInstruction("LABEL");
        struct operand* label2Name = newOperand();
        label2Name->intcon = falseLabelVal;
        label2->src1 = label2Name;

        goto2->next = label2;

        struct quad* label3 = newInstruction("LABEL");
        struct operand* label3Name = newOperand();
        label3Name->intcon = afterVal;
        label3->src1 = label3Name;

        struct quad* boolExpr = traverse(start->childOne, trueLabelVal, falseLabelVal);

        struct quad* temp = boolExpr;
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = goto1;

        label1->next = body;
        temp = label1;
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = goto2;

        label2->next = elseStmt;
        temp = label2;
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = label3;

        start->threeAddr = boolExpr;

        return(boolExpr);
    }


    else if(start->type == WHILE) {
        struct quad* body = traverse(start->childTwo, 0, 0);

        int trueLabelVal = getNewLabel(newLabel);
        int falseLabelVal = getNewLabel(newLabel);
        int afterVal = getNewLabel(newLabel);

        struct quad* goto1 = newInstruction("GOTO");
        struct operand* goto1Dest = newOperand();
        goto1Dest->intcon = falseLabelVal;
        goto1->dest = goto1Dest;

        struct quad* label1 = newInstruction("LABEL");
        struct operand* labelName = newOperand();
        labelName->intcon = trueLabelVal;
        label1->src1 = labelName;

        goto1->next = label1;
        //lableCount++;

        struct quad* goto2 = newInstruction("GOTO");
        struct operand* goto2Dest = newOperand();
        goto2Dest->intcon = afterVal;
        goto2->dest = goto2Dest;

        struct quad* label2 = newInstruction("LABEL");
        struct operand* label2Name = newOperand();
        label2Name->intcon = falseLabelVal;
        label2->src1 = label2Name;

        goto2->next = label2;

        struct quad* label3 = newInstruction("LABEL");
        struct operand* label3Name = newOperand();
        label3Name->intcon = afterVal;
        label3->src1 = label3Name;

        struct quad* boolExpr = traverse(start->childOne, trueLabelVal, falseLabelVal);

        label3->next = boolExpr;

        struct quad* temp = label3;
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = goto1;

        label1->next = body;

        temp = label1;
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = goto2;

        return(label3);
    }


    else if(start->type == EQ) {
        struct quad* lhs = traverse(start->childOne, 0, 0);
        struct quad* rhs = traverse(start->childTwo, 0, 0);

        struct quad* threeAdd = newInstruction("OP_EQ");
        struct operand* op1 = newOperand();
        struct operand* op2 = newOperand();
        struct operand* destination = newOperand();

        int lhsInt = 0;
        int rhsInt = 0;

        if(start->childOne->type == IDENTIFIER) {
            op1->location = start->childOne->location;
        }
        else if(start->childOne->type == INTCONST) {
            lhsInt = 1;
            op1->location = start->childOne->threeAddr->dest->location;
        }
        else if(start->childOne->type == ADD || start->childOne->type == SUB || start->childOne->type == MUL || start->childOne->type == DIV || start->childOne->type == UMINUS || start->childOne->type == FUNC_CALL) {
            lhsInt = 1;
            op1->location = start->childOne->threeAddr->dest->location;
        }

        if(start->childTwo->type == IDENTIFIER) {
            op2->location = start->childTwo->location;
        }
        else if(start->childTwo->type == INTCONST) {
            rhsInt = 1;
            op2->location = start->childTwo->threeAddr->dest->location;
        }
        else if(start->childTwo->type == ADD || start->childTwo->type == SUB || start->childTwo->type == MUL || start->childTwo->type == DIV || start->childTwo->type == UMINUS || start->childTwo->type == FUNC_CALL) {
            rhsInt = 1;
            op2->location = start->childTwo->threeAddr->dest->location;
        }

        destination->intcon = trueLabel;

        threeAdd->src1 = op1;
        threeAdd->src2 = op2;
        threeAdd->dest = destination;
        start->threeAddr = threeAdd;

        if(lhsInt == 1 && rhsInt == 1) {
            struct quad* temp = lhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = rhs;

            temp = rhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;

            threeAdd = lhs;
        }
        else if(lhsInt == 1 && rhsInt == 0) {
            struct quad* temp = lhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;
            threeAdd = lhs;
        }
        else if(lhsInt == 0 && rhsInt == 1) {
            struct quad* temp = rhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;
            threeAdd = rhs;
        }

        return(threeAdd);
    }

    else if(start->type == NE) {
        struct quad* lhs = traverse(start->childOne, 0, 0);
        struct quad* rhs = traverse(start->childTwo, 0, 0);

        struct quad* threeAdd = newInstruction("OP_NE");
        struct operand* op1 = newOperand();
        struct operand* op2 = newOperand();
        struct operand* destination = newOperand();

        int lhsInt = 0;
        int rhsInt = 0;

        if(start->childOne->type == IDENTIFIER) {
            op1->location = start->childOne->location;
        }
        else if(start->childOne->type == INTCONST) {
            lhsInt = 1;
            op1->location = start->childOne->threeAddr->dest->location;
        }
        else if(start->childOne->type == ADD || start->childOne->type == SUB || start->childOne->type == MUL || start->childOne->type == DIV || start->childOne->type == UMINUS || start->childOne->type == FUNC_CALL) {
            lhsInt = 1;
            op1->location = start->childOne->threeAddr->dest->location;
        }

        if(start->childTwo->type == IDENTIFIER) {
            op2->location = start->childTwo->location;
        }
        else if(start->childTwo->type == INTCONST) {
            rhsInt = 1;
            op2->location = start->childTwo->threeAddr->dest->location;
        }
        else if(start->childTwo->type == ADD || start->childTwo->type == SUB || start->childTwo->type == MUL || start->childTwo->type == DIV || start->childTwo->type == UMINUS || start->childTwo->type == FUNC_CALL) {
            rhsInt = 1;
            op2->location = start->childTwo->threeAddr->dest->location;
        }

        destination->intcon = trueLabel;

        threeAdd->src1 = op1;
        threeAdd->src2 = op2;
        threeAdd->dest = destination;
        start->threeAddr = threeAdd;

        if(lhsInt == 1 && rhsInt == 1) {
            struct quad* temp = lhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = rhs;

            temp = rhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;

            threeAdd = lhs;
        }
        else if(lhsInt == 1 && rhsInt == 0) {
            struct quad* temp = lhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;
            threeAdd = lhs;
        }
        else if(lhsInt == 0 && rhsInt == 1) {
            struct quad* temp = rhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;
            threeAdd = rhs;
        }

        return(threeAdd);

    }

    else if(start->type == LE) {
        struct quad* lhs = traverse(start->childOne, 0, 0);
        struct quad* rhs = traverse(start->childTwo, 0, 0);

        struct quad* threeAdd = newInstruction("OP_LE");
        struct operand* op1 = newOperand();
        struct operand* op2 = newOperand();
        struct operand* destination = newOperand();

        int lhsInt = 0;
        int rhsInt = 0;

        if(start->childOne->type == IDENTIFIER) {
            op1->location = start->childOne->location;
        }
        else if(start->childOne->type == INTCONST) {
            lhsInt = 1;
            op1->location = start->childOne->threeAddr->dest->location;
        }
        else if(start->childOne->type == ADD || start->childOne->type == SUB || start->childOne->type == MUL || start->childOne->type == DIV || start->childOne->type == UMINUS || start->childOne->type == FUNC_CALL) {
            lhsInt = 1;
            op1->location = start->childOne->threeAddr->dest->location;
        }

        if(start->childTwo->type == IDENTIFIER) {
            op2->location = start->childTwo->location;
        }
        else if(start->childTwo->type == INTCONST) {
            rhsInt = 1;
            op2->location = start->childTwo->threeAddr->dest->location;
        }
        else if(start->childTwo->type == ADD || start->childTwo->type == SUB || start->childTwo->type == MUL || start->childTwo->type == DIV || start->childTwo->type == UMINUS || start->childTwo->type == FUNC_CALL) {
            rhsInt = 1;
            op2->location = start->childTwo->threeAddr->dest->location;
        }

        destination->intcon = trueLabel;

        threeAdd->src1 = op1;
        threeAdd->src2 = op2;
        threeAdd->dest = destination;
        start->threeAddr = threeAdd;

        if(lhsInt == 1 && rhsInt == 1) {
            struct quad* temp = lhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = rhs;

            temp = rhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;

            threeAdd = lhs;
        }
        else if(lhsInt == 1 && rhsInt == 0) {
            struct quad* temp = lhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;
            threeAdd = lhs;
        }
        else if(lhsInt == 0 && rhsInt == 1) {
            struct quad* temp = rhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;
            threeAdd = rhs;
        }

        return(threeAdd);
    }

    else if(start->type == LT) {
        struct quad* lhs = traverse(start->childOne, 0, 0);
        struct quad* rhs = traverse(start->childTwo, 0, 0);

        struct quad* threeAdd = newInstruction("OP_LT");
        struct operand* op1 = newOperand();
        struct operand* op2 = newOperand();
        struct operand* destination = newOperand();

        int lhsInt = 0;
        int rhsInt = 0;

        if(start->childOne->type == IDENTIFIER) {
            op1->location = start->childOne->location;
        }
        else if(start->childOne->type == INTCONST) {
            lhsInt = 1;
            op1->location = start->childOne->threeAddr->dest->location;
        }
        else if(start->childOne->type == ADD || start->childOne->type == SUB || start->childOne->type == MUL || start->childOne->type == DIV || start->childOne->type == UMINUS || start->childOne->type == FUNC_CALL) {
            lhsInt = 1;
            op1->location = start->childOne->threeAddr->dest->location;
        }

        if(start->childTwo->type == IDENTIFIER) {
            op2->location = start->childTwo->location;
        }
        else if(start->childTwo->type == INTCONST) {
            rhsInt = 1;
            op2->location = start->childTwo->threeAddr->dest->location;
        }
        else if(start->childTwo->type == ADD || start->childTwo->type == SUB || start->childTwo->type == MUL || start->childTwo->type == DIV || start->childTwo->type == UMINUS || start->childTwo->type == FUNC_CALL) {
            rhsInt = 1;
            op2->location = start->childTwo->threeAddr->dest->location;
        }

        destination->intcon = trueLabel;

        threeAdd->src1 = op1;
        threeAdd->src2 = op2;
        threeAdd->dest = destination;
        start->threeAddr = threeAdd;

        if(lhsInt == 1 && rhsInt == 1) {
            struct quad* temp = lhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = rhs;

            temp = rhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;

            threeAdd = lhs;
        }
        else if(lhsInt == 1 && rhsInt == 0) {
            struct quad* temp = lhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;
            threeAdd = lhs;
        }
        else if(lhsInt == 0 && rhsInt == 1) {
            struct quad* temp = rhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;
            threeAdd = rhs;
        }

        return(threeAdd);
    }

    else if(start->type == GE) {
        struct quad* lhs = traverse(start->childOne, 0, 0);
        struct quad* rhs = traverse(start->childTwo, 0, 0);

        struct quad* threeAdd = newInstruction("OP_GE");
        struct operand* op1 = newOperand();
        struct operand* op2 = newOperand();
        struct operand* destination = newOperand();

        int lhsInt = 0;
        int rhsInt = 0;

        if(start->childOne->type == IDENTIFIER) {
            op1->location = start->childOne->location;
        }
        else if(start->childOne->type == INTCONST) {
            lhsInt = 1;
            op1->location = start->childOne->threeAddr->dest->location;
        }
        else if(start->childOne->type == ADD || start->childOne->type == SUB || start->childOne->type == MUL || start->childOne->type == DIV || start->childOne->type == UMINUS || start->childOne->type == FUNC_CALL) {
            lhsInt = 1;
            op1->location = start->childOne->threeAddr->dest->location;
        }

        if(start->childTwo->type == IDENTIFIER) {
            op2->location = start->childTwo->location;
        }
        else if(start->childTwo->type == INTCONST) {
            rhsInt = 1;
            op2->location = start->childTwo->threeAddr->dest->location;
        }
        else if(start->childTwo->type == ADD || start->childTwo->type == SUB || start->childTwo->type == MUL || start->childTwo->type == DIV || start->childTwo->type == UMINUS || start->childTwo->type == FUNC_CALL) {
            rhsInt = 1;
            op2->location = start->childTwo->threeAddr->dest->location;
        }

        destination->intcon = trueLabel;

        threeAdd->src1 = op1;
        threeAdd->src2 = op2;
        threeAdd->dest = destination;
        start->threeAddr = threeAdd;

        if(lhsInt == 1 && rhsInt == 1) {
            struct quad* temp = lhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = rhs;

            temp = rhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;

            threeAdd = lhs;
        }
        else if(lhsInt == 1 && rhsInt == 0) {
            struct quad* temp = lhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;
            threeAdd = lhs;
        }
        else if(lhsInt == 0 && rhsInt == 1) {
            struct quad* temp = rhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;
            threeAdd = rhs;
        }

        return(threeAdd);
    }

    else if(start->type == GT) {
        struct quad* lhs = traverse(start->childOne, 0, 0);
        struct quad* rhs = traverse(start->childTwo, 0, 0);

        struct quad* threeAdd = newInstruction("OP_GT");
        struct operand* op1 = newOperand();
        struct operand* op2 = newOperand();
        struct operand* destination = newOperand();

        int lhsInt = 0;
        int rhsInt = 0;

        if(start->childOne->type == IDENTIFIER) {
            op1->location = start->childOne->location;
        }
        else if(start->childOne->type == INTCONST) {
            lhsInt = 1;
            op1->location = start->childOne->threeAddr->dest->location;
        }
        else if(start->childOne->type == ADD || start->childOne->type == SUB || start->childOne->type == MUL || start->childOne->type == DIV || start->childOne->type == UMINUS || start->childOne->type == FUNC_CALL) {
            lhsInt = 1;
            op1->location = start->childOne->threeAddr->dest->location;
        }

        if(start->childTwo->type == IDENTIFIER) {
            op2->location = start->childTwo->location;
        }
        else if(start->childTwo->type == INTCONST) {
            rhsInt = 1;
            op2->location = start->childTwo->threeAddr->dest->location;
        }
        else if(start->childTwo->type == ADD || start->childTwo->type == SUB || start->childTwo->type == MUL || start->childTwo->type == DIV || start->childTwo->type == UMINUS || start->childTwo->type == FUNC_CALL) {
            rhsInt = 1;
            op2->location = start->childTwo->threeAddr->dest->location;
        }

        destination->intcon = trueLabel;

        threeAdd->src1 = op1;
        threeAdd->src2 = op2;
        threeAdd->dest = destination;
        start->threeAddr = threeAdd;

        if(lhsInt == 1 && rhsInt == 1) {
            struct quad* temp = lhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = rhs;

            temp = rhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;

            threeAdd = lhs;
        }
        else if(lhsInt == 1 && rhsInt == 0) {
            struct quad* temp = lhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;
            threeAdd = lhs;
        }
        else if(lhsInt == 0 && rhsInt == 1) {
            struct quad* temp = rhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;
            threeAdd = rhs;
        }

        return(threeAdd);
    }


    else if(start->type == AND) {
        int newLabelVal = getNewLabel(newLabel);
        struct quad* label1 = newInstruction("LABEL");
        struct operand* labelName = newOperand();
        labelName->intcon = newLabelVal;
        label1->src1 = labelName;

        int gotoVal = falseLabel;
        struct quad* goto1 = newInstruction("GOTO");
        struct operand* goto1Dest = newOperand();
        goto1Dest->intcon = gotoVal;
        goto1->dest = goto1Dest;

        goto1->next = label1;

        struct quad* lhs = traverse(start->childOne, newLabelVal, falseLabel);
        struct quad* rhs = traverse(start->childTwo, trueLabel, falseLabel);

        label1->next = rhs;

        struct quad* temp = lhs;
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = goto1;

        return(lhs);
    }


    else if(start->type == OR) {        
        int newLabelVal = getNewLabel(newLabel);
        struct quad* label1 = newInstruction("LABEL");
        struct operand* labelName = newOperand();
        labelName->intcon = newLabelVal;
        label1->src1 = labelName;

        int gotoVal = newLabelVal;
        struct quad* goto1 = newInstruction("GOTO");
        struct operand* goto1Dest = newOperand();
        goto1Dest->intcon = gotoVal;
        goto1->dest = goto1Dest;

        goto1->next = label1;

        struct quad* lhs = traverse(start->childOne, trueLabel, newLabelVal);
        struct quad* rhs = traverse(start->childTwo, trueLabel, falseLabel);

        label1->next = rhs;

        struct quad* temp = lhs;
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = goto1;

        return(lhs);
    }


    else if(start->type == ADD) {
        struct quad* threeAdd = newInstruction("ADD");
        struct operand* op1 = newOperand(); 
        struct operand* op2 = newOperand();
        struct operand* destination = newOperand();

        int lhsInt = 0;
        int rhsInt = 0;

        struct quad* lhs = traverse(start->childOne, 0, 0);
        if(start->childOne->type == IDENTIFIER) {
            op1->location = start->childOne->location;
            threeAdd->src1 = op1;
        }
        else {
            lhsInt = 1;
            op1->location = start->childOne->threeAddr->dest->location;
            threeAdd->src1 = op1;
        }

        struct quad* rhs = traverse(start->childTwo, 0, 0);
        if(start->childTwo->type == IDENTIFIER) {
            op2->location = start->childTwo->location;
            threeAdd->src2 = op2;
        }
        else {
            rhsInt = 1;
            op2->location = start->childTwo->threeAddr->dest->location;
            threeAdd->src2 = op2;
        }

        char newBuf[7];
        snprintf(newBuf, sizeof(newBuf), "%s%d", "temp", count);
        count++;

        addVariable(newBuf, "INTCON", &cur_table->symbolTables);        
        struct table* tempNode = getTableEntry(newBuf, cur_table);
        destination->location = tempNode;
        threeAdd->dest = destination;

        start->threeAddr = threeAdd; 

        if(lhsInt == 0 && rhsInt == 0) {
            return(threeAdd);
        } 
        else if(lhsInt == 1 && rhsInt == 0) {
            struct quad* temp = lhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;
            threeAdd = lhs;
        }
        else if(lhsInt == 0 && rhsInt == 1) {
            struct quad* temp = rhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;
            threeAdd = rhs;
        }

        else if(lhsInt == 1 && rhsInt == 1) {
            struct quad* temp = lhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = rhs;

            temp = rhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;

            threeAdd = lhs;
        }  
        
        return(threeAdd);
    }

    else if(start->type == SUB) {
        struct quad* threeAdd = newInstruction("SUB");

        struct operand* op1 = newOperand(); 
        struct operand* op2 = newOperand();
        struct operand* destination = newOperand();

        int lhsInt = 0;
        int rhsInt = 0;

        struct quad* lhs = traverse(start->childOne, 0, 0);
        if(start->childOne->type == IDENTIFIER) {
            op1->location = start->childOne->location;
            threeAdd->src1 = op1;
        }
        else {
            lhsInt = 1;
            op1->location = start->childOne->threeAddr->dest->location;
            threeAdd->src1 = op1;
        }

        struct quad* rhs = traverse(start->childTwo, 0, 0);
        if(start->childTwo->type == IDENTIFIER) {
            op2->location = start->childTwo->location;
            threeAdd->src2 = op2;
        }
        else {
            rhsInt = 1;
            op2->location = start->childTwo->threeAddr->dest->location;
            threeAdd->src2 = op2;
        }

        char newBuf[7];
        snprintf(newBuf, sizeof(newBuf), "%s%d", "temp", count);
        count++;

        addVariable(newBuf, "INTCON", &cur_table->symbolTables);        
        struct table* tempNode = getTableEntry(newBuf, cur_table);
        destination->location = tempNode;
        threeAdd->dest = destination;

        start->threeAddr = threeAdd;
        
        if(lhsInt == 0 && rhsInt == 0) {
            return(threeAdd);
        } 
        else if(lhsInt == 1 && rhsInt == 0) {
            struct quad* temp = lhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;
            threeAdd = lhs;
        }
        else if(lhsInt == 0 && rhsInt == 1) {
            struct quad* temp = rhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;
            threeAdd = rhs;
        }

        else if(lhsInt == 1 && rhsInt == 1) {
            struct quad* temp = lhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = rhs;

            temp = rhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;

            threeAdd = lhs;
        }  
        
        return(threeAdd);
    }

    else if(start->type == MUL) {
        struct quad* threeAdd = newInstruction("MUL");
        
        struct operand* op1 = newOperand(); 
        struct operand* op2 = newOperand();
        struct operand* destination = newOperand();

        int lhsInt = 0;
        int rhsInt = 0;

        struct quad* lhs = traverse(start->childOne, 0, 0);
        if(start->childOne->type == IDENTIFIER) {
            op1->location = start->childOne->location;
            threeAdd->src1 = op1;
        }
        else {
            lhsInt = 1;
            op1->location = start->childOne->threeAddr->dest->location;
            threeAdd->src1 = op1;
        }

        struct quad* rhs = traverse(start->childTwo, 0, 0);
        if(start->childTwo->type == IDENTIFIER) {
            op2->location = start->childTwo->location;
            threeAdd->src2 = op2;
        }
        else {
            rhsInt = 1;
            op2->location = start->childTwo->threeAddr->dest->location;
            threeAdd->src2 = op2;
        }

        char newBuf[7];
        snprintf(newBuf, sizeof(newBuf), "%s%d", "temp", count);
        count++;

        addVariable(newBuf, "INTCON", &cur_table->symbolTables);        
        struct table* tempNode = getTableEntry(newBuf, cur_table);
        destination->location = tempNode;
        threeAdd->dest = destination;

        start->threeAddr = threeAdd;
        
        if(lhsInt == 0 && rhsInt == 0) {
            return(threeAdd);
        } 
        else if(lhsInt == 1 && rhsInt == 0) {
            struct quad* temp = lhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;
            threeAdd = lhs;
        }
        else if(lhsInt == 0 && rhsInt == 1) {
            struct quad* temp = rhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;
            threeAdd = rhs;
        }

        else if(lhsInt == 1 && rhsInt == 1) {
            struct quad* temp = lhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = rhs;

            temp = rhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;

            threeAdd = lhs;
        }  
        
        return(threeAdd);
    }

    else if(start->type == DIV) {
        struct quad* threeAdd = newInstruction("DIV");
        
        struct operand* op1 = newOperand(); 
        struct operand* op2 = newOperand();
        struct operand* destination = newOperand();

        start->threeAddr = threeAdd;

        int lhsInt = 0;
        int rhsInt = 0;

        struct quad* lhs = traverse(start->childOne, 0, 0);
        if(start->childOne->type == IDENTIFIER) {
            op1->location = start->childOne->location;
            threeAdd->src1 = op1;
        }
        else {
            lhsInt = 1;
            op1->location = start->childOne->threeAddr->dest->location;
            threeAdd->src1 = op1;
        }

        struct quad* rhs = traverse(start->childTwo, 0, 0);
        if(start->childTwo->type == IDENTIFIER) {
            op2->location = start->childTwo->location;
            threeAdd->src2 = op2;
        }
        else {
            rhsInt = 1;
            op2->location = start->childTwo->threeAddr->dest->location;
            threeAdd->src2 = op2;
        }

        char newBuf[7];
        snprintf(newBuf, sizeof(newBuf), "%s%d", "temp", count);
        count++;

        addVariable(newBuf, "INTCON", &cur_table->symbolTables);        
        struct table* tempNode = getTableEntry(newBuf, cur_table);
        destination->location = tempNode;
        threeAdd->dest = destination;
        
        if(lhsInt == 0 && rhsInt == 0) {
            return(threeAdd);
        } 
        else if(lhsInt == 1 && rhsInt == 0) {
            struct quad* temp = lhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;
            threeAdd = lhs;
        }
        else if(lhsInt == 0 && rhsInt == 1) {
            struct quad* temp = rhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;
            threeAdd = rhs;
        }

        else if(lhsInt == 1 && rhsInt == 1) {
            struct quad* temp = lhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = rhs;

            temp = rhs;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;

            threeAdd = lhs;
        }  
        
        return(threeAdd);
    }

    else if(start->type == UMINUS) {
        struct quad* ch1 = traverse(start->childOne, 0, 0);

        struct quad* threeAdd = newInstruction("UMINUS");
        struct operand* op = newOperand();
        struct operand* destination = newOperand();

        char newBuf[7];
        snprintf(newBuf, sizeof(newBuf), "%s%d", "temp", count);
        count++;

        addVariable(newBuf, "INTCON", &cur_table->symbolTables);        
        struct table* tempNode = getTableEntry(newBuf, cur_table);
        destination->location = tempNode;
        threeAdd->dest = destination;

        start->threeAddr = threeAdd;
        if(start->childOne->type == IDENTIFIER) {
            op->location = start->childOne->location;
            threeAdd->src1 = op;
        }
        else if(start->childOne->type == INTCONST) {
            op->location = start->childOne->threeAddr->dest->location;
            threeAdd->src1 = op;
            ch1->next = threeAdd;

            threeAdd = ch1;
        }
        else if(start->childOne->type == ADD || start->childOne->type == SUB || start->childOne->type == MUL || start->childOne->type == DIV || start->childOne->type == FUNC_CALL) {
            op->location = start->childOne->threeAddr->dest->location;
            threeAdd->src1 = op;

            struct quad* temp = ch1;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;
            threeAdd = ch1;
        }
        else if(start->childOne->type == UMINUS) {
            op->location = start->childOne->threeAddr->dest->location;
            threeAdd->src1 = op;

            struct quad* temp = ch1;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = threeAdd;
            threeAdd = ch1;
        }

        return(threeAdd);
    }


    else if(start->type == RETURN) {
        struct quad* threeAdd = newInstruction("RETURN");

        struct quad* body = traverse(start->childOne, 0, 0);
        start->threeAddr = threeAdd;

        if(start->childOne != NULL) {
            if(start->childOne->type == INTCONST) {
                struct quad* temp = body;
                while(temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = threeAdd;

                struct operand* op = newOperand();
                op->location = body->dest->location;
                threeAdd->src1 = op;
                threeAdd = body;
            }

            else if(start->childOne->type == IDENTIFIER) {
                struct operand* op = newOperand();
                op->location = start->childOne->location;
                threeAdd->src1 = op;
            }
            
            else if(start->childOne->type == ADD || start->childOne->type == SUB || start->childOne->type == MUL || start->childOne->type == DIV || start->childOne->type == UMINUS || start->childOne->type == FUNC_CALL) {
                struct quad* temp = body;
                while(temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = threeAdd;

                struct operand* op = newOperand();
                op->location = start->childOne->threeAddr->dest->location;
                threeAdd->src1 = op;
                threeAdd = body;
            }
        }

        return(threeAdd);
    }


    return NULL;
}


void print(struct quad* linkedList) {
    printf("printing...\n");
    
    struct quad* temp = linkedList;
    while(temp != NULL) {
        if(strcmp(temp->op, "ASSG") == 0) {
            printf("%s  %d\n",temp->op, temp->src1->intcon);
        }
        else if(strcmp(temp->op, "FUNC_DEF") == 0) {
            printf("%s  %s\n", temp->op, temp->src1->location->name);
        }
        else {
            printf("%s\n", temp->op);
        }

        temp = temp->next;
    }
}


char* changeName(char* curName) {
    size_t original_len = strlen(curName);

    size_t new_len = original_len + 2; 
    char* newName = (char *)malloc(new_len * sizeof(char));

    newName[0] = '_';
    strcpy(newName + 1, curName);

    return newName;
}


void printGlobals() {
    printf(".data\n");

    struct table* temp = cur_table->symbolTables;

    while(temp != NULL) {
        if(checkType(temp->name,cur_table) == 1) {
            printf("%s: .space 4\n", changeName(temp->name));
        }
        temp = temp->nextTable;
    }
}


void countParams(struct node* params) {
    struct node* temp = params;

    int count = 8;
    while(temp != NULL) {
        temp->location->mips = count;
        count = count+4;
        temp = temp->next;
    }
}


int countRegisters() {
    struct table* temp = cur_table->symbolTables;
    int count = -4;

    while(temp != NULL) {
        if(temp->mips == 0) {
            temp->mips = count;
            count = count-4;
        }
        
        temp = temp->nextTable;
    }
    return count+4;
}


void printlnFunc() {
    printf(".align 2\n.data\n_nl: .asciiz \"\\n\"\n\n.align 2\n.text\n# println: print out an integer followed by a newline\n _println:\n    li $v0, 1\n    lw $a0, 0($sp)\n    syscall\n    li $v0, 4\n    la $a0, _nl\n    syscall\n    jr $ra\n");
    printf("\n");
}


void printMips(struct quad* linkedList) {
    struct quad* temp = linkedList;
    
    countParams(temp->src1->stmts);
    int space = (countRegisters());
    
    while(temp != NULL) {
        //printf("main: ");
        if(strcmp(temp->op, "ENTER") == 0) {
            printf("# ENTER\n");

            printf(".align 2\n");
            printf(".text\n");
            char* newName = changeName(temp->src1->location->name);
            printf("%s:\n", newName);
            printf("    la $sp, -8($sp)\n");
            printf("    sw $fp, 4($sp)\n");
            printf("    sw $ra, 0($sp)\n");
            printf("    la $fp, 0($sp)\n");
            printf("    la $sp, %d($sp)\n", space);
        }


        else if(strcmp(temp->op, "ASSG") == 0) {
            printf("    # ASSG\n");
            if(temp->src1->location != NULL) {
                int localSrc = checkForVariable(temp->src1->location->name, cur_table);
                int localDest = checkForVariable(temp->dest->location->name, cur_table);
                
                // Global
                if(localSrc != 1) {
                    printf("    lw $t0, _%s\n", temp->src1->location->name);
                }
                else {
                    printf("    lw $t0, %d($fp)\n", temp->src1->location->mips);
                }

                if(localDest != 1) {
                    printf("    sw $t0, _%s\n", temp->dest->location->name);
                }
                else {
                    printf("    sw $t0, %d($fp)\n", temp->dest->location->mips);
                }
            }

            else {
                int intcon = temp->src1->intcon;
                printf("    li $t0, %d\n", intcon);

                int localDest = checkForVariable(temp->dest->location->name,cur_table);
                if(localDest != 1) {
                    printf("    sw $t0, _%s\n", temp->dest->location->name);
                }
                else {
                    printf("    sw $t0, %d($fp)\n", temp->dest->location->mips);
                }
            }

        }


        else if(strcmp(temp->op, "PARAM") == 0) {
            printf("    # PARAM\n");

            int localSrc = checkForVariable(temp->src1->location->name, cur_table);
            if(localSrc == 0) {
                printf("    lw $t0, _%s\n", temp->src1->location->name);
            }
            else {
                printf("    lw $t0, %d($fp)\n", temp->src1->location->mips);
            }

            printf("    la $sp, -4($sp)\n");
            printf("    sw $t0, 0($sp)\n");
        }


        else if(strcmp(temp->op, "CALL") == 0) {
            printf("    # CALL\n");
            
            printf("    jal _%s\n", temp->src1->location->name);
            printf("    la $sp, %d($sp)\n", temp->src2->intcon*4);
        }


        else if(strcmp(temp->op, "GOTO") == 0) {
            printf("    # GOTO\n");
            
            printf("    j _L%d\n", temp->dest->intcon);
        }


        else if(strcmp(temp->op, "LABEL") == 0) {
            printf("    # LABEL\n");

            printf("    _L%d:\n", temp->src1->intcon);
        }


        else if(strcmp(temp->op, "OP_EQ") == 0) {
            printf("    # IF_EQ\n");

            int localSrc1 = checkForVariable(temp->src1->location->name, cur_table);
            int localSrc2 = checkForVariable(temp->src2->location->name, cur_table);
            
            if(localSrc1 == 0 && localSrc2 == 0) {
                printf("    lw $t0, _%s\n", temp->src1->location->name);
                printf("    lw $t1, _%s\n", temp->src2->location->name);
                printf("    beq $t0, $t1, _L%d\n", temp->dest->intcon);
            }

            else if(localSrc1 == 1 && localSrc2 == 0) {
                printf("    lw $t0, %d($fp)\n", temp->src1->location->mips);
                printf("    lw $t1, _%s\n", temp->src2->location->name);
                printf("    beq $t0, $t1, _L%d\n", temp->dest->intcon);
            }

            else if(localSrc1 == 0 && localSrc2 == 1) {
                printf("    lw $t0, _%s\n", temp->src1->location->name);
                printf("    lw $t1, %d($fp)\n", temp->src2->location->mips);
                printf("    beq $t0, $t1, _L%d\n", temp->dest->intcon);
            }

            else if(localSrc1 == 1 && localSrc2 == 1) {
                printf("    lw $t0, %d($fp)\n", temp->src1->location->mips);
                printf("    lw $t1, %d($fp)\n", temp->src2->location->mips);
                printf("    beq $t0, $t1, _L%d\n", temp->dest->intcon);
            }

        }


        else if(strcmp(temp->op, "OP_NE") == 0) {
            printf("    # IF_NE\n");
            
            int localSrc1 = checkForVariable(temp->src1->location->name, cur_table);
            int localSrc2 = checkForVariable(temp->src2->location->name, cur_table);
            
            if(localSrc1 == 0 && localSrc2 == 0) {
                printf("    lw $t0, _%s\n", temp->src1->location->name);
                printf("    lw $t1, _%s\n", temp->src2->location->name);
                printf("    bne $t0, $t1, _L%d\n", temp->dest->intcon);
            }

            else if(localSrc1 == 1 && localSrc2 == 0) {
                printf("    lw $t0, %d($fp)\n", temp->src1->location->mips);
                printf("    lw $t1, _%s\n", temp->src2->location->name);
                printf("    bne $t0, $t1, _L%d\n", temp->dest->intcon);
            }

            else if(localSrc1 == 0 && localSrc2 == 1) {
                printf("    lw $t0, _%s\n", temp->src1->location->name);
                printf("    lw $t1, %d($fp)\n", temp->src2->location->mips);
                printf("    bne $t0, $t1, _L%d\n", temp->dest->intcon);
            }

            else if(localSrc1 == 1 && localSrc2 == 1) {
                printf("    lw $t0, %d($fp)\n", temp->src1->location->mips);
                printf("    lw $t1, %d($fp)\n", temp->src2->location->mips);
                printf("    bne $t0, $t1, _L%d\n", temp->dest->intcon);
            }

        }


        else if(strcmp(temp->op, "OP_LE") == 0) {
            printf("    # IF_LE\n");

            int localSrc1 = checkForVariable(temp->src1->location->name, cur_table);
            int localSrc2 = checkForVariable(temp->src2->location->name, cur_table);
            
            if(localSrc1 == 0 && localSrc2 == 0) {
                printf("    lw $t0, _%s\n", temp->src1->location->name);
                printf("    lw $t1, _%s\n", temp->src2->location->name);
                printf("    ble $t0, $t1, _L%d\n", temp->dest->intcon);
            }

            else if(localSrc1 == 1 && localSrc2 == 0) {
                printf("    lw $t0, %d($fp)\n", temp->src1->location->mips);
                printf("    lw $t1, _%s\n", temp->src2->location->name);
                printf("    ble $t0, $t1, _L%d\n", temp->dest->intcon);
            }

            else if(localSrc1 == 0 && localSrc2 == 1) {
                printf("    lw $t0, _%s\n", temp->src1->location->name);
                printf("    lw $t1, %d($fp)\n", temp->src2->location->mips);
                printf("    ble $t0, $t1, _L%d\n", temp->dest->intcon);
            }

            else if(localSrc1 == 1 && localSrc2 == 1) {
                printf("    lw $t0, %d($fp)\n", temp->src1->location->mips);
                printf("    lw $t1, %d($fp)\n", temp->src2->location->mips);
                printf("    ble $t0, $t1, _L%d\n", temp->dest->intcon);
            }

        }


        else if(strcmp(temp->op, "OP_LT") == 0) {
            printf("    # IF_LT\n");

            int localSrc1 = checkForVariable(temp->src1->location->name, cur_table);
            int localSrc2 = checkForVariable(temp->src2->location->name, cur_table);
            
            if(localSrc1 == 0 && localSrc2 == 0) {
                printf("    lw $t0, _%s\n", temp->src1->location->name);
                printf("    lw $t1, _%s\n", temp->src2->location->name);
                printf("    blt $t0, $t1, _L%d\n", temp->dest->intcon);
            }

            else if(localSrc1 == 1 && localSrc2 == 0) {
                printf("    lw $t0, %d($fp)\n", temp->src1->location->mips);
                printf("    lw $t1, _%s\n", temp->src2->location->name);
                printf("    blt $t0, $t1, _L%d\n", temp->dest->intcon);
            }

            else if(localSrc1 == 0 && localSrc2 == 1) {
                printf("    lw $t0, _%s\n", temp->src1->location->name);
                printf("    lw $t1, %d($fp)\n", temp->src2->location->mips);
                printf("    blt $t0, $t1, _L%d\n", temp->dest->intcon);
            }

            else if(localSrc1 == 1 && localSrc2 == 1) {
                printf("    lw $t0, %d($fp)\n", temp->src1->location->mips);
                printf("    lw $t1, %d($fp)\n", temp->src2->location->mips);
                printf("    blt $t0, $t1, _L%d\n", temp->dest->intcon);
            }
          
        }


        else if(strcmp(temp->op, "OP_GE") == 0) {
            printf("    # IF_GE\n");

            int localSrc1 = checkForVariable(temp->src1->location->name, cur_table);
            int localSrc2 = checkForVariable(temp->src2->location->name, cur_table);
            
            if(localSrc1 == 0 && localSrc2 == 0) {
                printf("    lw $t0, _%s\n", temp->src1->location->name);
                printf("    lw $t1, _%s\n", temp->src2->location->name);
                printf("    bge $t0, $t1, _L%d\n", temp->dest->intcon);
            }

            else if(localSrc1 == 1 && localSrc2 == 0) {
                printf("    lw $t0, %d($fp)\n", temp->src1->location->mips);
                printf("    lw $t1, _%s\n", temp->src2->location->name);
                printf("    bge $t0, $t1, _L%d\n", temp->dest->intcon);
            }

            else if(localSrc1 == 0 && localSrc2 == 1) {
                printf("    lw $t0, _%s\n", temp->src1->location->name);
                printf("    lw $t1, %d($fp)\n", temp->src2->location->mips);
                printf("    bge $t0, $t1, _L%d\n", temp->dest->intcon);
            }

            else if(localSrc1 == 1 && localSrc2 == 1) {
                printf("    lw $t0, %d($fp)\n", temp->src1->location->mips);
                printf("    lw $t1, %d($fp)\n", temp->src2->location->mips);
                printf("    bge $t0, $t1, _L%d\n", temp->dest->intcon);
            }
          
        }


        else if(strcmp(temp->op, "OP_GT") == 0) {
            printf("    # IF_GT\n");

            int localSrc1 = checkForVariable(temp->src1->location->name, cur_table);
            int localSrc2 = checkForVariable(temp->src2->location->name, cur_table);
            
            if(localSrc1 == 0 && localSrc2 == 0) {
                printf("    lw $t0, _%s\n", temp->src1->location->name);
                printf("    lw $t1, _%s\n", temp->src2->location->name);
                printf("    bgt $t0, $t1, _L%d\n", temp->dest->intcon);
            }

            else if(localSrc1 == 1 && localSrc2 == 0) {
                printf("    lw $t0, %d($fp)\n", temp->src1->location->mips);
                printf("    lw $t1, _%s\n", temp->src2->location->name);
                printf("    bgt $t0, $t1, _L%d\n", temp->dest->intcon);
            }

            else if(localSrc1 == 0 && localSrc2 == 1) {
                printf("    lw $t0, _%s\n", temp->src1->location->name);
                printf("    lw $t1, %d($fp)\n", temp->src2->location->mips);
                printf("    bgt $t0, $t1, _L%d\n", temp->dest->intcon);
            }

            else if(localSrc1 == 1 && localSrc2 == 1) {
                printf("    lw $t0, %d($fp)\n", temp->src1->location->mips);
                printf("    lw $t1, %d($fp)\n", temp->src2->location->mips);
                printf("    bgt $t0, $t1, _L%d\n", temp->dest->intcon);
            }
          
        }


        else if(strcmp(temp->op, "ADD") == 0) {
            printf("    # ADD\n");

            int localSrc1 = checkForVariable(temp->src1->location->name, cur_table);
            int localSrc2 = checkForVariable(temp->src2->location->name, cur_table);

            // src1 is local
            if(localSrc1 == 1) {
                printf("    lw $t0, %d($fp)\n", temp->src1->location->mips);
            }
            else {
                printf("    lw $t0, _%s\n", temp->src1->location->name);
            }

            // src2 is local
            if(localSrc2 == 1) {
                printf("    lw $t1, %d($fp)\n", temp->src2->location->mips);
            }
            else {
                printf("    lw $t1, _%s\n", temp->src2->location->name);
            }

            printf("    add $t2, $t0, $t1\n");
            printf("    sw $t2, %d($fp)\n", temp->dest->location->mips);
        }


        else if(strcmp(temp->op, "SUB") == 0) {
            printf("    # SUB\n");

            int localSrc1 = checkForVariable(temp->src1->location->name, cur_table);
            int localSrc2 = checkForVariable(temp->src2->location->name, cur_table);

            // src1 is local
            if(localSrc1 == 1) {
                printf("    lw $t0, %d($fp)\n", temp->src1->location->mips);
            }
            else {
                printf("    lw $t0, _%s\n", temp->src1->location->name);
            }

            // src2 is local
            if(localSrc2 == 1) {
                printf("    lw $t1, %d($fp)\n", temp->src2->location->mips);
            }
            else {
                printf("    lw $t1, _%s\n", temp->src2->location->name);
            }

            printf("    sub $t2, $t0, $t1\n");
            printf("    sw $t2, %d($fp)\n", temp->dest->location->mips);

        }


        else if(strcmp(temp->op, "MUL") == 0) {
            printf("    # MUL\n");

            int localSrc1 = checkForVariable(temp->src1->location->name, cur_table);
            int localSrc2 = checkForVariable(temp->src2->location->name, cur_table);

            // src1 is local
            if(localSrc1 == 1) {
                printf("    lw $t0, %d($fp)\n", temp->src1->location->mips);
            }
            else {
                printf("    lw $t0, _%s\n", temp->src1->location->name);
            }

            // src2 is local
            if(localSrc2 == 1) {
                printf("    lw $t1, %d($fp)\n", temp->src2->location->mips);
            }
            else {
                printf("    lw $t1, _%s\n", temp->src2->location->name);
            }

            printf("    mul $t2, $t0, $t1\n");
            printf("    sw $t2, %d($fp)\n", temp->dest->location->mips);

        }


        else if(strcmp(temp->op, "DIV") == 0) {
            printf("    # DIV\n");

            int localSrc1 = checkForVariable(temp->src1->location->name, cur_table);
            int localSrc2 = checkForVariable(temp->src2->location->name, cur_table);

            // src1 is local
            if(localSrc1 == 1) {
                printf("    lw $t0, %d($fp)\n", temp->src1->location->mips);
            }
            else {
                printf("    lw $t0, _%s\n", temp->src1->location->name);
            }

            // src2 is local
            if(localSrc2 == 1) {
                printf("    lw $t1, %d($fp)\n", temp->src2->location->mips);
            }
            else {
                printf("    lw $t1, _%s\n", temp->src2->location->name);
            }

            printf("    div $t2, $t0, $t1\n");
            printf("    sw $t2, %d($fp)\n", temp->dest->location->mips);
        }


        else if(strcmp(temp->op, "UMINUS") == 0) {
            printf("    # UMINUS\n");
            
            int localSrc1 = checkForVariable(temp->src1->location->name, cur_table);

            if(localSrc1 == 1) {
                printf("    lw $t0, %d($fp)\n", temp->src1->location->mips);
            }
            else {
                printf("    lw $t0, _%s\n", temp->src1->location->name);
            }

            printf("    neg $t1, $t0\n");
            printf("    sw $t1, %d($fp)\n", temp->dest->location->mips);

        }


        else if(strcmp(temp->op, "RETURN") == 0) {
            printf("    # RETURN\n");
            
            if(temp->src1 != NULL) {
                int localSrc = checkForVariable(temp->src1->location->name, cur_table);
                if(localSrc == 1) {
                    printf("    lw $v0, %d($fp)\n\n", temp->src1->location->mips);
                }
                else {
                    printf("    lw $v0, _%s\n\n", temp->src1->location->name);
                }
                
            }
            printf("    la $sp, 0($fp)\n");
            printf("    lw $ra, 0($sp)\n");
            printf("    lw $fp, 4($sp)\n");
            printf("    la $sp, 8($sp)\n");
            printf("    jr $ra\n");
            //printf("\n");
        }


        else if(strcmp(temp->op, "RETRIEVE") == 0) {
            printf("    # RETRIEVE\n");
            printf("    move $t0, $v0\n");

            int localSrc = checkForVariable(temp->dest->location->name, cur_table);
            if(localSrc == 1) {
                printf("    sw $t0, %d($fp)\n", temp->dest->location->mips);
            }
            else {
                printf("    sw $t0, _%s\n", temp->dest->location->name);
            }
        }


        else if(strcmp(temp->op, "LEAVE") == 0) {
            printf("    # LEAVE\n");
            printf("    la $sp, 0($fp)\n");
            printf("    lw $ra, 0($sp)\n");
            printf("    lw $fp, 4($sp)\n");
            printf("    la $sp, 8($sp)\n");
            printf("    jr $ra\n");
        }

        printf("\n");
        temp = temp->next;
    }

}


int printed = 0;
void func_or_decl() {
    if(vars == 1) {
        vars = 0;
        // Check and put variable in table
        checkInTable();
        match(SEMI);
    }

    else if(cur_token == LPAREN) {
        // Check if function already in table
        int errorVal = checkForVariable(cur_variable, cur_table);
        save_var = strdup(cur_variable);
        
        struct node* start = makeEmptyNode(cur_variable, FUNC_DEF);
        curNode = start;
        
        if(chk_decl_flag == 1) {
            if(errorVal == 1) {
                fprintf(stderr, "ERROR on LINE %d, func_or_decl exit status = 1\n", line);
                exit(1);
            }
            else {
                addVariable(cur_variable, "func", &cur_table->symbolTables);
                struct table* getTable = getTableEntry(cur_variable, cur_table); // Get func location
                start->location = getTable; // Set location
            }
        }
        else {
            // Put the variable in the table
            addVariable(cur_variable, "func", &cur_table->symbolTables);
            struct table* getTable = getTableEntry(cur_variable, cur_table); // Get func location
            start->location = getTable; // Set location
        }        

        // Put println in the symbol table
        addVariable("println", "func", &cur_table->symbolTables);
        struct table* printFunc = getTableEntry("println", cur_table);
        printFunc->params = 1;

        match(LPAREN);
        cur_table = cur_table->down; // Change to local table
        count_formals = 0; // Initialize number of formals

        opt_formals(); // Put in stmt list
        match(RPAREN);
        addFuncCount(save_var, count_formals, cur_table->up); // Add count params
        start->numParams = count_formals; // Set number of formals

        match(LBRACE);
        opt_var_decls();

        struct node* body = opt_stmt_list(); // Needs tree node

        start->childOne = body;
        match(RBRACE);

        if(print_ast_flag == 1) {
            print_ast(start);
        }
        if(gen_code_flag == 1) {
            struct quad* linkedList = traverse(start, 0, 0);
            //print(linkedList);
            if(printed == 0) {
                printlnFunc();
                printed = 1;
            }
            printMips(linkedList);
        }

        popVariable(cur_table); // Pop the table
        cur_table = cur_table->up; // Change to global table
    }

    else {
        // Check and put variable in table
        checkInTable();
        match(SEMI);
    }
}


void prog() {
    if(cur_token == kwINT) {
        type();
        id_list();
        func_or_decl();
        prog();
    }

    else {
        return;
    }
}


/*
 * Start at parse to parse the input string.
 * Calls prog() to start matching the input
*/
int parse() {
    // Get first token
    cur_token = get_token();

    // Make empty global and local tables
    cur_table = malloc(sizeof(struct stack));
    cur_table->up = NULL;
    cur_table->down = NULL;
    cur_table->symbolTables = NULL;

    local_table = malloc(sizeof(struct stack));
    local_table->up = cur_table;
    local_table->down = NULL;
    local_table->symbolTables = NULL;
    
    cur_table->down = local_table;

    // Make empty tree
    root = NULL;
    curNode = root;

    newLabel = makeNewLabel();

    prog();
    // Match EOF before returning
    match(EOF);
    if (gen_code_flag){
        printf("\n");
        printGlobals();
        printf("\n");
        printf("\n# Call to main\n");
        printf(".text\n");
        printf("main: j _main\n");
    }
    return 0;
}