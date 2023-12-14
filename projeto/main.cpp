#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

enum State {
    START, IN_WORD, IN_DIGIT
};

bool isReservedWord(const string& word) {
    vector<string> reservedWords = {"SOME", "ALL", "VALUE", "MIN", "MAX", "ONLY", "EXACTLY", "THAT", "NOT", "AND", "OR"};
    return find(reservedWords.begin(), reservedWords.end(), word) != reservedWords.end();
}

bool isClassIdentifier(const string& word) {
    // Verifica se o identificador de classe segue as regras fornecidas
    if (isupper(word[0])) {
        if (all_of(word.begin() + 1, word.end(), [](char c) { return isalnum(c) || c == '_'; })) {
            return true;
        }
    }
    return false;
}

bool isPropertyIdentifier(const string& word) {
    // Verifica se o identificador de propriedade segue as regras fornecidas
    if (word.compare(0, 3, "has") == 0 && isupper(word[3])) {
        return true;
    } else if (word.compare(0, 2, "is") == 0 && word.compare(word.length() - 2, 2, "Of") == 0) {
        return true;
    }
    return false;
}

void identifyReservedWords(const string& text) {
    State state = START;
    string currentWord;

    for (char c : text) {
        switch (state) {
            case START:
                if (isalpha(c)) {
                    currentWord += c;
                    state = IN_WORD;
                } else if (isdigit(c)) {
                    state = IN_DIGIT;
                }
                break;

            case IN_WORD:
                if (isalnum(c) || c == '_') {
                    currentWord += c;
                } else {
                    if (isReservedWord(currentWord)) {
                        cout << "<" << currentWord << ", Palavra reservada>" << endl;
                    } else if (isClassIdentifier(currentWord)) {
                        cout << "<" << currentWord << ", Classe>" << endl;
                    } else if (isPropertyIdentifier(currentWord)) {
                        cout << "<" << currentWord << ", Propriedade>" << endl;
                    }
                    currentWord.clear();
                    state = START;
                    if (isalpha(c)) {
                        currentWord += c;
                        state = IN_WORD;
                    } else if (isdigit(c)) {
                        state = IN_DIGIT;
                    }
                }
                break;

            case IN_DIGIT:
                if (!isdigit(c)) {
                    state = START;
                    if (isalpha(c)) {
                        currentWord += c;
                        state = IN_WORD;
                    }
                }
                break;
        }
    }

    if (!currentWord.empty()) {
        if (isReservedWord(currentWord)) {
            cout << "<" << currentWord << ", >" << endl;
        } else if (isClassIdentifier(currentWord)) {
            cout << "<" << currentWord << ", CLASS>" << endl;
        } else if (isPropertyIdentifier(currentWord)) {
            cout << "<" << currentWord << ", PROPERTY>" << endl;
        }
    }
}

int main() {
    ifstream inputFile("entrada/test01.txt");  // Modifique o caminho conforme necessário

    if (!inputFile.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return 1;
    }

    stringstream buffer;
    buffer << inputFile.rdbuf();
    string text = buffer.str();

    identifyReservedWords(text);

    inputFile.close();

    return 0;
}
