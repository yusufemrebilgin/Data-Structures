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

bool search(Node *head, int key){
    if (head == NULL)
        return false;
    if (head->data == key)
        return true;
    search(head->next, key);
}

void printList(Node *head){
    if (head == NULL) 
        return;
    while (head != NULL) {
        printf("->%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main(void){

    int i;
    Node *head = NULL;

    for (i = 0; i < 5; i++)
        add(&head, i * 10 + 1);

    printList(head);

    printf(search(head,11) ? "true\n" : "false\n");
    printf(search(head,23) ? "true\n" : "false\n");

    return 0;
}