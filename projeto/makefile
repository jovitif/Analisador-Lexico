# Compiladores
CC=g++
LEX=flex++

# Dependências
all: test

test: lex.yy.cc
	$(CC) lex.yy.cc -std=c++17 -o analisador-lexico

lex.yy.cc: analisador.l
	$(LEX) analisador.l

clean:
	rm test lex.yy.cc