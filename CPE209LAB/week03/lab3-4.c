/*
Listede öğrenci adına göre kayıt arama yapan fonksiyonu yazınız.
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

//Parametre olarak gönderilen isim değişkeni listede varsa 'true' yoksa 'false' döndürür
bool searchByName(Student *head, char name[]){
    while (head != NULL) {
        if (!strcmp(head->name,name))
            return true;
        head = head->next;
    }
    return false;
}

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

int main(void){

    Student *head = NULL;

    addStudent(&head, 2110206, "Yusuf", 22);
    addStudent(&head, 2110211, "Emre", 19);

    char name[20];
    printf("Enter the name of the student you are searching for: ");
    scanf("%s", name);

    if (searchByName(head, name))
        printf("\ntrue");
    else
        printf("\nfalse");

    return 0;
}