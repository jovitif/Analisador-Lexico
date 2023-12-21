%{
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


unsigned charCount = 0, wordCount = 0, lineCount = 0;

vector<string> palavrasReservadas,classes,simbolosEspeciais,individuos,propriedades,tiposDeDados,cardinalidades;

void escreverCsv(vector<string> vector,ofstream& fout){
    int size = vector.size();

    for(int i = 0;i < size;i++){
        fout << vector[i] << " ;";
    }

    fout << endl;
}
%}

%option noyywrap
classe [A-Z][a-zA-Z_]*
individuo [A-Z][a-zA-Z0-9_]*[0-9]+
eol  \n
reservada (some|all|value|min|max|exactly|that|not|and|only|or|Class:|EquivalentTo:|Individuals:|SubClassOf:|DisjointClasses:)
especial ("{"|"}"|"("|")"|"["|"]"|","|"<"|">"|"=")
propriedade  [a-z][A-Za-z0-9]*
tipoDado (owl|rdfs|xsd):[A-Za-z0-9_]+
cardinalidade [0-9]+




%%
{reservada} {
	palavrasReservadas.push_back(yytext);
    wordCount++; charCount += YYLeng();
}


{classe} {
    classes.push_back(yytext);
    wordCount++; charCount += YYLeng(); 
}



{especial} {
    simbolosEspeciais.push_back(yytext);
    charCount++;
}

{propriedade} {
    propriedades.push_back(yytext);
    wordCount++; charCount += YYLeng(); 
}



{individuo} {
    individuos.push_back(yytext);
    wordCount++; charCount += YYLeng(); 
}

{tipoDado} {
    tiposDeDados.push_back(yytext);
    wordCount++; charCount += YYLeng(); 
}

{cardinalidade} {
    cardinalidades.push_back(yytext);
    wordCount++; charCount += YYLeng(); 
}


{eol}	{ lineCount++; }

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

    
    
    fin.close();

    ofstream fout("saida.csv", ios::out | ios::trunc);

    
    if (fout.is_open()) {
        fout << "Palavras reservadas;";
        escreverCsv(palavrasReservadas,fout);
        fout << "Classes;";
        escreverCsv(classes,fout);
        fout << "Indivíduos;";
        escreverCsv(individuos,fout);
        fout << "Propriedades;";
        escreverCsv(propriedades,fout);
        fout << "Tipos de dados;";
        escreverCsv(tiposDeDados,fout);
        fout << "Cardinalidades;";
        escreverCsv(cardinalidades,fout);
        fout << "Símbolos especiais;";
        escreverCsv(simbolosEspeciais,fout);
        fout << left <<   "Quantidade de linhas;" << lineCount+1 << "\n"
         << left <<   "Quantidade de palavras;" << wordCount << "\n"
         << left <<   "Quantidade de letras;" << charCount << "\n"
         << left <<   "Quantidade de palavras reservadas;" << palavrasReservadas.size() << "\n"
         << left <<   "Quantidade de Símbolos especiais;" << simbolosEspeciais.size() << "\n"
         << left <<   "Quantidade de Classes;" << classes.size() << "\n"
         << left <<   "Quantidade de Indivíduos;" << individuos.size() << "\n"
         << left <<   "Quantidade de Propriedades;" << propriedades.size() << "\n"
         << left <<   "Quantidade de tipos de dados;" << tiposDeDados.size() << "\n"
         << left <<   "Quantidade de cardinalidades;" << cardinalidades.size() << "\n";

        fout.close();
        cout << "As informações foram salvas em saida.csv.\n";
    } else {
        cout << "Não foi possível gerar ou abrir o arquivo saida.csv.\n";
    }

    return 0;
}