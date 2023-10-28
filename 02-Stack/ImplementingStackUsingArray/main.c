#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "stack.h"

int main(void){

    int size, choice = -1;
    printf("Please enter stack size: ");
    scanf("%d", &size);

    if (size <= 0) {
        fprintf(stderr, "Invalid stack size. Please enter a positive size.\n");
        exit(EXIT_FAILURE);
    }

    Stack *stack = createStack(size);
    if (stack == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("**********************************\n");
        printf("1.Push\n"
               "2.Pop\n"
               "3.Peek\n"
               "4.Search\n"
               "5.Print Stack\n"
               "6.Clear Stack\n"
               "0.Exit\n\n"
               "Enter your choice: ");
        
        scanf("%d", &choice);
        printf("\n");

        switch (choice) {
            case 1: {
                int value;
                printf("Please enter a value: ");
                scanf("%d", &value);
                push(stack, value);
                break;
            }
            case 2: {
                int value = pop(stack);
                if (value != INT_MIN)
                    printf("Popped item  --> %d\n\n", value);
                break;
            }
            case 3: {
                int value = peek(stack);
                if (value != INT_MIN)
                    printf("Element at the top of the stack --> %d\n\n", peek(stack));
                break;
            }
            case 4: {
                int target;
                printf("Enter the value you are searching for: ");
                scanf("%d", &target);
                printf(search(stack,target) ? "\ntrue\n\n" : "\nfalse\n\n");
                break;
            }
            case 5: {
                printStack(stack);
                break;
            }
            case 6: {
                freeStack(stack);
                printf("Stack cleared.\n\n");
                printf("Please enter a new size for the stack: ");
                scanf("%d", &size);
                if (size <= 0) {
                    fprintf(stderr, "\nStack size cannot be negative!\n");
                    exit(EXIT_FAILURE);
                }
                stack = createStack(size);
                printf("\nStack size changed to %d.\n\n", size);
                break;
            }
            case 0: {
                freeStack(stack);
                exit(EXIT_SUCCESS);
                break;
            }
            default:
                printf("Invalid option..\n\n");
                break;
        }
    }

    return 0;
}