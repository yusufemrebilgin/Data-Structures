#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*
    Mapping:
    if node index is i: (assuming root index is zero)
        (i-1) / 2   gives the parent index
        2 * i + 1   gives the left child index
        2 * i + 2   gives the right child index
*/

typedef struct {
    int *arr;
    int size;
    int capacity;
} PriorityQueue;

void swap(int *a, int *b){
    int temp = *b;
    *b = *a;
    *a = temp;
}

PriorityQueue *createPriorityQueue(int initialSize){
    PriorityQueue *priorityQueue = malloc(sizeof(PriorityQueue));
    if (priorityQueue != NULL) {
        if ((priorityQueue->arr = malloc(sizeof(*priorityQueue->arr) * initialSize)) != NULL) {
            priorityQueue->size = 0;
            priorityQueue->capacity = initialSize;
        }
        else {
            free(priorityQueue);
            priorityQueue = NULL;
        }
    }
    return priorityQueue;
}

void heapify(PriorityQueue *queue, int index){
    int smallest = index;
    int leftChild  = 2 * index + 1;
    int rightChild = 2 * index + 2;

    if (leftChild < queue->size && queue->arr[leftChild] < queue->arr[smallest])
        smallest = leftChild;
    if (rightChild < queue->size && queue->arr[rightChild] < queue->arr[smallest])
        smallest = rightChild;
    if (smallest != index) {
        swap(&queue->arr[smallest], &queue->arr[index]);
        heapify(queue, smallest);
    }
}

void enqueue(PriorityQueue *queue, int data){
    if (queue->size == queue->capacity) {
        fprintf(stderr, "Priority Queue is full!\n");
        return;
    }

    int i = queue->size++;
    queue->arr[i] = data;
    
    for (i = queue->size / 2 - 1; i >= 0; i--)
        heapify(queue, i);
}

int dequeue(PriorityQueue *queue){
    if (queue->size == 0) {
        fprintf(stderr, "Priority Queue is empty!\n");
        return INT_MIN;
    }

    int i, min = queue->arr[0];
    queue->arr[0] = queue->arr[queue->size - 1];
    queue->arr[queue->size - 1] = INT_MIN;
    queue->size--;

    for (i = queue->size / 2 - 1; i >= 0; i--)
        heapify(queue, i);
    
    return min;
}

void freePriorityQueue(PriorityQueue **queue){
    if (queue != NULL) {
        free((*queue)->arr);
        free(*queue);
        *queue = NULL;
    }
}

int main(void){
    
    int i, arr[] = {34, 22, 7, 10, 55, 123, 56, 48, 61, 70};
    int size = sizeof(arr) / sizeof(*arr);

    PriorityQueue *priorityQueue = createPriorityQueue(size);
    if (priorityQueue == NULL) {
        fprintf(stderr, "Memory allocation failed for the priority queue!");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < size; i++)
        enqueue(priorityQueue, arr[i]);
    
    for (i = 0; i < size; i++)
        printf("%3d dequed from priority queue\n", dequeue(priorityQueue));
    
    freePriorityQueue(&priorityQueue);
  
    return 0;
}