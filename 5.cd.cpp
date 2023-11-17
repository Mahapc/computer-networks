#include <stdio.h>

int main() {
    int temp = 1;
    char op1, op2, a1, a2, res1, res2;

    printf("Enter an expression: ");
    scanf(" %c %c %c %c %c", &res1, &op1, &a1, &op2, &a2);

    
    if (op2 == '*') {
        printf("t%d = %c %c %c\n", temp, a1, op2, a2);
        temp++;
        printf("t%d = %c %c t%d\n", temp, res1, op1, temp-1);
    } else {
        printf("t%d = %c %c %c\n", temp, res1, op1, a1);
        temp++;
        printf("t%d = t%d %c %c\n", temp, temp - 1, op2, a2);
    }

    return 0;
}
