/*
Rastgele üretilmiş 100 sayıyı bağlı listeye küçükten büyüğe doğru sıralı şekilde 
ekleyen fonksiyonu yazınız.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

void insertSorted(Node **head, int data){
    Node *newNode;
    //Bellekten yer ayırma işlemi gerçekleşmezse ekrana hata mesajı yazdırılır ve program sonlandırılır
    if ((newNode = malloc(sizeof(Node))) == NULL) {
        fprintf(stderr, "Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;

    //Liste boşsa veya parametre değeri ilk düğümde bulunan değerden küçükse düğüm başa eklenir
    if (*head == NULL || data < (*head)->data) {
        newNode->next = *head;
        *head = newNode;
    }
    //Girilen değere göre araya veya en sona ekleme yapar
    else {
        Node *iter = *head;
        while (iter->next != NULL && iter->next->data < data)
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

    srand(time(NULL));

    int i, n = 100;
    for (i = 0; i < n; i++) {
        int value = rand() % 100 + 1; //1 ile 100 arasında rastgele değer oluşturur
        insertSorted(&head, value);
    }

    printList(head);

    return 0;
}