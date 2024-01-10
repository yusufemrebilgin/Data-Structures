#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

typedef struct {
    int *arr;
    int size;
    int capacity;
} MaxHeap;

MaxHeap *createMaxHeap(int initialSize);
void heapify(MaxHeap *heap, int index);
void insert(MaxHeap *heap, int value);
int delete(MaxHeap *heap);
void swap(int *a, int *b);
void printHeap(MaxHeap *heap);
void freeHeap(MaxHeap **heap);

int main(void){

    MaxHeap *heap = NULL;

    int size, choice = -1;

    printf("Please enter heap size: ");
    scanf("%d", &size);

    if ((heap = createMaxHeap(size)) == NULL) {
        fprintf(stderr, "Memory allocation failed for the heap!");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("************ MAX HEAP ************\n"
               "1. INSERT\n"
               "2. DELETE\n"
               "3. PRINT HEAP\n"
               "0. EXIT\n\n"
               "Last choice: %d\n"
               "Enter your new choice: ", choice);
        
        scanf("%d", &choice);
        printf("\n");

        switch (choice) {
            case 1: {
                int value;
                printf("Please enter a new value: ");
                scanf("%d", &value);
                insert(heap, value);
                break;
            }
            case 2: {
                int max = delete(heap);
                if (max != INT_MIN)
                    printf("Deleted item --> %d\n", max);
                break;
            }
            case 3:
                printHeap(heap);
                break;
            case 0:
                printf("The program has been terminated.");
                freeHeap(&heap);
                return EXIT_SUCCESS;
            default:
                printf("Invalid option. Please try again..");
                break;
        }
        printf("\n");
    }

    return 0;
}

MaxHeap *createMaxHeap(int initialSize){
    MaxHeap *heap = malloc(sizeof(MaxHeap));
    if (heap != NULL) {
        if ((heap->arr = malloc(sizeof(*heap->arr) * initialSize)) != NULL) {
            heap->size = 0;
            heap->capacity = initialSize;
        } else {
            free(heap);
            heap = NULL;
        }
    }
    return heap;
}

void heapify(MaxHeap *heap, int index){
    int largest = index;
    int leftChild  = 2 * index + 1;
    int rightChild = 2 * index + 2;

    if (leftChild < heap->size && heap->arr[leftChild] > heap->arr[largest])
        largest = leftChild;
    if (rightChild < heap->size && heap->arr[rightChild] > heap->arr[largest])
        largest = rightChild;
    if (largest != index) {
        swap(&heap->arr[largest], &heap->arr[index]);
        heapify(heap, largest);
    }
}

void insert(MaxHeap *heap, int value){
    if (heap->size == heap->capacity) {
        fprintf(stderr, "Heap is full!\n");
        return;
    }

    int i = heap->size++;
    heap->arr[i] = value;

    for (i = heap->size / 2 - 1; i >= 0; i--)
        heapify(heap, i);
}

int delete(MaxHeap *heap){
    if (heap->size == 0) {
        fprintf(stderr, "Heap is empty!\n");
        return INT_MIN;
    }

    int i, max = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->arr[heap->size - 1] = INT_MIN;
    heap->size--;

    for (i = heap->size / 2 - 1; i >= 0; i--)
        heapify(heap, i);
    
    return max;
}

void swap(int *a, int *b){
    int temp = *b;
    *b = *a;
    *a = temp;
}

void printHeap(MaxHeap *heap){
    if (heap->size == 0) {
        fprintf(stderr, "Heap is empty!\n");
        return;
    }
    int i;
    for (i = 0; i < heap->size; i++)
        printf("%d ", heap->arr[i]);
}

void freeHeap(MaxHeap **heap){
    if (*heap != NULL) {
        free((*heap)->arr);
        free(*heap);
        *heap = NULL;
    }
}