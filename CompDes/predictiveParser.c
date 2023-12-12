#include <stdio.h>
#include <string.h>
char stack[1000], nonTerminals[100], startSymbol;
int stackPos = -1, parsingSuccessfull = 0, numberOfNonTerminals = 0;
int main()
{
    int numberOfProductions;
    printf("Enter the number of productions : ");
    scanf("%d", &numberOfProductions);
    char productionsLHS[numberOfProductions], productionsRHS[numberOfProductions][10];
    printf("Enter the productions : (\"_\" for epsilon) : \n");
    for (int i = 0; i < numberOfProductions; i++)
    {
        getchar();
        printf("Enter the LHS for production rule %d : ", i);
        scanf("%c", &productionsLHS[i]);
        printf("Enter the RHS for production rule %d : ", i);
        scanf("%s", productionsRHS[i]);
    }
    for (int i = 0; i < numberOfProductions; i++)
    {
        int j = 0;
        while (j < numberOfNonTerminals)
        {
            if (nonTerminals[j] == productionsLHS[i])
                break;
            j++;
        }
        if (j == numberOfNonTerminals)
            nonTerminals[numberOfNonTerminals++] = productionsLHS[i];
    }
    int parseTable[256][256];
    for (int i = 0; i < 256; i++)
        for (int j = 0; j < 256; j++)
            parseTable[i][j] = -1;
    // char bruh[][10] = {"i(", ")+$", "i(", ")+*$", "i("};
    // char omr[][10] = {"00", "212", "33", "5545", "67"};
    printf("Input parse table : (In the format (symbol, corresponding production number))\n");
    for (int i = 0; i < numberOfNonTerminals; i++)
    {
        int numberOfEntries;
        printf("Enter the number of entries for %c in the parse table : ", nonTerminals[i]);
        scanf("%d", &numberOfEntries);
        for (int j = 0; j < numberOfEntries; j++)
        {
            char symb;
            int productionNumber;
            getchar();
            printf("Enter the symbol and production number for entry %d : ", j + 1);
            scanf("%c %d", &symb, &productionNumber);
            parseTable[nonTerminals[i]][symb] = productionNumber;
        }
    }
    getchar();
    printf("Enter the start symbol : ");
    scanf("%c", &startSymbol);
    char inputBuffer[100];
    int ptr = 0, inputBufferLength;
    printf("Enter the string to be parsed : ");
    scanf("%s", inputBuffer);
    inputBufferLength = strlen(inputBuffer);
    inputBuffer[inputBufferLength++] = '$', inputBuffer[inputBufferLength] = '\0';
    stack[++stackPos] = '$';
    stack[++stackPos] = startSymbol;
    
    // Print the header of the table
    printf("%-20s\t%-20s\t%-20s\t%-20s\n", "Stack", "Input Buffer", "Stack Symbol", "Input Buffer Symbol");
    
    while (1)
    {
        char currentParsingSymbol = inputBuffer[ptr], currentTopOfStack = stack[stackPos];
        
        // Print the current state of the stack and input buffer
        printf("%-20.*s\t%-20.*s\t%-20c\t%-20c\n", stackPos + 1, stack, inputBufferLength - ptr, inputBuffer + ptr, currentTopOfStack, currentParsingSymbol);
        
        if (currentParsingSymbol == currentTopOfStack && currentTopOfStack == '$')
        {
            parsingSuccessfull = 1;
            break;
        }
        if (currentParsingSymbol == currentTopOfStack)
            ptr++, stackPos--;
        else if (parseTable[currentTopOfStack][currentParsingSymbol] == -1)
            break;
        else
        {
            int productionNumber = parseTable[currentTopOfStack][currentParsingSymbol];
            char tempRHS_production[10];
            strcpy(tempRHS_production, productionsRHS[productionNumber]);
            stackPos--;
            if (strcmp(tempRHS_production, "_") != 0)
                for (int i = strlen(tempRHS_production) - 1; i >= 0; i--)
                    stack[++stackPos] = tempRHS_production[i];
        }
    }
    
    // Print the final result
    if (parsingSuccessfull)
        printf("The given string was accepted by the parser\n");
    else
        printf("The given string was rejected by the parser\n");
}
