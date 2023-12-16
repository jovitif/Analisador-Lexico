# Compiladores
CC=g++
LEX=flex++

# Dependências
all: test

test: lex.yy.cc
	$(CC) lex.yy.cc -std=c++17 -o test

lex.yy.cc: test.l
	$(LEX) test.l

clean:
	rm test lex.yy.cc