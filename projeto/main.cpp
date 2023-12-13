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
    vector<string> reservedWords = {"SOME", "ALL", "VALUE", "MIN", "MAX", "EXACTLY", "THAT", "NOT", "AND", "OR"};
    return find(reservedWords.begin(), reservedWords.end(), word) != reservedWords.end();
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
