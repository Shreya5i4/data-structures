#include <stdio.h>
#include <stdlib.h>

// Define Node structure
struct Node {
    int data;
    struct Node* next;
};

// Define Queue structure
struct Queue {
    struct Node* front;
    struct Node* rear;
};

// Function to initialize the queue
void initQueue(struct Queue* q) {
    q->front = q->rear = NULL;
}

// Enqueue function (insert element at the rear of the queue)
void enqueue(struct Queue* q, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    
    // If queue is empty, both front and rear are the same
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        printf("%d enqueued to queue\n", value);
        return;
    }
    
    // Add the new node at the end and move the rear
    q->rear->next = newNode;
    q->rear = newNode;
    printf("%d enqueued to queue\n", value);
}

// Dequeue function (remove element from the front of the queue)
void dequeue(struct Queue* q) {
    if (q->front == NULL) {
        printf("Queue is empty!\n");
        return;
    }
    
    struct Node* temp = q->front;
    q->front = q->front->next;
    
    // If the front is NULL, the queue becomes empty, so set rear to NULL
    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    printf("%d dequeued from queue\n", temp->data);
    free(temp);
}

// Display the queue
void displayQueue(struct Queue* q) {
    if (q->front == NULL) {
        printf("Queue is empty!\n");
        return;
    }
    
    struct Node* temp = q->front;
    printf("Queue: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Main function
int main() {
    struct Queue q;
    initQueue(&q);
    
    int choice, value;
    
    while (1) {
        printf("\n1. Enqueue\n2. Dequeue\n3. Display Queue\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                enqueue(&q, value);
                break;
            case 2:
                dequeue(&q);
                break;
            case 3:
                displayQueue(&q);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }
    
    return 0;
}