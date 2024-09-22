/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *link;
} *top = NULL; // Initialize top to NULL

int count = 0;

void push(int data) {
    // Allocate memory for the new node
    struct node *temp = (struct node*)malloc(sizeof(struct node));
    if (temp == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    // Set the new node's data and link
    temp->data = data;
    temp->link = top; // Link the new node to the previous top
    top = temp; // Update top to the new node
    count++;
    printf("Node with data %d is inserted\n", data);
}



    // Optionally print the stack to verify
    void display(){
    struct node *current = top;
    printf("Current stack (top to bottom): ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->link;
    }
    printf("\n");
}
    
    int main() {
    push(90);
    push(10);
    display();

    return 0;
}
