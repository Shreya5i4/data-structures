#include<stdio.h>
#define size 4

int top=-1;
int stack_arr[size];

void push(int data);
void display();

void main(){
    int data;
    printf("enter data to be inserted:\n");
    if(scanf("%d", &data) != 1){  // Add input validation
        printf("Invalid input\n");
        return;
    }
    push(data);
    push(56);
    push(89);
    display();
}

void push(int data){
    if(top == size-1){
        printf("stack is overflow\n");
    }
    else{
        top = top + 1;
        stack_arr[top] = data;
    }
}

void display(){
    if(top == -1){
        printf("stack is empty\n");
        return;
    }
    else{
        for(int i = top; i >= 0; i--){  // Loop from top to 0
            printf("%d\n", stack_arr[i]);
        }
    }
}
