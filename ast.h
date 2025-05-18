#ifndef AST_H
#define AST_H

typedef enum {
    AST_NUMBER,
    AST_VAR,
    AST_ASSIGN,
    AST_PLUS,
    AST_MINUS,
    AST_TIMES,
    AST_DIVIDE,
    AST_STMT_LIST
} ast_type;

typedef struct ast_node {
    ast_type type;
    union {
        int number;                // For AST_NUMBER
        char *var;                 // For AST_VAR
        struct {                   // For AST_ASSIGN
            char *name;
            struct ast_node *expr;
        } assign;
        struct {                   // For binary operations and stmt_list
            struct ast_node *left;
            struct ast_node *right;
        } binop;
    } data;
} ast_node;

ast_node *create_number(int value);
ast_node *create_var(char *name);
ast_node *create_assign(char *name, ast_node *expr);
ast_node *create_binop(ast_type type, ast_node *left, ast_node *right);
void free_ast(ast_node *node);

#endif