#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

enum State {
    START, IN_WORD, IN_DIGIT
};

// Função para verificar se uma palavra é uma palavra reservada
bool isReservedWord(const string& word) {
    vector<string> reservedWords = {"SOME", "ALL", "VALUE", "MIN", "MAX", "EXACTLY", "THAT", "NOT", "AND", "OR"};
    return find(reservedWords.begin(), reservedWords.end(), word) != reservedWords.end();
}

// Função para processar o texto e identificar as palavras reservadas usando um autômato
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
                if (isalnum(c)) {
                    currentWord += c;
                } else {
                    if (isReservedWord(currentWord)) {
                        cout << "<" << currentWord << ", >" << endl;
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

    if (!currentWord.empty() && isReservedWord(currentWord)) {
        cout << "<" << currentWord << ", >" << endl;
    }
}

int main() {
    string text = "Pizza    THAT hasTopping    SOME          min      3";

    identifyReservedWords(text);

    return 0;
}
