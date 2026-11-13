#include <stdio.h>
#include <stdlib.h>

struct Node {
    char value;
    struct Node *left;
    struct Node *right;
};

int regCount = 0;

struct Node* createNode(char value, struct Node *left, struct Node *right) {
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    node->value = value;
    node->left = left;
    node->right = right;
    return node;
}

int generateCode(struct Node *root) {
    int leftReg, rightReg, currentReg;

    if (root == NULL)
        return -1;

    if (root->left == NULL && root->right == NULL) {
        currentReg = regCount++;
        printf("MOV R%d, %c\n", currentReg, root->value);
        return currentReg;
    }

    leftReg = generateCode(root->left);
    rightReg = generateCode(root->right);
    currentReg = regCount++;

    switch (root->value) {
        case '+':
            printf("ADD R%d, R%d, R%d\n", currentReg, leftReg, rightReg);
            break;
        case '-':
            printf("SUB R%d, R%d, R%d\n", currentReg, leftReg, rightReg);
            break;
        case '*':
            printf("MUL R%d, R%d, R%d\n", currentReg, leftReg, rightReg);
            break;
        case '/':
            printf("DIV R%d, R%d, R%d\n", currentReg, leftReg, rightReg);
            break;
    }

    return currentReg;
}

int main() {
    struct Node *a = createNode('a', NULL, NULL);
    struct Node *b = createNode('b', NULL, NULL);
    struct Node *c = createNode('c', NULL, NULL);

    struct Node *mul = createNode('*', b, c);
    struct Node *root = createNode('+', a, mul);

    printf("Abstract Syntax Tree:\n\n");
    printf("       +\n");
    printf("      / \\\n");
    printf("     a   *\n");
    printf("        / \\\n");
    printf("       b   c\n");

    printf("\nGenerated Target Code:\n");
    generateCode(root);

    return 0;
}

output 

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
