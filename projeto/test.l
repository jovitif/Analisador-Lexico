%{
// Exemplo de reconhecimento de números e texto 
#include <iostream>
using std::cout;
%}

%option noyywrap

%%
[ \t\n]+                                            ; // ignora espaços em branco
num [+-]?(([0-9]+)|([0-9]*\.[0-9]+)([eE][-+]?[0-9]+)?) 
letraMin [a-z] 
.+                                                  cout << "texto\n";
%%

int main()
{
    yyFlexLexer lexer;
	lexer.yylex();
}