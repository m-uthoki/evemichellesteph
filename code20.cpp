#include <stdio.h>
#include <stdlib.h>

// Structure for a binary tree node
struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Function to create a new node
struct TreeNode* newNode(int data) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Function to find index of value in an array
int findIndex(int arr[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == value)
            return i;
    }
    return -1;
}

// Function to construct BST from in-order and post-order traversals
struct TreeNode* constructUtil(int in[], int post[], int inStart, int inEnd, int* postIndex) {
    if (inStart > inEnd)
        return NULL;

    struct TreeNode* node = newNode(post[*postIndex]);
    (*postIndex)--;

    if (inStart == inEnd)
        return node;

    int inIndex = findIndex(in, inStart, inEnd, node->data);

    node->right = constructUtil(in, post, inIndex + 1, inEnd, postIndex);
    node->left = constructUtil(in, post, inStart, inIndex - 1, postIndex);

    return node;
}

// Function to construct BST
struct TreeNode* bst_construct(int in[], int post[], int n) {
    int postIndex = n - 1;
    return constructUtil(in, post, 0, n - 1, &postIndex);
}

// Function to print nodes of a binary tree in BFS order
void printBFS(struct TreeNode* root) {
    if (root == NULL)
        return;

    // Create a queue for BFS
    struct TreeNode* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        struct TreeNode* tempNode = queue[front++];
        printf("%d ", tempNode->data);

        if (tempNode->left != NULL)
            queue[rear++] = tempNode->left;
        if (tempNode->right != NULL)
            queue[rear++] = tempNode->right;
    }
}

// Main function
int main() {
    int inOrder[] = {5, 10, 15, 20, 25, 30, 45};
    int postOrder[] = {5, 15, 10, 25, 45, 30, 20};
    int n = sizeof(inOrder) / sizeof(inOrder[0]);

    // Construct BST
    struct TreeNode* root = bst_construct(inOrder, postOrder, n);

    // Print BST in BFS order
    printf("BFS traversal of constructed BST: ");
    printBFS(root);
    printf("\n");

    return 0;
}

