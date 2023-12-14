#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

enum Automato {
    INICIAL, IN_PALAVRA, IN_DIGITO
};

bool isPalavraReservada(const string& palavra) {
    vector<string> palavrasReservadas = {"SOME", "ALL", "VALUE", "MIN", "MAX", "ONLY", "EXACTLY", "THAT", "NOT", "AND", "OR"};
    return find(palavrasReservadas.begin(), palavrasReservadas.end(), palavra) != palavrasReservadas.end();
}

bool isClasse(const string& palavra) {
    if (isupper(palavra[0])) {
        if (all_of(palavra.begin() + 1, palavra.end(), [](char c) { return isalnum(c) || c == '_'; })) {
            return true;
        }
    }
    return false;
}

bool isIdentificadorPropriedade(const string& palavra) {
    // Verifica se o identificador de propriedade segue as regras fornecidas
    if (palavra.compare(0, 3, "has") == 0 && isupper(palavra[3])) {
        return true;
    } else if (palavra.compare(0, 2, "is") == 0 && palavra.compare(palavra.length() - 2, 2, "Of") == 0) {
        return true;
    }
    return false;
}

void identifyReservedWords(const string& texto) {
    Automato estado = INICIAL;
    string palavra;

    for (char letra : texto) {
        switch (estado) {
            case INICIAL:
                if (isalpha(letra)) {
                    palavra += letra;
                    estado = IN_PALAVRA;
                } else if (isdigit(letra)) {
                    estado = IN_DIGITO;
                }
                break;

            case IN_PALAVRA:
                if (isalnum(letra) || letra == '_') {
                    palavra += letra;
                } else {
                    if (isPalavraReservada(palavra)) {
                        cout << "<" << palavra << ", Palavra reservada>" << endl;
                    } else if (isClasse(palavra)) {
                        cout << "<" << palavra << ", Classe>" << endl;
                    } else if (isIdentificadorPropriedade(palavra)) {
                        cout << "<" << palavra << ", Propriedade>" << endl;
                    }
                    palavra.clear();
                    estado = INICIAL;
                    if (isalpha(letra)) {
                        palavra += letra;
                        estado = IN_PALAVRA;
                    } else if (isdigit(letra)) {
                        estado = IN_DIGITO;
                    }
                }
                break;

            case IN_DIGITO:
                if (!isdigit(letra)) {
                    estado = INICIAL;
                    if (isalpha(letra)) {
                        palavra += letra;
                        estado = IN_PALAVRA;
                    }
                }
                break;
        }
    }

    if (!palavra.empty()) {
        if (isPalavraReservada(palavra)) {
            cout << "<" << palavra << ", >" << endl;
        } else if (isClasse(palavra)) {
            cout << "<" << palavra << ", CLASS>" << endl;
        } else if (isIdentificadorPropriedade(palavra)) {
            cout << "<" << palavra << ", PROPERTY>" << endl;
        }
    }
}

string lerArquivo(const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        exit(EXIT_FAILURE);
    }

    stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}

int main() {
    const char arquivo[] = "entrada/test01.txt";
    string texto = lerArquivo(arquivo);

    identifyReservedWords(texto);

    return 0;
}

