%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "symbol_table.h"
#include "interpreter.h"

extern int yylex();
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
%}

%union {
    int num;
    char *str;
    struct ast_node *node;
}

%token <num> NUMBER
%token <str> IDENTIFIER
%token PLUS MINUS TIMES DIVIDE ASSIGN SEMICOLON

%type <node> expr statement stmt_list

%left PLUS MINUS
%left TIMES DIVIDE

%%

program: stmt_list { interpret($1); free_ast($1); }

stmt_list: statement { $$ = $1; }
         | stmt_list statement { $$ = create_binop(AST_STMT_LIST, $1, $2); }

statement: IDENTIFIER ASSIGN expr SEMICOLON { $$ = create_assign($1, $3); free($1); }
         | expr SEMICOLON { $$ = $1; }

expr: NUMBER { $$ = create_number($1); }
    | IDENTIFIER { $$ = create_var($1); free($1); }
    | expr PLUS expr { $$ = create_binop(AST_PLUS, $1, $3); }
    | expr MINUS expr { $$ = create_binop(AST_MINUS, $1, $3); }
    | expr TIMES expr { $$ = create_binop(AST_TIMES, $1, $3); }
    | expr DIVIDE expr { $$ = create_binop(AST_DIVIDE, $1, $3); }
    ;

%%
