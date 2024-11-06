#include <stdio.h>
#include <stdlib.h>

#define ORDER 3

typedef struct BTreeNode {
    int keys[ORDER - 1];  
    struct BTreeNode* children[ORDER];  
    int numKeys;  
    int leaf;  
} BTreeNode;

BTreeNode* createNode(int leaf) {
    BTreeNode* newNode = (BTreeNode*)malloc(sizeof(BTreeNode));
    newNode->leaf = leaf;
    newNode->numKeys = 0;

    for (int i = 0; i < ORDER; i++) {
        newNode->children[i] = NULL;
    }

    return newNode;
}

BTreeNode* search(BTreeNode* root, int key) {
    if (!root) {
        return NULL;
    }

    int i = 0;
    while (i < root->numKeys && key > root->keys[i]) {
        i++;
    }

    if (i < root->numKeys && key == root->keys[i]) {
        return root;  
    }

    if (root->leaf) {
        return NULL;  
    }

    return search(root->children[i], key); 
}

void splitChild(BTreeNode* parent, int childIndex, BTreeNode* child) {
    BTreeNode* newChild = createNode(child->leaf);
    newChild->numKeys = ORDER / 2;

    for (int i = 0; i < ORDER / 2; i++) {
        newChild->keys[i] = child->keys[i + ORDER / 2];
    }

    if (!child->leaf) {
        for (int i = 0; i < ORDER / 2 + 1; i++) {
            newChild->children[i] = child->children[i + ORDER / 2];
        }
    }

    child->numKeys = ORDER / 2;
    for (int i = parent->numKeys; i > childIndex; i--) {
        parent->children[i + 1] = parent->children[i];
    }

    parent->children[childIndex + 1] = newChild;

    for (int i = parent->numKeys - 1; i >= childIndex; i--) {
        parent->keys[i + 1] = parent->keys[i];
    }

    parent->keys[childIndex] = child->keys[ORDER / 2 - 1];
    parent->numKeys++;
}

void insertNonFull(BTreeNode* node, int key) {
    int i = node->numKeys - 1;

    if (node->leaf) {
        while (i >= 0 && node->keys[i] > key) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }

        node->keys[i + 1] = key;
        node->numKeys++;
    } else {
        while (i >= 0 && node->keys[i] > key) {
            i--;
        }

        i++;

        if (node->children[i]->numKeys == ORDER - 1) {
            splitChild(node, i, node->children[i]);
 
            if (node->keys[i] < key) {
                i++;
            }
        }

        insertNonFull(node->children[i], key);
    }
}

void insert(BTreeNode** root, int key) {
    BTreeNode* r = *root;

    if (r->numKeys == ORDER - 1) {
        BTreeNode* s = createNode(0);
        s->children[0] = r;
        splitChild(s, 0, r);
        *root = s;
        insertNonFull(s, key);
    } else {
        insertNonFull(r, key);
    }
}

void inorderTraversal(BTreeNode* root) {
    if (!root) {
        return;
    }

    int i;
    for (i = 0; i < root->numKeys; i++) {
        if (!root->leaf) {
            inorderTraversal(root->children[i]);
        }
        printf("%d ", root->keys[i]);
    }

    if (!root->leaf) {
        inorderTraversal(root->children[i]);
    }
}
int main() {
    BTreeNode* root = createNode(1);  
    int choice, key;

    while (1) {
        printf("\nB-Tree Operations Menu:\n");
        printf("1. Insert a key\n");
        printf("2. Search for a key\n");
        printf("3. Print in-order traversal\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the key to insert: ");
                scanf("%d", &key);
                insert(&root, key);
                printf("Key %d inserted into the B-tree.\n", key);
                break;

            case 2:
                printf("Enter the key to search for: ");
                scanf("%d", &key);
                BTreeNode* searchResult = search(root, key);
                if (searchResult) {
                    printf("Key %d found in the B-tree.\n", key);
                } else {
                    printf("Key %d not found in the B-tree.\n", key);
                }
                break;

            case 3:
                printf("In-order traversal of the B-tree: \n");
                inorderTraversal(root);
                printf("\n");
                break;

            case 4:
                printf("Exiting program.\n");
                exit(0);

            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}
