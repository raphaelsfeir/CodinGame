#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int espaces = 0;
bool nouvLigne = true;

void printSpaces(int espaces){
    for (int i = 0; i < espaces; ++i)
        cout << ' ';
}

void printNewLine(){
    cout << endl;
    nouvLigne = true;
}

void print(char c){
    if (nouvLigne){
        printSpaces(espaces);
        nouvLigne = false;
    }
    cout << c;
}

int main(){
    int N;
    cin >> N; cin.ignore();
    for (int i = 0; i < N; i++) {
        string CGXLine;
        getline(cin, CGXLine);
        bool readingString = false;
        for (char c : CGXLine){
            if (readingString){
                print(c);
                if (c == '\'')
                    readingString = false;
            }
            else{
                switch (c){
                    case ' ':
                    case '\t':
                        break;
                    case '(':
                        if (!nouvLigne)
                            printNewLine();
                        print('(');
                        printNewLine();
                        espaces += 4;
                        break;
                    case ')':
                        espaces -= 4;
                        if (!nouvLigne)
                            printNewLine();
                        print(')');
                        break;
                    case '\'':
                        readingString = !readingString;
                        print('\'');
                        break;
                    case ';':
                        print(';');
                        printNewLine();
                        break;
                    default:
                        print(c);
                        break;
                };
            }
        }
    }
}
