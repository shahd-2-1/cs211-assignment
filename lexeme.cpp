#include <iostream>
#include <sstream>      // for istringstream
#include <cctype>       // for character classification
#include <string>       // for string class

// Character classes
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99
#define END_OF_FILE -1

// Token codes
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26

using namespace std;

// Global declarations
int charClass;
string lexeme;
char nextChar;
int nextToken;
istringstream inputStream; // to simulate file input from user string

// Function to add character to lexeme
void addChar() {
    lexeme += nextChar;
}

// Function to get next character from input
void getChar() {
    if (inputStream.get(nextChar)) {
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else
            charClass = UNKNOWN;
    } else {
        charClass = END_OF_FILE;
    }
}

// Function to skip whitespace
void getNonBlank() {
    while (isspace(nextChar)) {
        getChar();
    }
}

// Function to lookup operators and parentheses
int lookup(char ch) {
    switch (ch) {
        case '(':
            addChar();
            nextToken = LEFT_PAREN;
            break;
        case ')':
            addChar();
            nextToken = RIGHT_PAREN;
            break;
        case '+':
            addChar();
            nextToken = ADD_OP;
            break;
        case '-':
            addChar();
            nextToken = SUB_OP;
            break;
        case '*':
            addChar();
            nextToken = MULT_OP;
            break;
        case '/':
            addChar();
            nextToken = DIV_OP;
            break;
        case '=':
            addChar();
            nextToken = ASSIGN_OP;
            break;
        default:
            addChar();
            nextToken = END_OF_FILE;
            break;
    }
    return nextToken;
}

// Lexical analyzer
int lex() {
    lexeme = "";
    getNonBlank();
    switch (charClass) {
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = IDENT;
            break;

        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = INT_LIT;
            break;

        case UNKNOWN:
            lookup(nextChar);
            getChar();
            break;

        case END_OF_FILE:
            nextToken = END_OF_FILE;
            lexeme = "EOF";
            break;
    }

    cout << "Next token is: " << nextToken << ", Next lexeme is: " << lexeme << endl;
    return nextToken;
}

// Main function
int main() {
    string inputLine;

    cout << "Enter an expression: ";
    getline(cin, inputLine);

    inputStream.str(inputLine);  // Load input into stream
    inputStream.clear();         // Reset stream state

    getChar();

    do {
        lex();
    } while (nextToken != END_OF_FILE);

    system("pause");  // ⬅️ This will wait for a key press before closing (Windows only)
    return 0;
}
