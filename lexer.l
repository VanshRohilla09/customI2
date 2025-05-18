%{
#include <stdio.h>
#include "ast.h"
#include "parser.tab.h"
%}

%option noyywrap
%option yylineno

%%
[0-9]+          { yylval.num = atoi(yytext); return NUMBER; }
[a-zA-Z][a-zA-Z0-9]* { yylval.str = strdup(yytext); return IDENTIFIER; }
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return TIMES; }
"/"             { return DIVIDE; }
"="             { return ASSIGN; }
";"             { return SEMICOLON; }
[ \t\n\r]       ; // Ignore whitespace and carriage returns
.               { fprintf(stderr, "Unknown character '%s' at line %d\n", yytext, yylineno); }
%%