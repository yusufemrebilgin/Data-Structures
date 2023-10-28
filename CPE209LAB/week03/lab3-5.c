/*
Listede aranan öğrencinin adının yer aldığı düğümden bir sonraki düğümü silen fonksiyonu yazınız.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct studentNode {
    int studentNumber;
    char name[20];
    int age;
    struct studentNode *next;
} Student;

void addStudent(Student **head, int studentNumber, char name[], int age){
    Student *newStudent = malloc(sizeof(Student));
    //Bellekten yer ayırma işlemi gerçekleşmezse ekrana hata mesajı yazdırılır ve program sonlandırılır
    if (newStudent == NULL) {
        fprintf(stderr, "Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    newStudent->studentNumber = studentNumber;
    strcpy(newStudent->name, name);
    newStudent->age = age;

    //Liste boşsa düğüm başa eklenir aksi halde sona eklenir
    if (*head == NULL) {
        newStudent->next = *head;
        *head = newStudent;
    }
    else {
        Student *iter = *head;
        while (iter->next != NULL)
            iter = iter->next;
        newStudent->next = iter->next;
        iter->next = newStudent;
    }
}

//Parametre olarak geçilen ismin bulunduğu düğümden sonraki öğrenci düğümünü siler
void removeStudent(Student **head, char name[]){
    if (*head == NULL) {
        printf("List is empty!\n");
        return;
    }
    int flag = false;
    Student *iter = *head;
    while (iter->next != NULL) {
        if (!strcmp(iter->name, name)) {
            flag = true;
            break;
        }
        iter = iter->next;
    }
    if (flag) {
        Student *temp = iter->next;
        iter->next = iter->next->next;
        free(temp);
    }
    else {
        printf("The student you are looking for is not on the list.\n\n");
    }
}

void printList(Student *head){
    while (head != NULL) {
        printf("%d -> %s\n", head->studentNumber, head->name);
        head = head->next;
    }
    printf("\n");
}

int main(void){

    Student *head = NULL;

    addStudent(&head, 2110206, "Yusuf", 22);
    addStudent(&head, 2110218, "Ali", 18);    
    addStudent(&head, 2110234, "Mehmet", 24);
    addStudent(&head, 2110211, "Emre", 19);    

    printf("Before removing node:\n");
    printList(head);

    //'Ali' isminin olduğu düğümden sonraki düğümü siler
    removeStudent(&head, "Ali");

    printf("After removing node:\n");
    printList(head);

    return 0;
}