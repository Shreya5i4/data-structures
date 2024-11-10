#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ORDER 3

typedef struct BPlusTreeNode {
    int *keys;  
    void **children; 
    bool isLeaf;  
    int numKeys;  
} BPlusTreeNode;

typedef struct BPlusTree {
    BPlusTreeNode *root;  
} BPlusTree;

BPlusTreeNode* createNode(bool isLeaf) {
    BPlusTreeNode *node = (BPlusTreeNode *)malloc(sizeof(BPlusTreeNode));
    node->isLeaf = isLeaf;
    node->keys = (int *)malloc((ORDER - 1) * sizeof(int));
    node->children = (void **)malloc(ORDER * sizeof(void *));
    node->numKeys = 0;
    return node;
}

BPlusTreeNode* search(BPlusTree *tree, int key) {
    BPlusTreeNode *currentNode = tree->root;
    
    while (!currentNode->isLeaf) {
        int i = 0;

        while (i < currentNode->numKeys && key >= currentNode->keys[i]) {
            i++;
        }
        currentNode = (BPlusTreeNode *)currentNode->children[i];
    }

    for (int i = 0; i < currentNode->numKeys; i++) {
        if (currentNode->keys[i] == key) {
            return currentNode; 
        }
    }
    return NULL; 
}

void splitChild(BPlusTree *tree, BPlusTreeNode *parent, int index, BPlusTreeNode *fullChild) {
    int midIndex = ORDER / 2;
    
    BPlusTreeNode *newChild = createNode(fullChild->isLeaf);
    newChild->numKeys = ORDER - 1 - midIndex;
    for (int i = 0; i < newChild->numKeys; i++) {
        newChild->keys[i] = fullChild->keys[midIndex + 1 + i];
        newChild->children[i] = fullChild->children[midIndex + 1 + i];
    }

    fullChild->numKeys = midIndex;

    for (int i = parent->numKeys; i > index; i--) {
        parent->children[i + 1] = parent->children[i];
        parent->keys[i] = parent->keys[i - 1];
    }
    parent->keys[index] = fullChild->keys[midIndex];
    parent->children[index + 1] = newChild;
    parent->numKeys++;
}

void insertNonFull(BPlusTree *tree, BPlusTreeNode *node, int key) {
    if (node->isLeaf) {
        int i = node->numKeys - 1;
        
        while (i >= 0 && node->keys[i] > key) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->numKeys++;
    } else {
        int i = node->numKeys - 1;
        while (i >= 0 && node->keys[i] > key) {
            i--;
        }
        i++;

        BPlusTreeNode *childNode = (BPlusTreeNode *)node->children[i];
        if (childNode->numKeys == ORDER - 1) {
         
            splitChild(tree, node, i, childNode);
            if (node->keys[i] < key) {
                i++;
            }
        }
        insertNonFull(tree, (BPlusTreeNode *)node->children[i], key);
    }
}

void insert(BPlusTree *tree, int key) {
    BPlusTreeNode *root = tree->root;

    if (root->numKeys == ORDER - 1) {
        
        BPlusTreeNode *newRoot = createNode(false);
        newRoot->children[0] = root;
        tree->root = newRoot;
        splitChild(tree, newRoot, 0, root);
        insertNonFull(tree, newRoot, key);
    } else {
        insertNonFull(tree, root, key);
    }
}
void printTree(BPlusTreeNode *node) {
    if (node != NULL) {
        for (int i = 0; i < node->numKeys; i++) {
            if (!node->isLeaf) {
                printTree((BPlusTreeNode *)node->children[i]);
            }
            printf("%d ", node->keys[i]);
        }
        if (!node->isLeaf) {
            printTree((BPlusTreeNode *)node->children[node->numKeys]);
        }
    }
}

int main() {
    BPlusTree tree;
    tree.root = createNode(true); 

    int numKeys, key;
    
    printf("Enter number of keys to insert: ");
    scanf("%d", &numKeys);

    printf("Enter the keys:\n");
    for (int i = 0; i < numKeys; i++) {
        scanf("%d", &key);
        insert(&tree, key);
    }

    printf("In-order traversal of the B+ Tree:\n");
    printTree(tree.root);
    printf("\n");

    printf("Enter a key to search: ");
    scanf("%d", &key);
    BPlusTreeNode *searchResult = search(&tree, key);
    if (searchResult) {
        printf("Key %d found in the B+ Tree.\n", key);
    } else {
        printf("Key %d not found in the B+ Tree.\n", key);
    }

    return 0;
}
