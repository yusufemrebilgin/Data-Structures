/*
Listede en uzun ismin olduğu kaydı yazdıran fonksiyonu yazınız.
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

//Liste boş değilse listede bulunan en uzun ismi ve ismin uzunluğunu ekrana yazdırır
void printLongestName(Student *head){
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    
    Student *stdWithLongestName = head;
    size_t len = strlen(stdWithLongestName->name);

    while (head != NULL) {
        size_t currentNameLen = strlen(head->name);
        if (len < currentNameLen) {
            stdWithLongestName = head;
            len = currentNameLen;
        }
        head = head->next;
    }
    printf("Longest name on the list: %s\n", stdWithLongestName->name);
    printf("Name length: %zu\n", len);
}

int main(void){

    Student *head = NULL;

    addStudent(&head, 2110206, "Yusuf", 22);
    addStudent(&head, 2110218, "Ali", 18);    
    addStudent(&head, 2110234, "Mehmet", 24);
    addStudent(&head, 2110211, "Emre", 19);
    addStudent(&head, 2110261, "Abdullah", 29);

    printLongestName(head);
    
    return 0;
}