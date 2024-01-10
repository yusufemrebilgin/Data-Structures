#include <stdio.h>

void swap(int *a, int *b){
    int temp = *b;
    *b = *a;
    *a = temp;
}

// Yığın(heap) yapısı oluşturur
void heapify(int arr[], int arrSize, int index){
    
    int largest = index;
    int leftChild  = 2 * index + 1;
    int rightChild = 2 * index + 2;
    
    if (leftChild < arrSize && arr[leftChild] > arr[largest])
        largest = leftChild;
    if (rightChild < arrSize && arr[rightChild] > arr[largest])
        largest = rightChild;
    if (largest != index) {
        swap(&arr[largest], &arr[index]);
        heapify(arr, arrSize, largest);
    }
}

void printArray(const int arr[], int size, const char *s){
    int i;
    printf("%s:\n", s);
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main(void){
    
    int i, arrayA[] = {5, 10, 30, 20, 45, 15};
    int sizeA = sizeof(arrayA) / sizeof(*arrayA);
    printArray(arrayA, sizeA, "Array A");

    // n ağaç boyutu olsun, 'n / 2 - 1' yaprak olmayan(non-leaf) son düğümü verir
    for (i = sizeA / 2 - 1; i >= 0; i--)
        heapify(arrayA, sizeA, i);
    printArray(arrayA, sizeA, "Heapified A");

    printf("\n\n");

    int arrayB[] = {5, 10, 20, 15, 12, 40, 25, 18};
    int sizeB = sizeof(arrayB) / sizeof(*arrayB);
    printArray(arrayB, sizeB, "Array B");

    for (i = sizeB / 2 - 1; i >= 0; i--)
        heapify(arrayB, sizeB, i);
    printArray(arrayB, sizeB, "Heapified B");
    
    return 0;
}