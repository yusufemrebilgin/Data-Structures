#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define STACK_EMPTY -1 //Stack'in boş olduğunu temsil eden indis değeri

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
    printf("\nPushed item --> %d\n\n", data);
}

//Stack'in en üstünde bulunan elemanı çıkarır
int pop(Stack *stack){
    if (isEmpty(stack)) {
        fprintf(stderr, "Stack is empty!\n\n");
        return INT_MIN;
    }
    return stack->array[stack->top--];
}

//Stack'in en üstündeki elemanın değerini döndürür (Eleman stack'in tepesinde kalmaya devam eder)
int peek(Stack *stack){
    if (isEmpty(stack)) {
        fprintf(stderr, "Stack is empty!\n\n");
        return INT_MIN;
    }
    return stack->array[stack->top];
}

//Stack'te belirli bir değeri arar
bool search(Stack *stack, int value){
    if (isEmpty(stack))
        return false;
    
    int i;
    for (i = 0; i <= stack->top; i++) {
        if (stack->array[i] == value)
            return true;
    }
    return false;
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
    printf("\n");
}

//Stack için ayrılan belleği geri iade eder
void freeStack(Stack *stack){
    if (stack != NULL) {
        free(stack->array);
        free(stack);
    }
}
