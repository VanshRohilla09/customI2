#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"

symbol *table = NULL;

void init_symbol_table() {
    table = NULL;
}

int get_symbol(char *name) {
    symbol *s = table;
    while (s) {
        if (strcmp(s->name, name) == 0) return s->value;
        s = s->next;
    }
    return 0; // Default value if not found
}

void set_symbol(char *name, int value) {
    symbol *s = table;
    while (s) {
        if (strcmp(s->name, name) == 0) {
            s->value = value;
            return;
        }
        s = s->next;
    }
    s = malloc(sizeof(symbol));
    s->name = strdup(name);
    s->value = value;
    s->next = table;
    table = s;
}

void free_symbol_table() {
    symbol *s = table;
    while (s) {
        symbol *next = s->next;
        free(s->name);
        free(s);
        s = next;
    }
    table = NULL;
}