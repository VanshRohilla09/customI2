# Makefile for building the interpreter
CC = gcc
CFLAGS = -Wall -g
FLEX = flex
BISON = bison

# Target executable
TARGET = mylang

# Source files
SOURCES = main.c ast.c symbol_table.c interpreter.c
OBJECTS = $(SOURCES:.c=.o) lex.yy.c parser.tab.c

all: $(TARGET)

# Generate lexer and parser
lex.yy.c: lexer.l
	$(FLEX) lexer.l

parser.tab.c parser.tab.h: parser.y
	$(BISON) -d parser.y

# Compile and link
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) -lfl

# Object file dependencies
main.o: main.c ast.h symbol_table.h interpreter.h parser.tab.h
ast.o: ast.c ast.h
symbol_table.o: symbol_table.c symbol_table.h
interpreter.o: interpreter.c interpreter.h ast.h symbol_table.h
lex.yy.o: lex.yy.c parser.tab.h
parser.tab.o: parser.tab.c ast.h

# Clean up
clean:
	rm -f $(OBJECTS) $(TARGET) lex.yy.c parser.tab.c parser.tab.h

.PHONY: all clean