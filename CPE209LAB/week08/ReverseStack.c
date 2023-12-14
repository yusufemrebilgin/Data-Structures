#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _Stack {
    int top;
    size_t size;
    int *array;
} Stack;

Stack *createStack(size_t initialSize);
void push(Stack *stack, int data);
int pop(Stack *stack);
bool isEmpty(Stack *stack);
bool isFull(Stack *stack);
void printStack(Stack *stack);
void freeStack(Stack *stack);

Stack *reverseStack(Stack *stack);

#define STACK_EMPTY -1 //Stack'in boş olduğunu temsil eden indis değeri

int main(void){

    Stack *stack = createStack(5);

    int i;
    for (i = 0; i < 5; i++)
        push(stack, i * 10 + 1);
    
    printf("Before reversing the stack:\n");
    printStack(stack);

    stack = reverseStack(stack);

    printf("After reversing the stack:\n");
    printStack(stack);

    freeStack(stack);

    return 0;
}

Stack *reverseStack(Stack *stack){
    Stack *reversedStack = createStack(stack->size);
    if (reversedStack == NULL) {
        fprintf(stderr, "Memory allocation failed for the stack!");
        exit(EXIT_FAILURE);
    }
    while (!isEmpty(stack))
        push(reversedStack, pop(stack));
    
    freeStack(stack);
    return reversedStack;
}

//Stack oluşturmak için fonksiyon
Stack *createStack(size_t initialSize){
    Stack *stack;
    if ((stack = malloc(sizeof(Stack))) != NULL) {
        stack->array = malloc(sizeof(int) * initialSize);
        if (stack->array != NULL) {
            stack->top = STACK_EMPTY;
            stack->size = initialSize;
        } else {
            free(stack);
            return NULL;
        }
    }
    return stack;
}

//Stack'in tepesine eleman ekler
void push(Stack *stack, int data){
    if (isFull(stack)) {
        fprintf(stderr, "\nStack is full!\n\n");
        return;
    }
    stack->array[++stack->top] = data;
}

//Stack'in en üstünde bulunan elemanı çıkarır
int pop(Stack *stack){
    if (isEmpty(stack)) {
        fprintf(stderr, "Stack is empty!\n\n");
        return -1;
    }
    return stack->array[stack->top--];
}

//Stack'in boş olup olmadığını kontrol eder
bool isEmpty(Stack *stack){
    return stack->top == STACK_EMPTY;
}

//Stack'in dolu olup olmadığını kontrol eder
bool isFull(Stack *stack){
    return stack->top == stack->size - 1;
}

//Stack içeriğini ekrana basar
void printStack(Stack *stack){
    if (isEmpty(stack)) {
        fprintf(stderr, "Stack is empty!\n\n");
        return;
    }
    int index;
    for (index = stack->top; index >= 0; index--) {
        printf("[%02d] --> %d\n", index, stack->array[index]);
    }
    printf("\n\n");
}

//Stack için ayrılan belleği geri iade eder
void freeStack(Stack *stack){
    if (stack != NULL) {
        free(stack->array);
        free(stack);
    }
}