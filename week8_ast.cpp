#include <iostream>
#include <map>
using namespace std;
struct Node
{
    char value;
    Node *left, *right;
    Node(char v, Node *l = NULL, Node *r = NULL) : value(v), left(l), right(r) {}
};
int regCount = 0;
map<char, string> op = {{'+', "ADD"}, {'-', "SUB"}, {'*', "MUL"}, {'/', "DIV"}};
int generateCode(Node *root)
{
    if (!root)
        return -1;
    if (!root->left && !root->right)
    {
        cout << "MOV R" << regCount << ", " << root->value << "\n";
        return regCount++;
    }
    int l = generateCode(root->left);
    int r = generateCode(root->right);
    int cur = regCount++;
    cout << op[root->value] << " R" << cur << ", R" << l << ", R" << r << "\n";
    return cur;
}
int main()
{
    Node *root = new Node('+', new Node('a'), new Node('*', new Node('b'), new Node('c')));
    cout << "Abstract Syntax Tree:\n\n";
    cout << "       +\n";
    cout << "      / \\\n";
    cout << "     a   *\n";
    cout << "        / \\\n";
    cout << "       b   c\n";
    cout << "\nGenerated Target Code:\n";
    generateCode(root);
    return 0;
}

Output

Abstract Syntax Tree:

       +
      / \
     a   *
        / \
       b   c

Generated Target Code:
MOV R0, a
MOV R1, b
MOV R2, c
MUL R3, R1, R2
ADD R4, R0, R3
