# Compiler
CC = g++
CFLAGS = -c -Wall 

all: evaluator

evaluator: parser.o lexer.o ast.o
	$(CC) parser.o lexer.o ast.o -o evaluator

parser.o: parser.cpp
	$(CC) $(CFLAGS) parser.cpp

lexer.o: lexer.cpp
	$(CC) $(CFLAGS) lexer.cpp

ast.o: ast.cpp
	$(CC) $(CFLAGS) ast.cpp

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -rf *.o