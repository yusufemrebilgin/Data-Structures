#ifndef STACK_H
#define STACK_H

#include <stddef.h>
#include <stdbool.h>

typedef struct _Stack {
    int top;
    size_t size;
    int *array;
} Stack;

Stack *createStack(size_t initialSize);
void push(Stack *stack, int data);
int pop(Stack *stack);
int peek(Stack *stack);
bool search(Stack *stack, int value);
bool isEmpty(Stack *stack);
bool isFull(Stack *stack);
void printStack(Stack *stack);
void freeStack(Stack *stack);

#endif