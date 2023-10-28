#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int value;
    struct node *next;
} Node;

void add(Node **head, int value);
void addFirst(Node **head, int value);
void addLast(Node **head, int value);
void insertSorted(Node **head, int value);
bool removeNode(Node **head, int index);
bool removeFirst(Node **head);
bool removeLast(Node **head);
bool search(Node *head, int value);
bool isEmpty(Node *head);
int listSize(Node *head);
void printList(Node *head);
void freeList(Node **head);

#endif