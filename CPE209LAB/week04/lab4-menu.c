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

void removeStudent(Student **head, char name[]){
    if (*head == NULL) {
        printf("List is empty!\n");
        return;
    }
    if (!strcmp((*head)->name, name)) {
        Student *temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }
    int flag = false;
    Student *iter = *head;
    while (iter->next != NULL) {
        if (!strcmp(iter->next->name, name)) {
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

//Parametre olarak gönderilen isim değişkeni listede varsa 'true' yoksa 'false' döndürür
bool searchByName(Student *head, char name[]){
    while (head != NULL) {
        if (!strcmp(head->name,name))
            return true;
        head = head->next;
    }
    return false;
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

void freeStudentList(Student **head){
    if (*head == NULL)
        return;
    while (*head != NULL) {
        Student *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

Student getStudentInputFromUser(void){
    Student student;
    printf("Please enter student number: ");
    scanf("%d", &student.studentNumber);
    printf("Please enter student name:   ");
    scanf("%s", student.name);
    printf("Please enter student age:    ");
    scanf("%d", &student.age);
    return student;
}

int main(void){

    int choice = -1;
    Student *head = NULL;

    while (true) {
        printf("************************************************\n"
               "1.Add Student\n"
               "2.Remove Student\n"
               "3.Search By Name\n"
               "4.Print Longest Name\n"
               "5.Print List\n"
               "0.Exit\n\n"
               "Enter your choice: ");

        scanf("%d", &choice);
        printf("\n\n");

        if (choice == 1) {
            Student tmp = getStudentInputFromUser();
            addStudent(&head, tmp.studentNumber, tmp.name, tmp.age);
        }
        else if (choice == 2) {
            char name[20];
            printf("Enter the name of the student you want to remove: ");
            scanf("%s", name);
            removeStudent(&head, name);
        }
        else if (choice == 3) {
            char name[20];
            printf("Enter the name of the student you are searching for: ");
            scanf("%s", name);
            searchByName(head, name) ? printf("\ntrue\n\n") : printf("\nfalse\n\n");
        }
        else if (choice == 4) {
            printLongestName(head);
        }
        else if (choice == 5) {
            printList(head);
        }
        else if (choice == 0) {
            freeStudentList(&head);
            exit(EXIT_SUCCESS);
        }
        else {
            printf("Invalid option. Please try again..\n\n");
        }
    
    }


    return 0;
}

