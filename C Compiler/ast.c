#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include<assert.h>
#include "ast.h"
#include "AST_node.h"
#include "symbol_table.h"


NodeType ast_node_type(void *ptr) {
    struct node* ast = ptr;
    assert(ast != NULL);
    return ast->type;
}


char* func_def_name(void *ptr) {
    struct node* ast = ptr;
    assert(ast != NULL);
    return ast->name;
}


int func_def_nargs(void *ptr) {
    struct node* ast = ptr;
    assert(ast != NULL);
    return ast->numParams;
}


// Return name of nth param //
char* func_def_argname(void *ptr, int n) {
    int i;
    
    struct node* ast = ptr;
    assert(ast != NULL);

    struct node* stmts = ast->stmts;
    for(i = 1; i < n; i++) {
        stmts = stmts->next;
    }
    return stmts->location->name;
}


void * func_def_body(void *ptr) {
    struct node* ast = ptr;
    assert(ast != NULL);
    return ast->childOne;
}


char * func_call_callee(void *ptr) {
    struct node* ast = ptr;
    assert(ast != NULL);
    return ast->name;
}


void * func_call_args(void *ptr) {
    struct node* ast = ptr;
    assert(ast != NULL);
    return ast->childOne;
}


void * stmt_list_head(void *ptr) {
    struct node* ast = ptr;
    assert(ast != NULL);
    return ast->childOne;
    // if(ast->type == STMT_LIST) {
    //     return ast->childOne;
    // }
    // return ast;
}


void * stmt_list_rest(void *ptr) {
    struct node* ast = ptr;
    assert(ast != NULL);

    return ast->next;

    // if(ast->type == STMT_LIST && ast->next != NULL) {
    //     return ast->next->next;
    // }
    // return ast->next;
}


void * expr_list_head(void *ptr) {
    struct node* ast = ptr;
    assert(ast != NULL);
    return ast->childOne;
}


void * expr_list_rest(void *ptr) {
    struct node* ast = ptr;
    assert(ast != NULL);
    return ast->next;
}


char *expr_id_name(void *ptr) {
    struct node* ast = ptr;
    assert(ast != NULL);
    return ast->name;
}


int expr_intconst_val(void *ptr) {
    struct node* ast = ptr;
    assert(ast != NULL);
    return ast->val;
}


void * expr_operand_1(void *ptr) {
    struct node* ast = ptr;
    assert(ast != NULL);
    return ast->childOne;
}


void * expr_operand_2(void *ptr) {
    struct node* ast = ptr;
    assert(ast != NULL);
    return ast->childTwo;
}


void * stmt_if_expr(void *ptr) {
    struct node* ast = ptr;
    assert(ast != NULL);
    return ast->childOne;
}


void * stmt_if_then(void *ptr) {
    struct node* ast = ptr;
    assert(ast != NULL);
    return ast->childTwo;
}


void * stmt_if_else(void *ptr) {
    struct node* ast = ptr;
    assert(ast != NULL);
    return ast->childThree;
}


char *stmt_assg_lhs(void *ptr) {
    struct node* ast = ptr;
    assert(ast != NULL);
    return ast->childOne->name;
}


void *stmt_assg_rhs(void *ptr) {
    struct node* ast = ptr;
    assert(ast != NULL);
    return ast->childTwo;
}


void *stmt_while_expr(void *ptr) {
    struct node* ast = ptr;
    assert(ast != NULL);
    return ast->childOne;
}


void *stmt_while_body(void *ptr) {
    struct node* ast = ptr;
    assert(ast != NULL);
    return ast->childTwo;
}


void *stmt_return_expr(void *ptr) {
    struct node* ast = ptr;
    assert(ast != NULL);
    return ast->childOne;
}


