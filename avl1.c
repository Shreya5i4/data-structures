#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};
int max(int a, int b) {
    return (a > b) ? a : b;
}
int height(struct Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}
struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; 
    return node;
}

struct Node *rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

struct Node *leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(struct Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Recursive function to insert a key in the subtree rooted with node and returns the new root of the subtree.
struct Node* insertNode(struct Node* node, int key) {
    // Perform the normal BST insertion
    if (node == NULL)
        return(newNode(key));
    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else
        return node; // Equal keys are not allowed in BST

    // Update height of this ancestor node
    node->height = 1 + max(height(node->left), height(node->right));

    // Get the balance factor of this ancestor node to check whether this node became unbalanced
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases
    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the (unchanged) node pointer
    return node;
}

// A utility function to find the node with the minimum value
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;

    // Loop down to find the leftmost leaf
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

// Recursive function to delete a node from the subtree rooted with node and returns the new root of the subtree.
struct Node* deleteNode(struct Node* root, int key) {
    // STEP 1: PERFORM STANDARD BST DELETE
    if (root == NULL) {
        printf("Element not found\n");
        return root;
    }

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL)) {
            struct Node *temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else // One child case
                *root = *temp; // Copy the contents of the non-empty child
            free(temp);
        } else {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            struct Node *temp = minValueNode(root->right);
            // Copy the inorder successor’s content to this node
            root->key = temp->key;
            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // If the tree had only one node then return
    if (root == NULL)
        return root;

    // STEP 2: UPDATE HEIGHT OF THIS ANCESTOR NODE
    root->height = 1 + max(height(root->left), height(root->right));

    // STEP 3: GET THE BALANCE FACTOR OF THIS ANCESTOR NODE TO CHECK WHETHER THIS NODE BECAME UNBALANCED
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// A utility function to print preorder traversal of the tree.
void printPreOrder(struct Node *root) {
    if (root != NULL) {
        printf("%d ", root->key);
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
}

// A utility function to print inorder traversal of the tree.
void printInOrder(struct Node *root) {
    if (root != NULL) {
        printInOrder(root->left);
        printf("%d ", root->key);
        printInOrder(root->right);
    }
}

// A utility function to print postorder traversal of the tree.
void printPostOrder(struct Node *root) {
    if (root != NULL) {
        printPostOrder(root->left);
        printPostOrder(root->right);
        printf("%d ", root->key);
    }
}

// Function to search for a node with a given key
struct Node* searchNode(struct Node* root, int key) {
    // Base Cases: root is null or key is present at root
    if (root == NULL || root->key == key)
        return root;

    // Key is greater than root's key
    if (key > root->key)
        return searchNode(root->right, key);

    // Key is smaller than root's key
    return searchNode(root->left, key);
}

int main() {
    struct Node *root = NULL;
    int value;
    int choice;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert Node\n");
        printf("2. Delete Node\n");
        printf("3. Search Node\n");
        printf("4. Pre-order Traversal\n");
        printf("5. In-order Traversal\n");
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

            case 2: // Delete Node
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                printf("Deleted %d if it existed.\n", value);
                break;

            case 3: // Search Node
                printf("Enter value to search: ");
                scanf("%d", &value);
                struct Node* searchedNode = searchNode(root, value);
                if (searchedNode != NULL) {
                    printf("Node %d found!\n", value);
                } else {
                    printf("Node %d not found!\n", value);
                }
                break;

            case 4: // Pre-order Traversal
                printf("Pre-order Traversal: ");
                printPreOrder(root);
                printf("\n");
                break;

            case 5: // In-order Traversal
                printf("In-order Traversal: ");
                printInOrder(root);
                printf("\n");
                break;

            case 6: // Post-order Traversal
                printf("Post-order Traversal: ");
                printPostOrder(root);
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