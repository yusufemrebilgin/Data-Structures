/*
Öğrenci bilgilerini ekrana yazdıran fonksiyonu yazınız.
*/
#include <stdio.h>
#include <stdlib.h>
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

void printList(Student *head){
    //Liste boşsa listenin boş olduğuna dair mesaj ekrana yazdırılır ve fonksiyon sonlandırılır
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    
    int i = 0;
    printf("\t%10s%20s\t%4s\n\n", "Student No", "Student Name", "Age");
    while (head != NULL) {
        printf("%02d\t%10d%20s\t%4d\n", (i++ + 1), head->studentNumber, head->name, head->age);
        head = head->next;
    }
}

int main(void){

    Student *head = NULL;

    addStudent(&head, 2110206, "Yusuf", 22);
    addStudent(&head, 2110211, "Emre", 19);    
    addStudent(&head, 2110218, "Ali", 18);    
    addStudent(&head, 2110234, "Mehmet", 24);

    printList(head);

    return 0;
}