#include <stdio.h>
#include <ctype.h>

// Function to ignore whitespace characters
void ignoreWhitespace(FILE *fp) {
    char c;
    while ((c = fgetc(fp)) == ' ' || c == '\t' || c == '\n') {
        // Ignore spaces, tabs, and new lines
    }
    // Put back the last non-whitespace character
    ungetc(c, fp);
}

// Function to ignore comments
void ignoreComments(FILE *fp) {
    char c;
    if ((c = fgetc(fp)) == '/') {
        // Line comment
        while ((c = fgetc(fp)) != '\n' && c != EOF) {
            // Ignore characters in the comment
        }
    } else if (c == '*') {
        // Block comment
        int insideComment = 1;
        while (insideComment) {
            while ((c = fgetc(fp)) != '*') {
                if (c == EOF) {
                    // Error: Unclosed block comment
                    printf("Error: Unclosed block comment\n");
                    break;
                }
            }
            if ((c = fgetc(fp)) == '/') {
                insideComment = 0; // Exit the block comment
            } else {
                ungetc(c, fp);
            }
        }
    } else {
        // Not a comment
        ungetc(c, fp);
    }
}

// Function to get the next token
void getNextToken(FILE *fp) {
    ignoreWhitespace(fp);
    ignoreComments(fp);

    // Now, you can implement logic to identify and print different tokens
    // For example, you can handle keywords, identifiers, numbers, etc.

    // Sample logic to print the remaining characters
    char c;
    while ((c = fgetc(fp)) != ' ' && c != '\t' && c != '\n' && c != EOF) {
        printf("%c", c);
    }
    printf("\n");
}

int main() {
    FILE *fp;
    fp = fopen("your_source_code.txt", "r");

    if (fp == NULL) {
        perror("Error opening file");
        return -1;
    }

    while (!feof(fp)) {
        getNextToken(fp);
    }

    fclose(fp);
    return 0;
}

