%{
#include <iostream>
#include <fstream>
#include <iomanip>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;
unsigned charCount = 0, wordCount = 0, lineCount = 0, palavrasReservadas = 0, identificadoresClasses = 0, identificadoresEspeciais = 0, identificadoresIndividuos = 0, identificadorPropriedades = 0, identificadorTipoDados = 0, identificadoresCardinalidade = 0;
%}

%option noyywrap
classe [ \t]*[A-Z][a-zA-Z_]*
individuo [ \t]*[A-Z][a-zA-Z0-9_]*[0-9]+
letterMa [A-Z]+
letterMi [a-z]+
letter [A-Za-z]+
noLetter [^A-Za-z]
digito	[0-9]+
underline [_]
word [^ \t\n]+
eol  \n
reservada [ \t\n]*(some|all|value|min|max|exactly|that|not|and|or|Class:|EquivalentTo:|Individuals:|SubClassOf:|DisjointClasses:)
especial [ \t\n]*("{"|"}"|"("|")"|"["|"]"|","|"<"|">")
propriedade  [ \t\n]*[a-z][A-Za-z0-9]*
tipoDado [ \t](owl|rdfs|xsd):[A-Za-z0-9_]+
cardinalidade [ \t\n]*[0-9]+




%%
{reservada} {
    std::cout << "Palavra Reservada: " << yytext << std::endl;
    palavrasReservadas++;
    wordCount++; charCount += YYLeng(); 
}


{classe} {
	cout<< "Classe: " << yytext << std::endl;
	identificadoresClasses++;
    wordCount++; charCount += YYLeng(); 
}



{especial} {
    std::cout << "Simbolo Especial: " << yytext << std::endl;
    identificadoresEspeciais++;
    charCount++;
}

{propriedade} {
	std::cout << "Propriedade: " << yytext << std::endl;
	identificadorPropriedades++;
    wordCount++; charCount += YYLeng(); 
}



{individuo} {
	cout << "Individuo: " << yytext << std::endl;
	identificadoresIndividuos++;
    wordCount++; charCount += YYLeng(); 
}

{tipoDado} {
	cout << "Tipo de Dados: " << yytext << std::endl;
	identificadorTipoDados++;
    wordCount++; charCount += YYLeng(); 
}

{cardinalidade} {
	std::cout << "Cardinalidade: " << yytext << std::endl;
    identificadoresCardinalidade++;
    wordCount++; charCount += YYLeng(); 
}


{eol}	{ lineCount++; }
{word}	{ charCount++; }



%%

int main(int argc, char** argv) {
    yyFlexLexer lexer;
    ifstream fin;

    if (argc > 1) {
        fin.open(argv[1]);
        if (!fin.is_open()) {
            cout << "Arquivo " << argv[1] << " não pode ser aberto!\n";
            exit(EXIT_FAILURE);
        } else {
            lexer.switch_streams(&fin);
        }
    }

    lexer.yylex();
    cout << "Gerando tabela de informações...\n\n"
         << left << setw(50) << "Quantidade de linhas:" << lineCount << "\n"
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

    // Salvar as informações no arquivo output.txt
    ofstream fout("output.txt", ios::out | ios::trunc);
    if (fout.is_open()) {
        fout << left << setw(50) << "Quantidade de linhas:" << lineCount << "\n"
             << left << setw(50) << "Quantidade de palavras:" << wordCount << "\n"
             << left << setw(50) << "Quantidade de letras:" << charCount << "\n"
             << left << setw(50) << "Quantidade de palavras reservadas:" << palavrasReservadas << "\n"
             << left << setw(50) << "Quantidade de Símbolos especiais:" << identificadoresEspeciais << "\n"
             << left << setw(50) << "Quantidade de Classes:" << identificadoresClasses << "\n"
             << left << setw(50) << "Quantidade de Indivíduos:" << identificadoresIndividuos << "\n"
             << left << setw(50) << "Quantidade de Propriedades:" << identificadorPropriedades << "\n"
             << left << setw(50) << "Quantidade de tipos de dados:" << identificadorTipoDados << "\n"
             << left << setw(50) << "Quantidade de cardinalidades:" << identificadoresCardinalidade << "\n";
        fout.close();
        cout << "As informações foram salvas em output.txt.\n";
    } else {
        cout << "Não foi possível criar ou abrir o arquivo output.txt.\n";
    }

    return 0;
}