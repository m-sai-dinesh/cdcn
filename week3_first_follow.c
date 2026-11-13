#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 20
char productions[MAX][MAX];
char first[MAX][MAX], follow[MAX][MAX];
int n;
void add(char *set, char ch)
{
    int i;
    for (i = 0; set[i] != '\0'; i++)
    {
        if (set[i] == ch)
            return;
    }
    int len = strlen(set);
    set[len] = ch;
    set[len + 1] = '\0';
}
void findFirst(char *result, char symbol)
{
    int i, j;
    char temp[MAX];
    if (!isupper((unsigned char)symbol))
    {
        add(result, symbol);
        return;
    }
   for (i = 0; i < n; i++)
    {
        if (productions[i][0] == symbol)
        {
            if (productions[i][2] == '#')
            {
                add(result, '#');
            }
            else
            {
                for (j = 2; productions[i][j] != '\0'; j++)
                {
                    temp[0] = '\0';
                    findFirst(temp, productions[i][j]);
                    int k;
                    for (k = 0; temp[k] != '\0'; k++)
                    {
                        if (temp[k] != '#')
                            add(result, temp[k]);
                    }
                    if (strchr(temp, '#') == NULL)
                        break;
                    if (productions[i][j + 1] == '\0')
                        add(result, '#');
                }
            }
        }
    }
}
void findFollow(char *result, char symbol)
{
    int i, j, k;
    char temp[MAX];
    if (symbol == productions[0][0])
        add(result, '$');
    for (i = 0; i < n; i++)
    {
        for (j = 2; productions[i][j] != '\0'; j++)
        {
            if (productions[i][j] == symbol)
            {
                if (productions[i][j + 1] != '\0')
                {
                    temp[0] = '\0';
                    findFirst(temp, productions[i][j + 1]);
                    for (k = 0; temp[k] != '\0'; k++)
                    {
                        if (temp[k] != '#')
                            add(result, temp[k]);
                    }
                    if (strchr(temp, '#') != NULL)
                    {
                        temp[0] = '\0';
                        findFollow(temp, productions[i][0]);
                        for (k = 0; temp[k] != '\0'; k++)
                            add(result, temp[k]);
                    }
                }
                else if (productions[i][0] != symbol)
                {
                    temp[0] = '\0';
                    findFollow(temp, productions[i][0]);
                    for (k = 0; temp[k] != '\0'; k++)
                        add(result, temp[k]);
                }
            }
        }
    }
}
int main()
{
    int i;
    char nonTerminals[MAX];
    printf("Enter number of productions: ");
    scanf("%d", &n);
    printf("Enter productions (use # for epsilon):\n");
    for (i = 0; i < n; i++)
        scanf("%s", productions[i]);
    int ntCount = 0;
    for (i = 0; i < n; i++)
    {
        char nt = productions[i][0];
        if (strchr(nonTerminals, nt) == NULL)
        {
            nonTerminals[ntCount++] = nt;
            nonTerminals[ntCount] = '\0';
        }
    }
    printf("\nFIRST sets:\n");
    for (i = 0; i < ntCount; i++)
    {
        char result[MAX] = "";
        findFirst(result, nonTerminals[i]);
        printf("FIRST(%c) = { ", nonTerminals[i]);
        for (int j = 0; result[j] != '\0'; j++)
            printf("%c ", result[j]);
        printf("}\n");
    }
    printf("\nFOLLOW sets:\n");
    for (i = 0; i < ntCount; i++)
    {
        char result[MAX] = "";
        findFollow(result, nonTerminals[i]);
        printf("FOLLOW(%c) = { ", nonTerminals[i]);
        for (int j = 0; result[j] != '\0'; j++)
            printf("%c ", result[j]);
        printf("}\n");
    }
    return 0;
}

Output 
Enter number of productions: 8
Enter productions (use # for epsilon):
E=TR
R=+TR
R=#
T=FS
S=*FS
S=#
F=(E)
F=i

FIRST sets:
FIRST(E) = { ( i }
FIRST(R) = { + # }
FIRST(T) = { ( i }
FIRST(S) = { * # }
FIRST(F) = { ( i }

FOLLOW sets:
FOLLOW(E) = { $ ) }
FOLLOW(R) = { $ ) }
FOLLOW(T) = { + $ ) }
FOLLOW(S) = { + $ ) }
FOLLOW(F) = { * + $ ) }
