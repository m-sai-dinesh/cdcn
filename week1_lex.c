#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *keywords[] = {
    "int", "char", "float", "double",
    "if", "else", "while", "for",
    "do", "return", "void", "break",
    "continue", "switch", "case", "default"
};

int isKeyword(char *word)
{
    int i;

    for (i = 0; i < 16; i++)
    {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }

    return 0;
}

int main()
{
    char ch, next, word[100];
    int i;

    printf("Enter source code (Ctrl+D to stop):\n");

    while ((ch = getchar()) != EOF)
    {
        if (isspace((unsigned char)ch))
            continue;

        /* Ignore comments and identify division operator */
        if (ch == '/')
        {
            next = getchar();

            if (next == '/')
            {
                while ((ch = getchar()) != '\n' && ch != EOF);
                continue;
            }
            else if (next == '*')
            {
                char prev = '\0';

                while ((ch = getchar()) != EOF)
                {
                    if (prev == '*' && ch == '/')
                        break;

                    prev = ch;
                }

                continue;
            }
            else
            {
                if (next != EOF)
                    ungetc(next, stdin);

                printf("Operator: /\n");
                continue;
            }
        }

        /* Identify keywords and identifiers */
        if (isalpha((unsigned char)ch) || ch == '_')
        {
            i = 0;
            word[i++] = ch;

            while ((ch = getchar()) != EOF &&
                   (isalnum((unsigned char)ch) || ch == '_'))
            {
                if (i < 99)
                    word[i++] = ch;
            }

            word[i] = '\0';

            if (ch != EOF)
                ungetc(ch, stdin);

            if (isKeyword(word))
                printf("Keyword: %s\n", word);
            else
                printf("Identifier: %s\n", word);
        }

        /* Identify numeric constants */
        else if (isdigit((unsigned char)ch))
        {
            i = 0;
            word[i++] = ch;

            while ((ch = getchar()) != EOF && isdigit((unsigned char)ch))
            {
                if (i < 99)
                    word[i++] = ch;
            }

            word[i] = '\0';

            if (ch != EOF)
                ungetc(ch, stdin);

            printf("Constant: %s\n", word);
        }

        /* Identify operators */
        else if (strchr("+-*%=<>!&|", ch) != NULL)
        {
            next = getchar();

            if (next == '=' ||
                (ch == '+' && next == '+') ||
                (ch == '-' && next == '-') ||
                (ch == '&' && next == '&') ||
                (ch == '|' && next == '|'))
            {
                printf("Operator: %c%c\n", ch, next);
            }
            else
            {
                if (next != EOF)
                    ungetc(next, stdin);

                printf("Operator: %c\n", ch);
            }
        }

        /* Identify special symbols */
        else if (strchr(";(){}[]", ch) != NULL)
        {
            printf("Special Symbol: %c\n", ch);
        }

        /* Identify unrecognized symbols */
        else
        {
            printf("Unknown Symbol: %c\n", ch);
        }
    }

    return 0;
}
