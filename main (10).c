#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *link;
};

struct node *top = NULL;
int count = 0;

void push(int data) {
    struct node *temp = (struct node*)malloc(sizeof(struct node));
    if (temp == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    temp->data = data;
    temp->link = top; // Link new node to current top
    top = temp; // Update top to the new node
    count++;
    printf("Node with data %d is inserted\n", data);
}

int pop() {
    if (top == NULL) {
        printf("Stack underflow\n");
        return -1; // Indicate stack is empty
    } else {
        struct node *temp = top;
        int popped_element = top->data;
        top = top->link; // Update top to the next node
        free(temp);
        count--;
        return popped_element;
    }
}

void display() {
    struct node *ptr = top;
    if (ptr == NULL) {
        printf("Stack is empty\n");
        return;
    }
    printf("The stack: ");
    while (ptr != NULL) {
        printf("%d --> ", ptr->data);
        ptr = ptr->link;
    }
    printf("NULL\n");
}

int main() {
    int choice, value;
    while (1) {
        printf("\nStack operations\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to insert: ");
                scanf("%d", &value);
                push(value);
                break;
            case 2:
                printf("Popped element is: %d\n", pop());
                break;
            case 3:
                display();
                break;
            case 4:
                printf("exiting\n");
                exit(0);
            default:
                printf("Enter a valid choice!\n");
        }
    }

    return 0;
}
