#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>

typedef struct {
    int *arr;
    size_t size;
    size_t length;
} Array;

Array *createArray(size_t initialSize);
bool isSorted(const Array *array);
bool isEmpty(const Array *array);
bool isFull(const Array *array);
bool isOutOfBounds(size_t index, size_t arrLength);
bool add(Array *array, int newNum);
void insert(Array *array, size_t index, int newNum);
void deleteByIndex(Array *array, size_t index);
void deleteByValue(Array *array, int key);
bool linearSearch(const Array *array, int key);
bool binarySearch(const Array* array, int key);
void print(const Array *array, const char *header);
void fill(Array *array, size_t fromIndex, size_t toIndex, int value);
int findMax(const Array *array);
int findMin(const Array *array);
void swap(int *a, int *b);
void reverse(Array *array);
void resize(Array *array, size_t newSize);
void freeArray(Array **arrayRef);

int main(void) {

    // Test createArray function
    Array *array = createArray(10);
    assert(array != NULL);

    // Test add function
    assert(add(array, 10) == true);
    assert(add(array, 20) == true);
    assert(add(array, 30) == true);
    assert(add(array, 40) == true);
    assert(add(array, 50) == true);

    // Test insert function
    insert(array, 1, 15);
    assert(array->arr[1] == 15 && array->length == 6);
    print(array, "Array after inserting 15");

    // Test deleteByIndex function
    deleteByIndex(array, 2);
    assert(array->length == 5);
    print(array, "Array after deleting the value in the 2nd index");

    // Test deleteByValue function
    deleteByValue(array, 10);
    assert(array->length == 4);
    print(array, "Array after deleting the value 10");
    deleteByValue(array, 11);
    assert(array->length == 4);

    // Test binarySearch function
    assert(binarySearch(array, 40) == true);
    
    // Test linearSearch function
    assert(linearSearch(array, 40) == true);
    print(array, "Array after linear search function (40) with transposition method");
    assert(linearSearch(array, 40) == true);
    print(array, "Array after linear search function (40) with transposition method");

    // Test fill function
    fill(array, 0, 1, 100);
    assert(array->arr[0] == 100 && array->arr[1] == 100);
    print(array, "Array after filling the array from [0] to [1] with the value 100");

    // Test findMax and findMin functions
    assert(findMax(array) == 100);
    assert(findMin(array) == 30);

    // Test reverse function
    reverse(array);
    print(array, "Array after reversing");
    assert(array->arr[0] == 50 && array->arr[3] == 100);

    // Test isSorted function
    assert(isSorted(array) == false);

    // Test isEmpty function
    assert(isEmpty(array) == false);

    // Test isFull function
    assert(isFull(array) == false);

    // Test resize function
    resize(array, 3);
    print(array, "New array size (3)");
    assert(array->size == 3);

    // Test freeArray function
    freeArray(&array);
    assert(array == NULL);

    printf("All test cases passed successfully!\n");

    return 0;
}

Array *createArray(size_t initialSize) {
    if (initialSize <= 0) {
        fprintf(stderr, "Size cannot be zero or negative.\n");
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

void deleteByIndex(Array *array, size_t index) {
    if (isOutOfBounds(index, array->length)) {
        fprintf(stderr, "Index Out of Bounds\n");
        return;
    }
    if (!isEmpty(array)) {
        size_t i;
        for (i = index; i < array->length - 1; i++)
            array->arr[i] = array->arr[i + 1];
        array->length--;
    }
}

void deleteByValue(Array *array, int key) {
    if (isEmpty(array))
        return;

    size_t i;
    bool isFound = false;
    for (i = 0; i < array->length; i++) {
        if (array->arr[i] == key) {
            isFound = true;
            break;
        }
    }
    if (isFound)
        deleteByIndex(array, i);
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
    if (isEmpty(array)) 
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

int findMax(const Array *array) {
    if (isEmpty(array)) {
        fprintf(stderr, "Array is empty!\n");
        return INT_MAX;
    }
    int max = array->arr[0];
    size_t i;
    for (i = 1; i < array->length; i++) {
        if (max < array->arr[i])
            max = array->arr[i];
    }
    return max;
}

int findMin(const Array *array) {
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
    if (isEmpty(array)) 
        return;

    size_t i;
    for (i = 0; i < array->length / 2; i++) {
        swap(&array->arr[i], &array->arr[array->length - i - 1]);
    }
}

bool isSorted(const Array *array) {
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

bool isEmpty(const Array *array) {
    return array->length == 0;
}

bool isFull(const Array *array) {
    return array->length == array->size;
}

bool isOutOfBounds(size_t index, size_t arrLength) {
    return (index < 0 || index > arrLength);
}

void resize(Array *array, size_t newSize) {
    array->arr = realloc(array->arr, sizeof(int) * newSize);
    if (array->arr == NULL) {
        perror("Memory reallocation failed for the array");
        exit(EXIT_FAILURE);
    }
    array->size = newSize;
    if (newSize < array->length)
        array->length = newSize;
}

void freeArray(Array **arrayRef) {
    if (*arrayRef != NULL) {
        free((*arrayRef)->arr);
        free(*arrayRef);
        *arrayRef = NULL;
    }
}