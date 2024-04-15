#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* newNode(int data) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

int findIndex(int arr[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == value)
            return i;
    }
    return -1;
}

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

struct TreeNode* bst_construct(int in[], int post[], int n) {
    int postIndex = n - 1;
    return constructUtil(in, post, 0, n - 1, &postIndex);
}

void printBFS(struct TreeNode* root) {
    if (root == NULL)
        return;

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

int main() {
    int inOrder[] = {5, 10, 15, 20, 25, 30, 45};
    int postOrder[] = {5, 15, 10, 25, 45, 30, 20};
    int n = sizeof(inOrder) / sizeof(inOrder[0]);

    struct TreeNode* root = bst_construct(inOrder, postOrder, n);

    printf("BFS traversal of constructed BST: ");
    printBFS(root);
    printf("\n");

    return 0;
}

