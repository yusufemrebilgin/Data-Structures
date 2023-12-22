#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

//Using Circular Array
typedef struct _Queue {
    int front, rear, counter;
    size_t size;
    int *data;
} Queue;

Queue *createQueue(size_t size);
void enqueue(Queue *queue, int data);
int dequeue(Queue *queue);
bool isEmpty(Queue *queue);
bool isFull(Queue *queue);
void freeQueue(Queue *queue);

int main(void){

    int size, choice = -1;
    printf("Please enter queue size: ");
    scanf("%d", &size);

    if (size <= 0) {
        fprintf(stderr, "Invalid queue size. Size must be greater than zero.");
        exit(EXIT_FAILURE);
    }

    Queue *queue = createQueue(size);
    if (queue == NULL) {
        fprintf(stderr, "Memory allocation failed for the queue!");
        exit(EXIT_FAILURE);
    }

    printf("\n");

    while (1) {

        printf("**************************\n"
               "1.Enqueue\n"
               "2.Dequeue\n"
               "0.Exit\n\n"
               "Enter your choice: ");
        
        scanf("%d", &choice);
        printf("\n");

        switch (choice) {
            case 1: {
                int value;
                printf("Please enter a value: ");
                scanf("%d", &value);
                enqueue(queue, value);
                break;
            }
            case 2: {
                int popped = dequeue(queue);
                if (popped != INT_MIN)
                    printf("Popped item --> %d\n", popped);
                break;
            }
            case 0:
                freeQueue(queue);
                return EXIT_SUCCESS;
            default:
                printf("Invalid option. Please try again...\n");
                break;
        }
    }
}

Queue *createQueue(size_t size){
    Queue *queue = malloc(sizeof(Queue));
    if (queue != NULL) {
        queue->data = malloc(sizeof(int) * size);
        if (queue->data != NULL) {
            queue->front = 0;
            queue->rear = -1;
            queue->counter = 0;
            queue->size = size;
        }
        else {
            free(queue);
            return NULL;
        }
    }
    return queue;
}

void enqueue(Queue *queue, int data){
    if (isFull(queue)) {
        fprintf(stderr, "Queue is full!\n");
        return;
    }

    queue->rear++;
    queue->counter++; 
    if (queue->rear == queue->size)
        queue->rear = 0;
    queue->data[queue->rear] = data;
    printf("\nPushed item --> %d\n", data);
}

int dequeue(Queue *queue){
    if (isEmpty(queue)) {
        fprintf(stderr, "Queue is empty!\n");
        return INT_MIN;
    }

    int data = queue->data[queue->front++];
    queue->counter--;
    if (queue->front == queue->size)
        queue->front = 0;
    return data;
}

bool isEmpty(Queue *queue){
    return queue->counter == 0;
}

bool isFull(Queue *queue){
    return queue->counter == queue->size; 
}

void freeQueue(Queue *queue){
    if (queue != NULL) {
        free(queue->data);
        free(queue);
    }
}