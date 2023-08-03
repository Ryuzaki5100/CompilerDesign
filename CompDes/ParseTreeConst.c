#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_RULES 10
#define MAX_SYMBOLS 20

typedef struct Node {
    char data[MAX_SYMBOLS];
    struct Node* children[MAX_SYMBOLS];
    int numChildren;
} Node;

typedef struct Rule {
    char nonTerminal[MAX_SYMBOLS];
    char production[MAX_SYMBOLS];
} Rule;

Rule grammar[MAX_RULES];
int numRules = 0;

Node* createNode(char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(1);
    }
    strcpy(newNode->data, data);
    newNode->numChildren = 0;
    return newNode;
}

void addChild(Node* parent, Node* child) {
    parent->children[parent->numChildren++] = child;
}

int isNonTerminal(char* symbol) {
    return isupper((int)symbol[0]);
}

void parseSymbol(Node* node, char* symbol);

void parseProduction(Node* node, char* production) {
    char* token = strtok(production, " ");
    while (token != NULL) {
        parseSymbol(node, token);
        token = strtok(NULL, " ");
    }
}

void parseSymbol(Node* node, char* symbol) {
    if (isNonTerminal(symbol)) {
        Node* child = createNode(symbol);
        addChild(node, child);

        for (int i = 0; i < numRules; i++) {
            if (strcmp(grammar[i].nonTerminal, symbol) == 0) {
                parseProduction(child, grammar[i].production);
                break;
            }
        }
    } else {
        Node* child = createNode(symbol);
        addChild(node, child);
    }
}

Node* parseTree(char* startSymbol) {
    Node* rootNode = createNode(startSymbol);
    for (int i = 0; i < numRules; i++) {
        if (strcmp(grammar[i].nonTerminal, startSymbol) == 0) {
            parseProduction(rootNode, grammar[i].production);
            break;
        }
    }
    return rootNode;
}

void printParseTree(Node* root, int depth) {
    if (root == NULL)
        return;

    for (int i = 0; i < depth; i++)
        printf("  ");

    printf("%s\n", root->data);

    for (int i = 0; i < root->numChildren; i++) {
        printParseTree(root->children[i], depth + 1);
    }
}

int main() {
    printf("Enter the grammar rules (non-terminal -> production):\n");
    printf("Enter 'q' to quit.\n");

    while (1) {
        char input[MAX_SYMBOLS];
        fgets(input, MAX_SYMBOLS, stdin);
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "q") == 0) {
            break;
        }

        char* arrow = strstr(input, "->");
        if (arrow != NULL) {
            arrow[0] = '\0';
            strcpy(grammar[numRules].nonTerminal, input);
            strcpy(grammar[numRules].production, arrow + 2);
            numRules++;
        }
    }

    printf("Enter the start symbol: ");
    char startSymbol[MAX_SYMBOLS];
    fgets(startSymbol, MAX_SYMBOLS, stdin);
    startSymbol[strcspn(startSymbol, "\n")] = '\0';

    printf("Enter the input to construct the parse tree: ");
    char input[MAX_SYMBOLS];
    fgets(input, MAX_SYMBOLS, stdin);
    input[strcspn(input, "\n")] = '\0';

    Node* p = parseTree(startSymbol);

    printf("Parse Tree:\n");
    printParseTree(p, 0);

    return 0;
}
