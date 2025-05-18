#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef struct symbol {
    char *name;
    int value;
    struct symbol *next;
} symbol;

void init_symbol_table();
int get_symbol(char *name);
void set_symbol(char *name, int value);
void free_symbol_table();

#endif