#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "linkedlist.h"

int getIntValueFromUser(void){
    int value;
    printf("Please enter a value: ");
    scanf("%d", &value);
    return value;
}

int main(void){

    int choice = -1;
    Node *head = NULL;
    
    while (1) {
        system("cls");
        printf("1. ADD\t\t\t"
               "6. REMOVE FIRST\n"
               "2. ADD FIRST\t\t"
               "7. REMOVE LAST\n"
               "3. ADD LAST\t\t"
               "8. SEARCH\n"
               "4. INSERT SORTED\t"
               "9. LIST SIZE\n"
               "5. REMOVE\t\t"
               "10.PRINT LIST\n\n"
               "0. EXIT\n\n"
               "Last choice: %d\n"
               "Enter your new choice: ", choice);
        
        scanf("%d", &choice);
        putchar('\n');

        if (choice == 1) {
            add(&head, getIntValueFromUser());
        }
        else if (choice == 2) {
            addFirst(&head, getIntValueFromUser());
        }
        else if (choice == 3) {
            addLast(&head, getIntValueFromUser());
        }
        else if (choice == 4) {
            insertSorted(&head, getIntValueFromUser());
        }
        else if (choice == 5) {
            int index;
            printf("Enter the index of the element you want to delete: ");
            scanf("%d", &index);
            removeNode(&head, index);
        }
        else if (choice == 6) {
            removeFirst(&head);
        }
        else if (choice == 7) {
            removeLast(&head);
        }
        else if (choice == 8) {
            int target;
            printf("Enter the value you are searching for: ");
            scanf("%d", &target);
            printf((search(head, target)) ? "\ntrue\n\n" : "\nfalse\n\n");
            system("pause");
        }
        else if (choice == 9) {
            printf("List size: %d\n\n", listSize(head));
            system("pause");
        }
        else if (choice == 10) {
            printList(head);
            system("pause");
        }
        else if (choice == 0) {
            freeList(&head);
            exit(EXIT_SUCCESS);
        }
        else {
            printf("Invalid option..\n\n");
            system("pause");
        }
    }

    return 0;
}