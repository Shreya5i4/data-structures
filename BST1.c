/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

// Definition of a BST Node
struct BST {
    int key;
    struct BST *left, *right;
};

// Function to create a new node
struct BST *newNode(int value) {
    struct BST *temp = (struct BST*)malloc(sizeof(struct BST));
    temp->key = value;
    temp->left = temp->right = NULL;
    return temp;
}

// Function to insert a node into the BST
struct BST *insertNode(struct BST *node, int value) {
    if (node == NULL) {
        return newNode(value); // Create a new node if position is found
    }
    if (value < node->key) {
        node->left = insertNode(node->left, value); // Insert into left subtree
    } else if (value > node->key) {
        node->right = insertNode(node->right, value); // Insert into right subtree
    }
    return node;
}

// Function to search for a node with a given value
struct BST *searchNode(struct BST *root, int target) {
    if (root == NULL || root->key == target) {
        return root; // Return the node if found
    }
    if (root->key < target) {
        return searchNode(root->right, target); // Search in right subtree
    }
    return searchNode(root->left, target); // Search in left subtree
}

// Function for pre-order traversal
void preOrder(struct BST *root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(struct BST *root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->key);
    }
}

void inOrder(struct BST *root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

struct BST *minValueNode(struct BST *node) {
    struct BST *current = node;
   
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Function to delete a node from the BST
struct BST *deleteNode(struct BST *root, int key) {
    if (root == NULL) {
        printf("Element not found\n");
        return root;
    }
    if (key < root->key) {
        root->left = deleteNode(root->left, key); // Go to left subtree
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key); // Go to right subtree
    } else {
        // Node with only one child or no child
        if (root->left == NULL) {
            struct BST *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct BST *temp = root->left;
            free(root);
            return temp;
        }
        // Node with two children: Get the inorder successor (smallest in the right subtree)
        struct BST *temp = minValueNode(root->right);
        // Copy the inorder successor’s content to this node
        root->key = temp->key;
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

// Main function to test the BST functions
int main() {
    struct BST *root = NULL;
    int choice, value;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert Node\n");
        printf("2. Search Node\n");
        printf("3. Delete Node\n");
        printf("4. In-order Traversal\n");
        printf("5. Pre-order Traversal\n");
        printf("6. Post-order Traversal\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Insert Node
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insertNode(root, value);
                printf("Inserted %d\n", value);
                break;

            case 2: // Search Node
                printf("Enter value to search: ");
                scanf("%d", &value);
                if (searchNode(root, value) != NULL) {
                    printf("Node %d found!\n", value);
                } else {
                    printf("Node %d not found!\n", value);
                }
                break;

            case 3: // Delete Node
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                printf("Deleted %d if it existed.\n", value);
                break;

            case 4: // In-order Traversal
                printf("In-order Traversal: ");
                inOrder(root);
                printf("\n");
                break;

            case 5: // Pre-order Traversal
                printf("Pre-order Traversal: ");
                preOrder(root);
                printf("\n");
                break;

            case 6: // Post-order Traversal
                printf("Post-order Traversal: ");
                postOrder(root);
                printf("\n");
                break;

            case 7: // Exit
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}