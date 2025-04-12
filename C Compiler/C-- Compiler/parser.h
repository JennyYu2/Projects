#ifndef __PARSER__
#define __PARSER__

#include "scanner.h"

void checkInTable();
void match(Token expected);
void type();
void id_check();
void id_list();
void var_decl();
void more_formals();
void opt_var_decls();
void opt_formals();
struct node* arith_exp();
struct node* arith_exp2();
struct node* arith_op();
void opt_arith_op();
struct node* more_expr_list();
struct node* fn_call_or_assg();
struct node* relop();
struct node* bool_exp();
struct node* bool_exp2();
struct node* bool_exp3();
struct node* while_stmt();
struct node* opt_if_stmt();
struct node* if_stmt() ;
struct node* opt_return();
struct node* return_stmt();
void fn_call();
struct node* stmt();
struct node* opt_stmt_list();
void formals();
struct node* expr_list();
struct node* opt_expr_list();
void func_or_decl();
void prog();
int parse();
struct node* makeParamExprList(struct node* params);

#endif