#include <stdio.h>
#include <string.h>
int map(char ch)
{
    switch (ch)
    {
    case '+':
        return 0;
    case '*':
        return 1;
    case '(':
        return 2;
    case ')':
        return 3;
    case '^':
        return 4;
    case '/':
        return 5;
    case '$':
        return 7;
    default:
        return 6;
    }
}
int precedence_table[8][8] = {
    /*       +     *    (    )    ^    /   id    $   */
    /* + */ {'>', '>', '<', '>', '<', '>', '<', '>'},
    /* * */ {'>', '>', '<', '>', '<', '>', '<', '>'},
    /* ( */ {'<', '<', '<', '=', '<', '<', '<', ' '},
    /* ) */ {'>', '>', ' ', '>', '>', '>', ' ', '>'},
    /* ^ */ {'>', '>', '<', '>', '>', '>', '<', '>'},
    /* / */ {'>', '>', '<', '>', '>', '>', '<', '>'},
    /* id */ {'>', '>', ' ', '>', '<', '>', ' ', '>'},
    /* $ */ {'<', '<', '<', ' ', '<', '<', '<', '='}};
char stack[100], symbStack[100];
int stackPos = -1, symbstackPos = -1, flag = 0;
int main()
{
    char inputBuffer[100];
    printf("Enter the string to be parsed : (Accepted operators {+ * ( ) ^ /}) : ");
    scanf("%s", inputBuffer);
    int inputBufferLength = strlen(inputBuffer), ptr = 0;
    inputBuffer[inputBufferLength++] = '$', inputBuffer[inputBufferLength] = '\0';
    stack[++stackPos] = symbStack[++symbstackPos] = '$';

    // Print the header of the table
    printf("%-20s\t%-20s\t%-20s\t%-20s\n", "Stack", "Input Buffer", "Stack Symbol", "Input Buffer Symbol");

    while (1)
    {
        char stackSymbol = symbStack[symbstackPos], inputBufferSymbol = inputBuffer[ptr];
        char operation = precedence_table[map(stackSymbol)][map(inputBufferSymbol)];

        // Print the current state of the stack and input buffer
        printf("%-20.*s\t%-20.*s\t%-20c\t%-20c\n", stackPos + 1, stack, inputBufferLength - ptr, inputBuffer + ptr, stackSymbol, inputBufferSymbol);

        if (stackSymbol == '$' && inputBufferSymbol == '$')
        {
            flag = 1;
            break;
        }
        if (operation == '<' || operation == '=')
            stack[++stackPos] = symbStack[++symbstackPos] = inputBufferSymbol, ptr++;
        else if (operation == '>')
        {
            if (map(stackSymbol) == 6)
                stack[stackPos] = 'E', --symbstackPos;
            else
                stackPos -= 2, stack[stackPos] = 'E', symbstackPos -= stackSymbol == ')' ? 2 : 1;
        }
        else if (operation == ' ')
            break;
    }

    // Print the final result
    if (flag)
        printf("The string was accepted by the parser\n");
    else
        printf("The string was rejected by the parser\n");
}
