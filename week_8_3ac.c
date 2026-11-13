
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int tempCount = 1;

int precedence(char op)
{
    if (op == '*' || op == '/')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

void generateTAC(char expr[])
{
    char operands[50][20], operators[50];
    int topOperand = -1, topOperator = -1;
    int i = 0;

    while (expr[i] != '\0')
    {
        if (expr[i] == ' ')
        {
            i++;
            continue;
        }
        if (isalnum(expr[i]))
        {
            char operand[20];
            int j = 0;
            while (isalnum(expr[i]))
                operand[j++] = expr[i++];
            operand[j] = '\0';
            strcpy(operands[++topOperand], operand);
        }
        else if (expr[i] == '(')
        {
            operators[++topOperator] = expr[i++];
        }
        else if (expr[i] == ')')
        {
            while (topOperator >= 0 && operators[topOperator] != '(')
            {
                char op = operators[topOperator--];
                char right[20], left[20], temp[20];
                strcpy(right, operands[topOperand--]);
                strcpy(left, operands[topOperand--]);
                sprintf(temp, "t%d", tempCount++);
                printf("%s = %s %c %s\n", temp, left, op, right);
                strcpy(operands[++topOperand], temp);
            }
            topOperator--;
            i++;
        }
        else
        {
            char op = expr[i];
            while (topOperator >= 0 && operators[topOperator] != '(' && precedence(operators[topOperator]) >= precedence(op))
            {
                char oldOp = operators[topOperator--];
                char right[20], left[20], temp[20];
                strcpy(right, operands[topOperand--]);
                strcpy(left, operands[topOperand--]);
                sprintf(temp, "t%d", tempCount++);
                printf("%s = %s %c %s\n", temp, left, oldOp, right);
                strcpy(operands[++topOperand], temp);
            }
            operators[++topOperator] = op;
            i++;
        }
    }
    while (topOperator >= 0)
    {
        char op = operators[topOperator--];
        char right[20], left[20], temp[20];
        strcpy(right, operands[topOperand--]);
        strcpy(left, operands[topOperand--]);
        sprintf(temp, "t%d", tempCount++);
        printf("%s = %s %c %s\n", temp, left, op, right);
        strcpy(operands[++topOperand], temp);
    }
}

int main()
{
    char expr[100];
    printf("Enter the expression: ");
    scanf("%99s", expr);
    printf("\nThree Address Code:\n");
    generateTAC(expr);
    return 0;
}

output 

Enter the expression: a+b*c-d/g

Three Address Code:
t1 = b * c
t2 = a + t1
t3 = d / g
t4 = t2 - t3

