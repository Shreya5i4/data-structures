/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#define size 5
int stack_arr[size];
int top=-1;
void push();
void pop();
void display();
void peak();
int main(){
    int choice;
    while(1){
        printf("\n perform operations on stack\n");
        printf("\n menu\n");
        printf("1.push element\n2.pop element\n3.display stack\n4.peak element\n5.exit\n");
        printf("enter your choice:\n");
        scanf("%d",&choice);
        switch(choice){
            case 1:
            push();
            break;
            case 2:
            pop();
            break;
            case 3:
            display();
            break;
            case 4:
            peak();
            break;
            case 5:
            printf("exiting");
            exit(0);
            default:
            printf("please enter valid choice\n");
        }
    }
}
void push(){
    int data;
    if(top==size-1){
        printf("stack overflow\n");
        
    }
    else{
        printf("enter data to store in stack:\n");
        scanf("%d",&data);
        top=top+1;
        stack_arr[top]=data;
        printf("data is inserted into stack\n");
    }
}
void pop(){
    int value;
    if(top==-1){
        printf("stack is underflow\n");
        
    }
    else{
        printf("popped element:%d",stack_arr[top]);
        value =stack_arr[top];
        top=top-1;
        return value;
    }
}
void display(){
    if(top==-1){
        printf("stack  underflow\n");
        
    }
    else{
        printf("data present in stack is:\n");
        for(int i=top;i>=0;i--)
        printf("%d\n",stack_arr[i]);
    }
}
void peak(){
    if(top==-1){
        printf("stack underflow\n");
        
    }
    else{
        printf("peak element in the stack:\n");
        printf("%d",stack_arr[top]);
    }
}
