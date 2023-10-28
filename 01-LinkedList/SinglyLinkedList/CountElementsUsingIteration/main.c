#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

struct node *createNode(int data){
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void add(Node **head, int data){
    Node *newNode = createNode(data);
    if (*head == NULL) {
        newNode->next = *head;
        *head = newNode;
    }
    else {
        Node *iter = *head;
        while (iter->next != NULL)
            iter = iter->next;
        newNode->next = iter->next;
        iter->next = newNode;
    }
}

int listSize(Node *head){
    int size = 0;
    while (head != NULL) {
        head = head->next;
        size++;
    }
    return size;
}

void printList(Node *head){
    if (head == NULL) 
        return;
    while (head != NULL) {
        printf("%d\n", head->data);
        head = head->next;
    }
}

int main(void){

    int i;
    Node *head = NULL;

    for (i = 0; i < 5; i++)
        add(&head, i * 10 + 1);

    printList(head);

    printf("List size: %d\n", listSize(head));

    return 0;
}