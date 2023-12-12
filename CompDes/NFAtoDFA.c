#include <stdio.h>

// Array to track the discovered states
int statesDiscovered[256] = {0};

// Array to store states left to discover
int statesLeftToDiscover[256];

// Map function to map DFA states to indices
int mapFunction[256] = {0};

// Number of states left to discover
int numberOfStatesLeftToDiscover = 0;

int main()
{
    // Variable to store the number of states in NFA
    int numberOfStatesNFA;

    printf("Enter the number of states in NFA : ");
    scanf("%d", &numberOfStatesNFA);

    // 2D array to store transitions of NFA states
    int statesOfNFA[numberOfStatesNFA][2];

    // Inputting the transitions of NFA states
    for (int i = 0; i < numberOfStatesNFA; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            statesOfNFA[i][j] = 0;
            int num, temp;

            printf("Enter the number of states to which stateNumber - %d goes to upon the input %c: ", i, 'a' + j);
            scanf("%d", &num);
            printf("Enter those State Numbers : \n");

            for (int k = 0; k < num; k++)
            {
                scanf("%d", &temp);
                statesOfNFA[i][j] = statesOfNFA[i][j] | (128 >> temp);
            }
        }
    }

    int startingState, finalState, numberOfStatesDFA = 0;

    // 2D array to store transitions of DFA states
    int statesOfDFA[256][3];

    printf("Enter the Start and Final State of the NFA : ");
    scanf("%d %d", &startingState, &finalState);

    // Adding the starting state of the NFA to states left to discover
    statesLeftToDiscover[numberOfStatesLeftToDiscover++] = 128 >> startingState;

    // Discovering DFA states using NFA transitions
    while (numberOfStatesLeftToDiscover)
    {
        int currentState = statesLeftToDiscover[--numberOfStatesLeftToDiscover];
        int temp_a = 0, temp_b = 0;

        // Mark the current state as discovered
        statesDiscovered[currentState] = 1;

        // Add the current state to DFA state transitions
        statesOfDFA[numberOfStatesDFA][0] = currentState;

        // Calculate the transitions for input 'a' and 'b'
        for (int i = 0; i < 8; i++)
        {
            if ((currentState & (128 >> i)))
            {
                temp_a = temp_a | statesOfNFA[i][0];
                temp_b = temp_b | statesOfNFA[i][1];
            }
        }

        // Add the transitions to DFA state transitions
        statesOfDFA[numberOfStatesDFA][1] = temp_a;
        statesOfDFA[numberOfStatesDFA][2] = temp_b;

        // Check if the transitions have not been discovered before, add them to states left to discover
        if (statesDiscovered[temp_a] == 0)
        {
            statesDiscovered[temp_a] = 1;
            statesLeftToDiscover[numberOfStatesLeftToDiscover++] = temp_a;
        }

        if (statesDiscovered[temp_b] == 0)
        {
            statesDiscovered[temp_b] = 1;
            statesLeftToDiscover[numberOfStatesLeftToDiscover++] = temp_b;
        }

        // Increase the number of DFA states
        numberOfStatesDFA++;
    }

    // Map DFA states to indices
    int count = 0;
    for (int i = 1; i < 256; i++)
    {
        if (statesDiscovered[i])
        {
            mapFunction[i] = count++;
        }
    }

    printf("\nConverted DFA will be : \n\n");
    printf("|-----------------------------------------------|\n");
    printf("|\t State \t|\t a \t|\t b \t|\n");
    printf("|-----------------------------------------------|\n");

    // Print the DFA table
    for (int i = 0; i < numberOfStatesDFA; i++)
    {
        printf("|\t ");

        // Mark the starting state and final state with appropriate symbols
        if (statesOfDFA[i][0] == (128 >> startingState))
        {
            printf("->");
        }
        else if (statesOfDFA[i][0] & (128 >> finalState))
        {
            printf("*");
        }

        for (int j = 0; j < 3; j++)
        {
            if (statesOfDFA[i][j] == 0)
            {
                printf("# \t|\t ");
            }
            else
            {
                printf("q%d \t|\t ", mapFunction[statesOfDFA[i][j]]);
            }
        }
        printf("\n|-----------------------------------------------|\n");
    }
    return 0;
}
