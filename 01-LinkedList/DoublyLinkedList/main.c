#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
    int data;
    struct node *next;
    struct node *prev;
} Node;

Node *createNode(int data){
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    newNode->next = newNode->prev = NULL;
    newNode->data = data;
    return newNode;
}

void addFirst(Node **head, int data){
    Node *newNode = createNode(data);

    if (*head == NULL) {
        *head = newNode;
        newNode->next = newNode->prev = NULL;
    }
    else {
        newNode->next = *head;
        newNode->prev = NULL;
        (*head)->prev = newNode;
        *head = newNode;
    }
}

void addLast(Node **head, int data){
    Node *newNode = createNode(data);
    if (*head != NULL) {
        Node *iter = *head;
        while (iter->next != NULL)
            iter = iter->next;
        newNode->next = NULL;
        newNode->prev = iter;
        iter->next = newNode;
    }
    else
        addFirst(head, data);
}

void insertSorted(Node **head, int data){
    Node *newNode = createNode(data);

    if (*head == NULL) {
        *head = newNode;
        (*head)->next = (*head)->prev = NULL;
    }
    else if (data < (*head)->data) {
        newNode->next = *head;
        newNode->prev = NULL;
        (*head)->prev = newNode;
        *head = newNode;
    }
    else {
        Node *iter = *head;
        while (iter->next != NULL && iter->next->data < data)
            iter = iter->next;
        newNode->next = iter->next;
        newNode->prev = iter;
        iter->next = newNode;
        if (newNode->next != NULL)
            newNode->next->prev = newNode;
    }
}

void removeNode(Node **head, int data){
    if (*head != NULL) {
        Node *temp = NULL;
        if ((*head)->data == data) {
            temp = *head;
            *head = (*head)->next;
            (*head)->prev = NULL;
        }
        else {
            Node *iter = *head;
            while (iter->next != NULL && iter->next->data != data) {
                iter = iter->next;
            }
            if (iter->next == NULL) {
                printf("The given value is not on the list.\n\n");
                return;
            }
            temp = iter->next;
            iter->next = iter->next->next;
            if (iter->next != NULL)
                iter->next->prev = iter;
        }
        free(temp);
    }
}

void printList(Node *head){
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    while (head != NULL) {
        printf("->%d ", head->data);
        head = head->next;
    }
    printf("\n\n");
}

int main(void){

    int i;
    Node *head = NULL;
    srand(time(NULL));

    for (i = 0; i < 5; i++)
        insertSorted(&head, rand() % 15);

    printList(head);

    int value = rand() % 15;
    printf("Adding %d to the front of the list:\n", value);
    addFirst(&head, value);
    printList(head);

    value = rand() % 15;
    printf("Adding %d to the end of the list:\n", value);
    addLast(&head, value);
    printList(head);

    value = rand() % 15;
    printf("After deleting the value %d:\n", value);
    removeNode(&head, value);
    printList(head);
    
    value = rand() % 15;
    printf("After deleting the value %d:\n", value);
    removeNode(&head, value);

    printList(head);

    return 0;
}