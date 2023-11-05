#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

typedef struct _Stack {
    Node *top;
} Stack;

Stack *createStack(void);
void push(Stack *stack, int data);
int pop(Stack *stack);
int peek(Stack *stack);
bool isEmpty(Stack *stack);
void printStack(Stack *stack);
void freeStack(Stack *stack);

int main(void){

    Stack *stack = createStack();
    if (stack == NULL) {
        fprintf(stderr, "Memory allocation failed for the stack!\n");
        exit(EXIT_FAILURE);
    }
    
    int choice = -1;

    while (true) {
        printf("**************************\n"
               "1.Push\n"
               "2.Pop\n"
               "3.Peek\n"
               "4.Print\n"
               "0.Exit\n\n"
               "Enter your choice: ");

        scanf("%d", &choice);
        printf("\n");
        switch (choice) {
        case 1: {
            int value;
            printf("Please enter a value: ");
            scanf("%d", &value);
            push(stack, value);
            break;
        }
        case 2: {
            int value = pop(stack);
            if (value != -1)
                printf("Popped item --> %d\n", value);
            break;
        }
        case 3: {
            int value = peek(stack);
            if (value != -1)
                printf("Element at the top of the list: %d\n", value);
            break;
        }
        case 4:
            printStack(stack);
            break;
        case 0:
            freeStack(stack);
            exit(EXIT_SUCCESS);
            break;
        default:
            printf("Invalid option..\n\n");
            break;
        }
    }

    return 0;
}

Stack *createStack(void){
    Stack *stack = malloc(sizeof(Stack));
    if (stack != NULL) {
        stack->top = NULL;
    }
    return stack;
}

void push(Stack *stack, int data){
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed for the new node!\n");
        freeStack(stack);
        exit(EXIT_FAILURE);
    }
    else {
        newNode->data = data;
        newNode->next = NULL;
    }
    newNode->next = stack->top;
    stack->top = newNode;
}

int pop(Stack *stack){
    if (isEmpty(stack)) {
        fprintf(stderr, "Stack is empty!\n");
        return -1;
    }
    Node *temp = stack->top;
    int data = stack->top->data;
    stack->top = stack->top->next;
    free(temp);
    return data;
}

int peek(Stack *stack){
    if (isEmpty(stack)) {
        fprintf(stderr, "Stack is empty!\n");
        return -1;
    }
    return stack->top->data;
}

bool isEmpty(Stack *stack){
    return stack->top == NULL;
}

void printStack(Stack *stack){
    if (isEmpty(stack)) {
        fprintf(stderr, "Stack is empty!\n");
        return;
    }
    Node *iter = stack->top;
    while (iter != NULL) {
        printf("%d -> ", iter->data);
        iter = iter->next;
    }
    printf("\n\n");
}

void freeStack(Stack *stack){
    if (stack != NULL) {
        while (stack->top != NULL) {
            Node *temp = stack->top;
            stack->top = stack->top->next;
            free(temp);
        }
        free(stack);
    }
}