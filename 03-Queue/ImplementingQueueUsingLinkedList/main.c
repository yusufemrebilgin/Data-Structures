#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ERROR_VALUE -1

typedef struct Node {
    int data;
    struct Node *next;
} QueueNode;

typedef struct _Queue {
    QueueNode *front;
    QueueNode *rear;
} Queue;

Queue *createQueue(void);
QueueNode *createNode(int data);
void enqueue(Queue *queue, int data);
int dequeue(Queue *queue);
bool isEmpty(Queue *queue);
void freeQueue(Queue *queue);

int main(void){

    Queue *queue = createQueue();

    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    dequeue(queue);
    dequeue(queue);
    enqueue(queue, 40);
    enqueue(queue, 50);

    printf("Queue front: %d\n", queue->front->data);
    printf("Queue rear:  %d\n", queue->rear->data);

    return 0;
}

Queue *createQueue(void){
    Queue *queue = malloc(sizeof(Queue));
    if (queue == NULL) {
        fprintf(stderr, "Memory allocation failed for the queue!");
        exit(EXIT_FAILURE);
    }
    queue->front = queue->rear = NULL;
    return queue;
}

QueueNode *createNode(int data){
    QueueNode *newNode = malloc(sizeof(QueueNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed for the queue node!");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void enqueue(Queue *queue, int data){
    QueueNode *newNode = createNode(data);
    if (isEmpty(queue))
        queue->front = queue->rear = newNode;
    else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

int dequeue(Queue *queue){
    if (isEmpty(queue)) {
        fprintf(stderr, "Queue is empty!\n");
        return ERROR_VALUE;
    }
    QueueNode *temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL)
        queue->rear = NULL;
    int value = temp->data;
    free(temp);
    return value; 
}

bool isEmpty(Queue *queue){
    return (queue->front == NULL) ? true : false;
}

void freeQueue(Queue *queue){
    while (!isEmpty(queue)) {
        dequeue(queue);
    }
    free(queue);
}