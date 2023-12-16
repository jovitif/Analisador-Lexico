%{
// Faz contagem de caracteres, palavras e linhas de um arquivo
#include <iostream>
#include <fstream>
#include <iomanip>  
using namespace std;

unsigned charCount = 0, wordCount = 0, lineCount = 0, palavrasReservadas = 0, identificadoresClasses = 0, identificadoresEspeciais = 0,identificadoresIndividuos =0, identificadorPropriedades=0, identificadorTipoDados=0, identificadoresCardinalidade = 0;
%}

%option noyywrap
classe [ \t]*[A-Z][a-zA-Z_]*
individuo [ \t]*[A-Z][a-zA-Z0-9_]*[0-9]*
letterMa [A-Z]+
letterMi [a-z]+
letter [A-Za-z]+
noLetter [^A-Za-z]
digito	[0-9]+
underline [_]
word [^ \t\n]+
eol  \n
reservada (some|all|value|min|max|exactly|that|not|and|or|Class:|EquivalentTo:|Individuals:|SubClassOf:|DisjointClasses:)
especial ("{"|"}"|"("|")"|"["|"]"|",")
propriedade has[A-Za-z0-9_]+|is[A-Za-z0-9_]+Of|[a-z][A-Za-z0-9_]*
tipoDado [ \t](owl|rdfs|xsd):[A-Za-z0-9_]+
cardinalidade [0-9]+


%%

{classe} {
	std::cout << "Classe: " << yytext << std::endl;
	identificadoresClasses++;
}

{tipoDado} {
	std::cout << "Tipo de Dados: " << yytext << std::endl;
	identificadorTipoDados++;
}

{individuo} {
	std::cout << "Individuo: " << yytext << std::endl;
	identificadoresIndividuos++;
}

{propriedade} {
	std::cout << "Propriedade: " << yytext << std::endl;
	identificadorPropriedades++;
}

{reservada} {
    std::cout << "Palavra Reservada: " << yytext << std::endl;
    palavrasReservadas++;
}

{especial} {
    std::cout << "Simbolo Especial: " << yytext << std::endl;
    identificadoresEspeciais++;
}

{cardinalidade} {
	std::cout << "Cardinalidade: " << yytext << std::endl;
    identificadoresCardinalidade++;
}

{word}	{ wordCount++; charCount += YYLeng(); }
{eol}	{ charCount++; lineCount++; }
.	    { charCount++; }

%%

int main(int argc, char ** argv)
{
	yyFlexLexer lexer;  // lexer lê da entrada padrão (teclado)
	ifstream fin;

	if (argc > 1) 
	{    
		fin.open(argv[1]);
		if (!fin.is_open()) 
        {
			cout << "Arquivo " << argv[1] << " não pode ser aberto!\n";
			exit(EXIT_FAILURE);
		}
		else
		{
			// altera entrada para arquivo aberto
			lexer.switch_streams(&fin);
		}
	}

	lexer.yylex();
 	cout << "Gerando tabela de informações...\n\n";
    cout << left << setw(50) << "Quantidade de linhas:" << lineCount << "\n"
         << left << setw(50) << "Quantidade de palavras:" << wordCount << "\n"
         << left << setw(50) << "Quantidade de letras:" << charCount << "\n"
         << left << setw(50) << "Quantidade de palavras reservadas:" << palavrasReservadas << "\n"
         << left << setw(50) << "Quantidade de Símbolos especiais:" << identificadoresEspeciais << "\n"
         << left << setw(50) << "Quantidade de Classes:" << identificadoresClasses << "\n"
         << left << setw(50) << "Quantidade de Indivíduos:" << identificadoresIndividuos << "\n"
         << left << setw(50) << "Quantidade de Propriedades:" << identificadorPropriedades << "\n"
         << left << setw(50) << "Quantidade de tipos de dados:" << identificadorTipoDados << "\n"
         << left << setw(50) << "Quantidade de cardinalidades:" << identificadoresCardinalidade << "\n";
	fin.close();
	return 0;
}
