#include <stdio.h>
#include <stdlib.h>

#define MAX 3  // Max number of nodes in the graph

void DFS(int adj[][MAX], int visited[], int start);

int main() {
    int visited[MAX] = {0};
    int adj[MAX][MAX];
    int i, j;

    // Input adjacency matrix
    printf("Enter the values into the adjacency matrix (5x5 for this example):\n");
    for (i = 0; i < MAX; i++) {
        for (j = 0; j < MAX; j++) {
            scanf("%d", &adj[i][j]);
        }
    }

    // DFS traversal
    printf("DFS Traversal is:\n");
    DFS(adj, visited, 0);  // Start DFS from node 0 (A)
    
    return 0;
}

// DFS function using a stack
void DFS(int adj[][MAX], int visited[], int start) {
    int s[MAX];  // Stack to hold nodes for DFS
    int top = -1, i, k;

    // Mark all nodes as not visited initially
    for (k = 0; k < MAX; k++) {
        visited[k] = 0;
    }

    // Push the start node onto the stack
    s[++top] = start;
    visited[start] = 1;

    // DFS traversal loop
    while (top != -1) {
        // Pop the top node from the stack
        start = s[top--];
        printf("%c -- ", start + 65);  // Print the node as a character ('A' = 65, 'B' = 66, etc.)

        // Explore all the adjacent nodes
        for (i = 0; i < MAX; i++) {
            // If there's an edge and the node hasn't been visited
            if (adj[start][i] && visited[i] == 0) {
                s[++top] = i;  // Push the unvisited adjacent node onto the stack
                visited[i] = 1; // Mark the node as visited
            }
        }
    }
}
