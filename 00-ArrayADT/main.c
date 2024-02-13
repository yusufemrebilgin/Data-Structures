#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct {
    int *arr;
    size_t size;
    size_t length;
} Array;

Array *createArray(size_t initialSize);
bool isSorted(Array *array);
bool isEmpty(Array *array);
bool isFull(Array *array);
bool isOutOfBounds(size_t index, size_t arrLength);
bool add(Array *array, int newNum);
void insert(Array *array, size_t index, int newNum);
void delete(Array *array, size_t index);
bool linearSearch(const Array *array, int key);
bool binarySearch(const Array* array, int key);
void print(const Array *array, const char *header);
void fill(Array *array, size_t fromIndex, size_t toIndex, int value);
int findMax(Array *array);
int findMin(Array *array);
void swap(int *a, int *b);
void reverse(Array *array);
void resize(Array *array, size_t newSize);
void freeArray(Array **arrayRef);

int main(void) {

    

    return 0;
}

Array *createArray(size_t initialSize) {
    if (initialSize < 0) {
        fprintf(stderr, "Size cannot be negative.\n");
        return NULL;
    }
    Array *array = malloc(sizeof(Array));
    if (array != NULL) {
        if ((array->arr = malloc(sizeof(int) * initialSize)) != NULL) {
            array->length = 0;
            array->size = initialSize;
        } else {
            free(array);
            array = NULL;
        }
    }
    return array;
}

bool add(Array *array, int newNum) {
    if (isFull(array)) {
        return false;
    }
    array->arr[array->length++] = newNum;
    return true;
}

void insert(Array *array, size_t index, int newNum) {
    if (isOutOfBounds(index, array->length)) {
        fprintf(stderr, "Index Out of Bounds\n");
        return;
    }
    if (isFull(array)) {
        fprintf(stderr, "Array is full!\n");
        return;
    }
    size_t i;
    for (i = array->length; i > index; i--) {
        array->arr[i] = array->arr[i - 1];
    }
    array->arr[index] = newNum;
    array->length++;
}

void delete(Array *array, size_t index) {
    if (isOutOfBounds(index, array->length)) {
        fprintf(stderr, "Index Out of Bounds\n");
        return;
    }
    if (!isEmpty(array)) {
        size_t i;
        for (i = index; i < array->length - 1; i++)
            array->arr[i] = array->arr[i + 1];
    }
}

bool linearSearch(const Array *array, int key) {
     size_t i;
     for (i = 0; i < array->length; i++) {
        if (array->arr[i] == key) {
            // Transposition method for linear searching
            swap(&array->arr[i], &array->arr[i - 1]);
            return true;
        }
     }
     return false;
}

bool binarySearch(const Array* array, int key) {
    size_t left  = 0;
    size_t right = array->length - 1;
    while (left <= right) {
        size_t mid = (left + right) / 2;
        if (key < array->arr[mid])
            right = mid - 1;
        else if (key > array->arr[mid])
            left = mid + 1;
        else
            return true;
    }
    return false;
}

void print(const Array *array, const char *header) {
    if (isEmpty((Array *)array)) 
        return;
    
    size_t i;
    printf("%s:\n[", header);
    for (i = 0; i < array->length; i++) {
        if (i != array->length - 1)
            printf("%d, ", array->arr[i]);
        else
            printf("%d]\n\n", array->arr[i]);
    }
}

void fill(Array *array, size_t fromIndex, size_t toIndex, int value) {
    if (isEmpty(array)) 
        return;

    if (isOutOfBounds(fromIndex, array->length) || isOutOfBounds(toIndex, array->length)) {
        fprintf(stderr, "Index Out of Bound\n");
        return;
    }

    for (fromIndex; fromIndex <= toIndex; fromIndex++) {
        array->arr[fromIndex] = value;
    }
}

int findMax(Array *array) {
    if (isEmpty(array)) {
        fprintf(stderr, "Array is empty!\n");
        return INT_MIN;
    }
    int max = array->arr[0];
    size_t i;
    for (i = 1; i < array->length; i++) {
        if (max < array->arr[i])
            max = array->arr[i];
    }
    return max;
}

int findMin(Array *array) {
    if (isEmpty(array)) {
        fprintf(stderr, "Array is empty!\n");
        return INT_MIN;
    }
    int min = array->arr[0];
    size_t i;
    for (i = 1; i < array->length; i++) {
        if (min > array->arr[i])
            min = array->arr[i];
    }
    return min;
}

void swap(int *a, int *b) {
    int temp = *b;
    *b = *a;
    *a = temp;
}

void reverse(Array *array) {
    if (isEmpty(array)) return;

    size_t i;
    for (i = 0; i < array->length / 2; i++) {
        swap(&array->arr[i], &array->arr[array->length - i - 1]);
    }
}

bool isSorted(Array *array) {
    if (isEmpty(array)) {
        fprintf(stderr, "Array is empty!\n");
        return false;
    }

    size_t i;
    for (i = 0; i < array->length - 1; i++) {
        if (array->arr[i] > array->arr[i + 1])
            return false;
    }
    return true;
}

bool isEmpty(Array *array) {
    return array->length == 0;
}

bool isFull(Array *array) {
    return array->length == array->size;
}

bool isOutOfBounds(size_t index, size_t arrLength) {
    return (index < 0 || index > arrLength);
}

void resize(Array *array, size_t newSize) {
    array->arr = realloc(array->arr, sizeof(int) * newSize);
    if (array->arr == NULL) {
        fprintf(stderr, "Memory reallocation failed for the array!\n");
        exit(EXIT_FAILURE);
    }
    array->size = newSize;
}

void freeArray(Array **arrayRef) {
    if (*arrayRef != NULL) {
        free((*arrayRef)->arr);
        free(*arrayRef);
        *arrayRef = NULL;
    }
}