// Girilen metnin palindrom olup olmadığını stack ve queue yapısı kullanarak kontrol eden programı yazınız.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_STR_SIZE 100

typedef struct {
    int front, rear;
    size_t size;
    char *data;
} Queue;

typedef struct {
    int top;
    size_t size;
    char *data;
} Stack;

Stack *createStack(size_t size);
void push(Stack *stack, char c);
char pop(Stack *stack);
char peek(Stack *stack);
bool isStackEmpty(Stack *stack);
bool isStackFull(Stack *stack);
void freeStack(Stack *stack);

Queue *createQueue(size_t size);
void enqueue(Queue *queue, char c);
int dequeue(Queue *queue);
bool isQueueEmpty(Queue *queue);
bool isQueueFull(Queue *queue);
void freeQueue(Queue *queue);

bool isPalindrome(Stack *stack, Queue *queue, const char *text);

int main(void){

    Stack *stack = createStack(MAX_STR_SIZE);
    if (stack == NULL) {
        fprintf(stderr, "Memory allocation failed for the stack!\n");
        exit(EXIT_FAILURE);
    }

    Queue *queue = createQueue(MAX_STR_SIZE);
    if (queue == NULL) {
        fprintf(stderr, "Memory allocation failed for the queue!\n");
        exit(EXIT_FAILURE);
    }

    char text[MAX_STR_SIZE];
    printf("Please enter a text: ");
    if ((fgets(text, MAX_STR_SIZE, stdin)) == NULL) {
        fprintf(stderr, "Failed to read input!\n");
        exit(EXIT_FAILURE);
    }

    text[strcspn(text,"\n")] = '\0';

    if (isPalindrome(stack, queue, text))
        printf("true");
    else
        printf("false");


    freeStack(stack);
    freeQueue(queue);

    return 0;
}

// Parametre olarak gönderilen metnin palindrom olup olmadığını kontrol eder
bool isPalindrome(Stack *stack, Queue *queue, const char *text){
    int i;
    // Metinde bulunan alfabetik karakterleri stack ve queue yapısına ekler
    for (i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            push(stack, tolower(text[i]));
            enqueue(queue, tolower(text[i]));
        }
    }
    while (!isQueueEmpty(queue)) {
        // Stack'ten çıkarılan karakter ile queue yapısından çıkarılan karakter eşit değil ise 'false' döndürür
        if (pop(stack) != dequeue(queue))
            return false;
    }
    return true;
}

Queue *createQueue(size_t size){
    Queue *queue = malloc(sizeof(Queue));
    if (queue != NULL) {
        queue->data = malloc(sizeof(char) * size);
        if (queue->data != NULL) {
            queue->front = 0;
            queue->rear = -1;
            queue->size = size;
        }
        else {
            free(queue);
            return NULL;
        }
    }
}

void enqueue(Queue *queue, char c){
    if (isQueueFull(queue)) {
        fprintf(stderr, "Queue is full!\n");
        return;
    }
    queue->data[++queue->rear] = c;
}

int dequeue(Queue *queue){
    if (isQueueEmpty(queue)) {
        fprintf(stderr, "Queue is empty!\n");
        return -1;
    }
    return queue->data[queue->front++];
}

bool isQueueEmpty(Queue *queue){
    return queue->front == queue->rear;
}

bool isQueueFull(Queue *queue){
    return queue->rear == queue->size;
}

void freeQueue(Queue *queue){
    if (queue != NULL) {
        free(queue->data);
        free(queue);
    }
}

Stack *createStack(size_t size){
    Stack *stack = malloc(sizeof(Stack));
    if (stack != NULL) {
        stack->data = malloc(sizeof(char) * size);
        if (stack->data != NULL) {
            stack->top = -1;
            stack->size = size;
        }
        else {
            free(stack);
            return NULL;
        }
    }
    return stack;
}

void push(Stack *stack, char c){
    if (isStackFull(stack)) {
        fprintf(stderr, "Stack is full!\n");
        return;
    }
    stack->data[++stack->top] = c;
}

char pop(Stack *stack){
    if (isStackEmpty(stack)) {
        fprintf(stderr, "Stack is empty!\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top--];
}

char peek(Stack *stack){
    if (isStackEmpty(stack)) {
        fprintf(stderr, "Stack is empty!\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top];
}

bool isStackEmpty(Stack *stack){
    return stack->top == -1;
}

bool isStackFull(Stack *stack){
    return stack->top == stack->size - 1;
}

void freeStack(Stack *stack){
    if (stack != NULL) {
        free(stack->data);
        free(stack);
    }
}