#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int top;
    size_t size;
    void **data;
} GenericStack;

GenericStack *createGenericStack(size_t size);
void push(GenericStack *stack, void *var);
void *pop(GenericStack *stack);
void *peek(GenericStack *stack);
bool isEmpty(GenericStack *stack);
bool isFull(GenericStack *stack);
void freeStack(GenericStack *stack);

int main(void){

    GenericStack *stack = createGenericStack(5);

    int a = 34;
    char b = 'F';
    double c = 3.45566;
    float d = 6.7f;

    struct User {
        int age;
        char *name;
    } u1 = {22, "Yusuf"};

    push(stack, &a);
    push(stack, &b);
    push(stack, &c);
    push(stack, &d);
    push(stack, &u1);

    void *out = pop(stack);
    printf("user->name: %s\n", ((struct User *)out)->name);

    out = pop(stack);
    printf("float: %.2f\n", *((float *)out));
    
    out = pop(stack);
    printf("double: %lf\n", *((double *)out));
    
    out = pop(stack);
    printf("char: %c\n", *((char *)out));

    out = pop(stack);
    printf("int: %d\n", *((int *)out));

    freeStack(stack);

    return 0;
}

GenericStack *createGenericStack(size_t size){
    GenericStack *stack = malloc(sizeof(GenericStack));
    if (stack == NULL) {
        fprintf(stderr, "Memory allocation failed for the stack!");
        exit(EXIT_FAILURE);
    }
    
    if ((stack->data = malloc(sizeof(void *) * size)) == NULL) {
        fprintf(stderr, "Memory allocation failed for the stack data!");
        free(stack);
        exit(EXIT_FAILURE);
    }
    stack->top = -1;
    stack->size = size;
    return stack;
}

void push(GenericStack *stack, void *var){
    if (isFull(stack)) {
        fprintf(stderr, "Stack is full!\n");
        return;
    }
    stack->data[++stack->top] = var;
}

void *pop(GenericStack *stack){
    if (isEmpty(stack)) {
        fprintf(stderr, "Stack is empty!\n");
        return NULL;
    }
    return stack->data[stack->top--];
}

void *peek(GenericStack *stack){
    if (isEmpty(stack)) {
        fprintf(stderr, "Stack is empty!\n");
        return NULL;
    }
    return stack->data[stack->top];
}

bool isEmpty(GenericStack *stack){
    return stack->top == -1;
}

bool isFull(GenericStack *stack){
    return stack->top == stack->size - 1;
}

void freeStack(GenericStack *stack){
    if (stack != NULL) {
        free(stack->data);
        free(stack);
    }
}