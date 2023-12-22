#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
    int data;
    struct node *next;
    struct node *prev;
} Node;

Node *createNode(int data);
void insertSorted(Node **head, int data);
void printList(Node *head);
void freeList(Node **head);

int main(void){

    int i;
    Node *head = NULL;

    srand(time(NULL));

    for (i = 0; i < 10; i++)
        insertSorted(&head, rand() % 100);

    printList(head);

    freeList(&head);

    return 0;
}

Node *createNode(int data){
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) 
        return NULL;
    newNode->next = newNode->prev = NULL;
    newNode->data = data;
    return newNode;
}

void insertSorted(Node **head, int data){
    Node *newNode = createNode(data);
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed for the node!");
        exit(EXIT_FAILURE);
    }
    if (*head == NULL)
        *head = newNode;
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

void freeList(Node **head){
    if (*head == NULL) {
        fprintf(stderr, "List is empty!\n");
        return;
    }
    while (*head != NULL) {
        Node *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}