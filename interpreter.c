#include <stdio.h>
#include <stdlib.h>
#include "interpreter.h"
#include "symbol_table.h"

int eval(ast_node *node) {
    if (!node) {
        fprintf(stderr, "Null AST node\n");
        return 0;
    }
    switch (node->type) {
        case AST_NUMBER:
            return node->data.number;
        case AST_VAR:
            return get_symbol(node->data.var);
        case AST_ASSIGN:
            set_symbol(node->data.assign.name, eval(node->data.assign.expr));
            return 0;
        case AST_PLUS:
            return eval(node->data.binop.left) + eval(node->data.binop.right);
        case AST_MINUS:
            return eval(node->data.binop.left) - eval(node->data.binop.right);
        case AST_TIMES:
            return eval(node->data.binop.left) * eval(node->data.binop.right);
        case AST_DIVIDE:
            {
                int right = eval(node->data.binop.right);
                if (right == 0) {
                    fprintf(stderr, "Division by zero\n");
                    exit(1);
                }
                return eval(node->data.binop.left) / right;
            }
        case AST_STMT_LIST:
            eval(node->data.binop.left);
            return eval(node->data.binop.right); // Return result of last statement
        default:
            fprintf(stderr, "Unknown AST node type %d\n", node->type);
            exit(1);
    }
}

void interpret(ast_node *node) {
    int result = eval(node);
    if (node->type != AST_ASSIGN && node->type != AST_STMT_LIST) {
        printf("Result: %d\n", result);
    } else if (node->type == AST_STMT_LIST && result != 0) {
        printf("Result: %d\n", result);
    }
}