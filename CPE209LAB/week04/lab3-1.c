/*
Klavyeden -1 girilinceye kadar girilen tek sayıları listenin başına, çift sayıları ise listenin sonuna
ekleyen fonksiyonu yazınız.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

void addNode(Node **head, int data){
    Node *newNode;
    //Bellekten yer ayırma işlemi gerçekleşmezse ekrana hata mesajı yazdırılır ve program sonlandırılır
    if ((newNode = malloc(sizeof(Node))) == NULL) {
        fprintf(stderr, "Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    
    //Parametre değeri tek veya liste boş olduğunda, düğüm liste başına eklenir
    if (*head == NULL || data % 2 != 0) {
        newNode->next = *head;
        *head = newNode;
    }
    //Parametre değeri çift olduğunda, düğüm listenin sonuna eklenir
    else {
        Node *iter = *head;
        while (iter->next != NULL)
            iter = iter->next;
        newNode->next = iter->next;
        iter->next = newNode;
    }
}

void printList(Node *head){
    //Liste boşsa listenin boş olduğuna dair mesaj ekrana yazdırılır ve fonksiyon sonlandırılır
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
}

int main(void){

    Node *head = NULL;

    int value;

    printf("Please enter values to add to the list (Enter [-1] to exit):\n\n");
    while (1) {
        printf("--> ");
        scanf("%d", &value);
        if (value == -1)
            break;
        addNode(&head, value);
    }
    printf("\n");

    printList(head);

    return 0;
}