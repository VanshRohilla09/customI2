#include <stdio.h>
#include "ast.h"
#include "symbol_table.h"
#include "interpreter.h"
#include "parser.tab.h"

extern FILE *yyin;

int main(int argc, char *argv[]) {
    init_symbol_table();
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            fprintf(stderr, "Cannot open file %s\n", argv[1]);
            return 1;
        }
    } else {
        yyin = fopen("examples/sample_code.txt", "r");
        if (!yyin) {
            fprintf(stderr, "Cannot open sample_code.txt\n");
            return 1;
        }
    }
    yyparse();
    fclose(yyin);
    free_symbol_table();
    return 0;
}