#include <stdio.h>
#include <string.h>
#define NUMBEROFOPERATORS 17
#define PRECEDENCES 6
char ops[][2] = {"*", "/", "%", "+", "-", "<<", ">>", "<", ">", "<=", ">=", "&", "^", "|", "&&", "||", "()"};
int priorityNumber(char arr[])
{
    if (strcmp(arr, "*") == 0 || strcmp(arr, "/") == 0 || strcmp(arr, "%") == 0)
        return 5;
    if (strcmp(arr, "+") == 0 || strcmp(arr, "-") == 0)
        return 4;
    if (strcmp(arr, "<<") == 0 || strcmp(arr, ">>") == 0)
        return 3;
    if (strcmp(arr, "<") == 0 || strcmp(arr, ">") == 0 || strcmp(arr, "<=") == 0 || strcmp(arr, ">=") == 0)
        return 2;
    if (strcmp(arr, "&") == 0 || strcmp(arr, "^") == 0 || strcmp(arr, "|") == 0)
        return 1;
    if (strcmp(arr, "&&") == 0 || strcmp(arr, "||") == 0)
        return 0;
    return -1;
}
int main()
{
    int num, pr = 0, flag = 0, first = 1;
    char ch = 'E';
    printf("Enter the number of productions for E : ");
    scanf("%d", &num);
    char productions[num][4];
    printf("Allowed operators --> ");
    for (int i = 0; i < NUMBEROFOPERATORS; i++)
        printf("\"%s\" ", ops[i]);
    printf("\n\nINPUT PRODUCTION RULES : (\"id\" for Terminal)\n");
    for (int i = 0; i < num; i++)
    {
        printf("Enter the production rule %d : ", i + 1);
        scanf("%s", productions[i]);
    }
    printf("Before removal of ambiguity : PRODUCTION RULES : \n\nE -> ");
    for (int i = 0; i < num; i++)
    {
        printf("%s", productions[i]);
        if (i != num - 1)
            printf("|");
    }
    printf("\n\nAfter removal of ambiguity : PRODUCTION RULES :\n");
    for (int i = 0; i < PRECEDENCES; i++)
    {
        for (int j = 0; j < num; j++)
        {
            if (productions[j][0] != '(')
            {
                int n = strlen(productions[j]) - 2;
                char temp[n + 1];
                for (int k = 0; k < n; k++)
                    temp[k] = productions[j][k + 1];
                temp[n] = '\0';
                if (priorityNumber(temp) == i)
                {
                    flag = 1;
                    if (first)
                    {
                        printf("%c -> ", ch);
                        first = 0;
                    }
                    printf("%c%s%c|", ch, temp, ch + 1);
                }
            }
            else if (productions[j][0] == '(')
                pr = 1;
        }
        if (flag)
        {
            flag = 0, first = 1, ch++;
            printf("%c\n", ch);
        }
    }
    printf("%c -> ", ch);
    if (pr)
        printf("(E)|");
    printf("id");
}