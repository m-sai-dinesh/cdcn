#include <iostream>
#include <vector>
#include <string>
using namespace std;
int tempCount = 1;
vector<string> operands;
vector<char> operators;
int precedence(char op)
{
    if (op == '*' || op == '/')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}
void applyOperator()
{
    char op = operators.back();
    operators.pop_back();
    string right = operands.back();
    operands.pop_back();
    string left = operands.back();
    operands.pop_back();
    string temp = "t" + to_string(tempCount++);
    cout << temp << " = " << left << " " << op << " " << right << "\n";
    operands.push_back(temp);
}
void generateTAC(const string &expr)
{
    for (size_t i = 0; i < expr.size();)
    {
        char c = expr[i];
        if (c == ' ')
            i++;
        else if (isalnum(c))
        {
            string operand;
            while (i < expr.size() && isalnum(expr[i]))
                operand += expr[i++];
            operands.push_back(operand);
        }
        else if (c == '(')
        {
            operators.push_back(c);
            i++;
        }
        else if (c == ')')
        {
            while (!operators.empty() && operators.back() != '(')
                applyOperator();
            operators.pop_back();
            i++;
        }
        else
        {
            while (!operators.empty() && operators.back() != '(' && precedence(operators.back()) >= precedence(c))
                applyOperator();
            operators.push_back(c);
            i++;
        }
    }
    while (!operators.empty())
        applyOperator();
}
int main()
{
    string expr;
    cout << "Enter the expression: ";
    cin >> expr;
    cout << "\nThree Address Code:\n";
    generateTAC(expr);
    return 0;
}

Output

Enter the expression: a+b*c-d/g

Three Address Code:
t1 = b * c
t2 = a + t1
t3 = d / g
t4 = t2 - t3
