#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_IDENTIFIER_LENGTH 50
#define MAX_NUMBER_LENGTH 10

typedef enum {
    KEYWORD,
    IDENTIFIER,
    NUMBER,
    OPERATOR,
    PUNCTUATION
} TokenType;

typedef struct {
    TokenType type;
    char lexeme[MAX_IDENTIFIER_LENGTH];
} Token;

int isKeyword(char *word) {
    // Add your list of keywords here
    char *keywords[] = {"int", "float", "if", "else", "while", "return"};
    int numKeywords = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < numKeywords; ++i) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1; // It's a keyword
        }
    }

    return 0; // It's not a keyword
}

void getToken(FILE *file, Token *token) {
    char c;
    int i = 0;

    // Ignore whitespace and comments
    while ((c = fgetc(file)) != EOF) {
        if (isspace(c)) {
            continue; // Ignore spaces, tabs, and new lines
        }

        if (c == '/') {
            // Check for comments
            if ((c = fgetc(file)) == '/') {
                // Line comment, ignore until the end of the line
                while ((c = fgetc(file)) != '\n' && c != EOF);
            } else if (c == '*') {
                // Block comment, ignore until the closing */
                while ((c = fgetc(file)) != '*' || (c = fgetc(file)) != '/');
            } else {
                // Not a comment, backtrack
                ungetc(c, file);
                break;
            }
        } else {
            // Not a space, tab, new line, or comment, backtrack
            ungetc(c, file);
            break;
        }
    }

    // Identify the token type
    c = fgetc(file);
    if (isalpha(c) || c == '_') {
        // Identifier or keyword
        token->type = isKeyword(token->lexeme) ? KEYWORD : IDENTIFIER;
        while (isalnum(c) || c == '_') {
            token->lexeme[i++] = c;
            c = fgetc(file);
        }
    } else if (isdigit(c)) {
        // Number
        token->type = NUMBER;
        while (isdigit(c)) {
            token->lexeme[i++] = c;
            c = fgetc(file);
        }
    } else if (c == '+' || c == '-' || c == '*' || c == '/') {
        // Operator
        token->type = OPERATOR;
        token->lexeme[i++] = c;
    } else if (c == ';' || c == ',' || c == '(' || c == ')' || c == '{' || c == '}') {
        // Punctuation
        token->type = PUNCTUATION;
        token->lexeme[i++] = c;
    } else {
        // Invalid character
        token->type -1;
    }

    token->lexeme[i] = '\0';
}

int main() {
    FILE *file = fopen("3.c.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    Token token;
    while (1) {
        getToken(file, &token);
        if (token.type == -1) {
            printf("Error: Invalid character\n");
            break;
        }

        printf("Type: %d, Lexeme: %s\n", token.type, token.lexeme);

        if (feof(file)) {
            break;
        }
    }

    fclose(file);
    return 0;
}

