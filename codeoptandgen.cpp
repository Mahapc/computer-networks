#include <stdio.h>
typedef enum {
    NUMBER,
    ADD,
    MULTIPLY,
} TokenType;
typedef struct {
    TokenType type;
    int value; 
} Token;
void generateOptimizedCode(Token token) {
    switch (token.type) {
        case NUMBER:
            printf("PUSH %d\n", token.value);
            break;
        case ADD:
            printf("ADD\n");
            break;
        case MULTIPLY:
            printf("MULTIPLY\n");
            break;
        default:
            fprintf(stderr, "Error: Unknown token type\n");
            break;
    }
}

int main() {
    // Example expression: 2 * (3 + 4)
    Token tokens[] = {
        {NUMBER, 2},
        {NUMBER, 3},
        {NUMBER, 4},
        {ADD, 0},       
        {MULTIPLY, 0},  
    };

  
    for (int i = 0; i < sizeof(tokens) / sizeof(tokens[0]); i++) {
        generateOptimizedCode(tokens[i]);
    }

    return 0;
}
