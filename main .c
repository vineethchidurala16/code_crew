#include <stdio.h>
#include <stdlib.h>

struct Node { // Creating the basic structure of the tree
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

struct Node* buildTree(int preOrder[], int postOrder[], int* preOrderIdx, int postLeftIdx, int postRightIdx, int n) {
    // Base condition: if the pointers are out of bounds
    if (*preOrderIdx >= n || postLeftIdx > postRightIdx) {
        return NULL;
    }

    // The first element in preOrder is the root
    struct Node* root = createNode(preOrder[*preOrderIdx]);
    ++(*preOrderIdx); // Incrementing the pointer

    // If there are no more elements to add, return the root
    if (*preOrderIdx >= n || postLeftIdx == postRightIdx) {
        return root;
    }

    // Finding the next element in preOrder within the postOrder array to determine the split point
    int i;
    for (i = postLeftIdx; i < postRightIdx; i++) {
        if (preOrder[*preOrderIdx] == postOrder[i]) {
            break;
        }
    }

    // Build left and right subtrees based on the position found
    if (i <= postRightIdx) {
        root->left = buildTree(preOrder, postOrder, preOrderIdx, postLeftIdx, i, n);        // Build left subtree
        root->right = buildTree(preOrder, postOrder, preOrderIdx, i + 1, postRightIdx - 1, n); // Build right subtree
    }

    return root; // Returning the root of the tree
}

void printPreOrder(struct Node* root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->data);
    printPreOrder(root->left);
    printPreOrder(root->right);
}

void printPostOrder(struct Node* root) {
    if (root == NULL) {
        return;
    }
    printPostOrder(root->left);
    printPostOrder(root->right);
    printf("%d ", root->data);
}

int main() {
    int n;
    printf("Enter length: ");
    scanf("%d", &n);

    int postOrder[n];
    printf("Enter postOrder nodes: \n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &postOrder[i]);
    }

    int preOrder[n];
    printf("Enter preOrder nodes: \n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &preOrder[i]);
    }

    int preOrderIdx = 0; // Starting index for preOrder

    struct Node* root = buildTree(preOrder, postOrder, &preOrderIdx, 0, n - 1, n);

    printf("Root is: %d\n", root->data);

    // Printing preOrder and postOrder traversals of the constructed tree
    printf("Postorder traversal: ");
    printPostOrder(root);
    printf("\n");
    
    printf("Preorder traversal: ");
    printPreOrder(root);
    printf("\n");

    

    return 0;
}