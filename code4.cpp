#include <stdio.h>
#include <stdlib.h>

// Structure for a node in the binary search tree
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a node into the binary search tree
struct Node* insertNode(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
    }
    return root;
}

// Function to delete a node from the binary search tree
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) {
        return root;
    }
    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        // Case 1: Node with only one child or no child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Case 2: Node with two children
        struct Node* temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to calculate the height of the binary search tree
int height(struct Node* root) {
    if (root == NULL) {
        return -1; // Empty tree has height -1
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Function to print the level and height of a given node
void printLevelAndHeight(struct Node* root, int key, int level) {
    if (root == NULL) {
        printf("Node not found.\n");
        return;
    }
    if (root->data == key) {
        printf("Level: %d\n", level);
        printf("Height: %d\n", height(root));
        return;
    }
    if (key < root->data) {
        printLevelAndHeight(root->left, key, level + 1);
    } else {
        printLevelAndHeight(root->right, key, level + 1);
    }
}

int main() {
    int arr[] = {30, 20, 10, 25, 40, 35, 45, 5, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    struct Node* root = NULL;

    // Create BST from array
    for (int i = 0; i < n; i++) {
        root = insertNode(root, arr[i]);
    }

    // Print the height of the BST
    printf("Height of the BST: %d\n", height(root));

    // Print level and height of a given node (e.g., 40)
    int key = 40;
    printf("Details for node with value %d:\n", key);
    printLevelAndHeight(root, key, 0);

    return 0;
}

