#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

Node *createNode(int data){
    Node *newNode;
    if ((newNode = malloc(sizeof(Node))) == NULL) {
        fprintf(stderr, "Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void addNode(Node **head, int data){
    Node *newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        newNode->next = *head;
    }
    else {
        Node *iter = *head;
        while (iter->next != *head)
            iter = iter->next;
        iter->next = newNode;
        newNode->next = *head;
    }
}

void removeNode(Node **head, int data){
    if (*head == NULL) {
        printf("List is empty!\n");
        return;
    }
    
    Node *temp = NULL;

    if ((*head)->data == data) {
        temp = *head;
        Node *iter = *head;
        while (iter->next != *head)
            iter = iter->next;
        iter->next = (*head)->next;
        *head = iter->next;
    }
    else {
        Node *iter = *head;
        while (iter->next != *head && iter->next->data != data)
            iter = iter->next;
        temp = iter->next;
        iter->next = iter->next->next;
    }
    free(temp);
}

void printList(Node *head){
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    Node *iter = head;
    do {
        printf("->%d ", iter->data);
        iter = iter->next;
    } while (iter != head);
    printf("\n\n");
}

int main(void){

    int i;
    Node *head = NULL;

    for (i = 0; i < 10; i++)
        addNode(&head, (i+1) * 10);
    
    printf("Before removing the nodes:\n");
    printList(head);

    removeNode(&head, 10);
    removeNode(&head, 50);
    removeNode(&head, 100);
    
    printf("After removing the nodes:\n");
    printList(head);

    return 0;
}