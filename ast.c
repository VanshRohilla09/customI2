#include <stdlib.h>
#include <string.h>
#include "ast.h"

ast_node *create_number(int value) {
    ast_node *node = malloc(sizeof(ast_node));
    node->type = AST_NUMBER;
    node->data.number = value;
    return node;
}

ast_node *create_var(char *name) {
    ast_node *node = malloc(sizeof(ast_node));
    node->type = AST_VAR;
    node->data.var = strdup(name);
    return node;
}

ast_node *create_assign(char *name, ast_node *expr) {
    ast_node *node = malloc(sizeof(ast_node));
    node->type = AST_ASSIGN;
    node->data.assign.name = strdup(name);
    node->data.assign.expr = expr;
    return node;
}

ast_node *create_binop(ast_type type, ast_node *left, ast_node *right) {
    ast_node *node = malloc(sizeof(ast_node));
    node->type = type;
    node->data.binop.left = left;
    node->data.binop.right = right;
    return node;
}

void free_ast(ast_node *node) {
    if (!node) return;
    switch (node->type) {
        case AST_NUMBER:
            break;
        case AST_VAR:
            free(node->data.var);
            break;
        case AST_ASSIGN:
            free(node->data.assign.name);
            free_ast(node->data.assign.expr);
            break;
        case AST_PLUS:
        case AST_MINUS:
        case AST_TIMES:
        case AST_DIVIDE:
        case AST_STMT_LIST:
            free_ast(node->data.binop.left);
            free_ast(node->data.binop.right);
            break;
    }
    free(node);
}