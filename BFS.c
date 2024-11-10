#include <stdio.h>

#define MAX 3 // Max number of nodes in the graph

void BFS(int adj[][MAX], int visited[], int start);

int main() {
    int visited[MAX] = {0};
    int adj[MAX][MAX];
    int i, j;

    printf("Enter the values into the adjacency matrix (5x5 for this example):\n");
    for (i = 0; i < MAX; i++) {
        for (j = 0; j < MAX; j++) {
            scanf("%d", &adj[i][j]);
        }
    }

    printf("BFS Traversal is:\n");
    BFS(adj, visited, 0);  // Start BFS from node 0
    return 0;
}

void BFS(int adj[][MAX], int visited[], int start) {
    int q[MAX], rear = -1, front = -1, i;

    // Mark all nodes as not visited initially
    for (i = 0; i < MAX; i++) {
        visited[i] = 0;
    }

    // Enqueue the starting node
    q[++rear] = start; 
    visited[start] = 1;

    while (rear >= front) {
        start = q[front++];  // Dequeue the front element
        printf("%c -- ", start + 65);  // Print the node (ASCII A=65, B=66, etc.)
        
        // Check all adjacent nodes
        for (i = 0; i < MAX; i++) {
            if (adj[start][i] == 1 && !visited[i]) {
                q[++rear] = i;  // Enqueue the unvisited adjacent node
                visited[i] = 1;  // Mark the node as visited
            }
        }
    }
}
