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

void identifyReservedWords(const string& text) {
    Automato estado = INICIAL;
    string currentWord;

    for (char c : text) {
        switch (estado) {
            case INICIAL:
                if (isalpha(c)) {
                    currentWord += c;
                    estado = IN_PALAVRA;
                } else if (isdigit(c)) {
                    estado = IN_DIGITO;
                }
                break;

            case IN_PALAVRA:
                if (isalnum(c) || c == '_') {
                    currentWord += c;
                } else {
                    if (isPalavraReservada(currentWord)) {
                        cout << "<" << currentWord << ", Palavra reservada>" << endl;
                    } else if (isClasse(currentWord)) {
                        cout << "<" << currentWord << ", Classe>" << endl;
                    } else if (isIdentificadorPropriedade(currentWord)) {
                        cout << "<" << currentWord << ", Propriedade>" << endl;
                    }
                    currentWord.clear();
                    estado = INICIAL;
                    if (isalpha(c)) {
                        currentWord += c;
                        estado = IN_PALAVRA;
                    } else if (isdigit(c)) {
                        estado = IN_DIGITO;
                    }
                }
                break;

            case IN_DIGITO:
                if (!isdigit(c)) {
                    estado = INICIAL;
                    if (isalpha(c)) {
                        currentWord += c;
                        estado = IN_PALAVRA;
                    }
                }
                break;
        }
    }

    if (!currentWord.empty()) {
        if (isPalavraReservada(currentWord)) {
            cout << "<" << currentWord << ", >" << endl;
        } else if (isClasse(currentWord)) {
            cout << "<" << currentWord << ", CLASS>" << endl;
        } else if (isIdentificadorPropriedade(currentWord)) {
            cout << "<" << currentWord << ", PROPERTY>" << endl;
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

