// S -> A
// A -> X | abX
// X -> ab | bX | Aa | $

// S -> A
// A -> abXA'
// X -> bXA' | AaX' | $
// A' -> bXA' | aX | ε
// X' -> aX | ε

#include <stdio.h>
#include <string.h>
char parseString[100];
int parsingPosition = 0;
char stack[1000];
int stackPos = 0;
void addtoStack(char ch) { stack[stackPos++] = ch; }
void S()
{
    addtoStack('S');
    A();
}
void A()
{
    addtoStack('A');
    if (parseString[parsingPosition] == 'a')
    {
        addtoStack('a');
        parsingPosition++;
        if (parseString[parsingPosition] == 'b')
        {
            addtoStack('b');
            parsingPosition++;
            X();
        }
    }
    else
        X();
}
void X()
{
    addtoStack('X');
    if (parseString[parsingPosition] == 'a')
    {
        addtoStack('a');
        parsingPosition++;
        if (parseString[parsingPosition] == 'b')
        {
            addtoStack('b');
            parsingPosition++;
        }
    }
    else if (parseString[parsingPosition] == 'b')
    {
        addtoStack('b');
        parsingPosition++;
        X();
    }
    else if (parseString[parsingPosition] != '\0')
    {
        A();
        if (parseString[parsingPosition] == 'a')
        {
            addtoStack('a');
            parsingPosition++;
        }
    }
    else
        return;
}
int main()
{
    printf("\nName : ATHARVA GULKOTWAR, REGISTRATION NUMBER : 21BCI0367\n");
    printf("Enter the string to be parsed : ");
    scanf("%s", parseString);
    S();
    if (parseString[parsingPosition] == '\0')
    {
        printf("Accepted\nParse Tree (PREFIX FORMAT) :: ");
        for (int i = 0; i < stackPos; i++)
            printf("%c ", stack[i]);
    }
    else
        printf("Rejected");
}
