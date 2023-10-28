#include "linkedlist.h"

struct node *createNode(int value){
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    newNode->next = NULL;
    newNode->value = value;
    return newNode;
}

void add(Node **head, int value){
    if (*head == NULL)
        addFirst(head, value);
    else
        addLast(head, value);
}

void addFirst(Node **head, int value){
    Node *newNode = createNode(value);
    newNode->next = *head;
    *head = newNode;
}

void addLast(Node **head, int value){
    if (*head == NULL) return;
    Node *iter = *head;
    Node *newNode = createNode(value);
    while (iter->next != NULL)
        iter = iter->next;
    newNode->next = iter->next;
    iter->next = newNode;
}

void insertSorted(Node **head, int value){
    if (*head == NULL || (*head)->value > value) {
        addFirst(head, value);
    } else {
        Node *iter = *head;
        Node *newNode = createNode(value);
        while (iter->next != NULL && newNode->value > iter->next->value)
            iter = iter->next;
        newNode->next = iter->next;
        iter->next = newNode;
    }
}

bool removeNode(Node **head, int index){
    if (isEmpty(*head)) {
        printf("\nList is empty!\n\n");
        system("pause");
        return false;
    }
    if (index < 0) {
        printf("\nIndex value cannot be negative\n\n");
        system("pause");
        return false;
    }

    int flag = false;

    if (index == 0){
        removeFirst(head);
    } else {
        int i = 0;
        Node *temp, *iter = *head;
        while (iter->next != NULL) {
            iter = iter->next;
            i++;
            if (index - 1 == i) {
                flag = true;
                break;
            }
        }
        if (flag) {
            temp = iter->next;
            iter->next = iter->next->next;
            free(temp);
            return true;
        }
    }
    if (!flag) {
        printf("\nThere is no node at the index value you entered\n\n");
        system("pause");
        return false;
    }
    return false;
}

bool removeFirst(Node **head){
    if (isEmpty(*head)) {
        printf("List is empty!\n\n");
        system("pause");
        return false;
    }

    Node *temp = *head;
    *head = (*head)->next;
    free(temp);
    return true;
}

bool removeLast(Node **head){
    if (isEmpty(*head)) {
        printf("List is empty!\n\n");
        system("pause");
        return false;
    }
    
    Node *temp, *iter = *head;
    while (iter->next->next != NULL)
        iter = iter->next;
    temp = iter->next;
    iter->next = iter->next->next;
    free(temp);
    return true;
}

bool search(Node *head, int value){
    while (head != NULL) {
        if (head->value == value)
            return true;
        head = head->next;
    }
    return false;
}

bool isEmpty(Node *head){
    if (head == NULL)
        return true;
    return false;
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
    if (isEmpty(head)) {
        printf("List is empty!\n\n");
        return;
    }
    int i = 0;
    while (head != NULL) {
        printf("[%02d] --> %d\n", i++, head->value);
        head = head->next;
    }
    printf("\n");
}

void freeList(Node **head){
    if (*head == NULL)
        return;

    while (*head != NULL) {
        Node *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}