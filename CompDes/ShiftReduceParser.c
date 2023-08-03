#include <stdio.h>
#include <string.h>
char charStack[1000];
int numStack[1000], finalState, numStackPos = -1, charStackPos = -1;
int main()
{
    printf("\nName : ATHARVA GULKOTWAR, REGISTRATION NUMBER : 21BCI0367\n");
    int numberOfProductions, flag = 0;
    printf("Enter the total number of productions : ");
    scanf("%d", &numberOfProductions);
    char productionsLHS[numberOfProductions], productionsRHS[numberOfProductions][100];
    for (int i = 0; i < numberOfProductions; i++)
    {
        getchar();
        printf("Enter LHS for the production number %d : ", i + 1);
        scanf("%c", &productionsLHS[i]);
        printf("Enter the RHS for the production number %d : ", i + 1);
        scanf("%s", productionsRHS[i]);
    }
    int numberOfCanonicalStates, totalEntries;
    printf("Enter the number of canonical states : ");
    scanf("%d", &numberOfCanonicalStates);
    int parseTable[1000][numberOfCanonicalStates];
    for (int i = 0; i < 1000; i++)
        for (int j = 0; j < numberOfCanonicalStates; j++)
            parseTable[i][j] = 0;
    printf("Enter the total number of entries in the parse table : ");
    scanf("%d", &totalEntries);
    printf("Enter the entries in the form (Symbol,Reduction Number/Shift Number) use -ve for reduction and +ve for shifting :\n");
    for (int i = 0; i < numberOfCanonicalStates; i++)
    {
        int transitions;
        printf("Enter the number of transitions for canonical state %d : ", i);
        scanf("%d", &transitions);
        for (int j = 0; j < transitions; j++)
        {
            char symb;
            int op;
            getchar();
            scanf("%c %d", &symb, &op);
            parseTable[symb][i] = op;
        }
    }
    printf("Enter the final canonical state : ");
    scanf("%d", &finalState);
    char inputBuffer[100];
    printf("Enter the string to be parsed : ");
    scanf("%s", inputBuffer);
    int inputBufferLength = strlen(inputBuffer), ptr = 0;
    inputBuffer[inputBufferLength++] = '$', inputBuffer[inputBufferLength] = '\0';
    charStack[++charStackPos] = '$';
    numStack[++numStackPos] = 0;
    printf("STACK\t\t|INPUT BUFFER\n");
    while (1)
    {
        for (int i = 0; (charStackPos == numStackPos && i <= charStackPos) || (charStackPos != numStackPos && i < charStackPos); i++)
            printf("%c%d", charStack[i], numStack[i]);
        if (charStackPos != numStackPos)
            printf("%c", charStack[charStackPos]);
        printf("\t\t");
        for (int i = ptr; inputBuffer[i] != '\0'; i++)
            printf("%c", inputBuffer[i]);
        printf("\n");
        char charTopOfStack = charStack[charStackPos], currentSymbol = inputBuffer[ptr];
        int numTopOfStack = numStack[numStackPos];
        if (charStackPos != numStackPos && (charTopOfStack >= 'A' && charTopOfStack <= 'Z'))
            numStack[++numStackPos] = parseTable[charTopOfStack][numTopOfStack];
        else
        {
            if (numTopOfStack == finalState && inputBuffer[ptr] == '$')
            {
                flag = 1;
                break;
            }
            int operation = parseTable[currentSymbol][numTopOfStack];
            if (operation == 0)
                break;
            if (operation > 0)
            {
                charStack[++charStackPos] = currentSymbol;
                numStack[++numStackPos] = operation;
                ptr++;
            }
            else
            {
                operation *= -1;
                int elliminate = strlen(productionsRHS[operation - 1]);
                numStackPos -= elliminate, charStackPos -= elliminate;
                charStack[++charStackPos] = productionsLHS[operation - 1];
            }
        }
    }
    if (flag)
        printf("Given String is accepted by the parser");
    else
        printf("Given String is not accepted by the parser");
}