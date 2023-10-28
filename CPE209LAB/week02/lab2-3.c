#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct patientNode {
    int age;
    char name[20];
    struct patientNode *next;
} Patient;

void addPatient(Patient **head, int age, char name[]){
    Patient *newPatient = malloc(sizeof(Patient));
    if (newPatient == NULL) {
        fprintf(stderr, "Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    else {
        newPatient->age = age;
        strcpy(newPatient->name, name);
    }

    if (*head == NULL) {
        newPatient->next = *head;
        *head = newPatient;
    }
    else {
        Patient *iter = *head;
        while (iter->next != NULL)
            iter = iter->next;
        newPatient->next = iter->next;
        iter->next = newPatient;
    }
}

void printList(Patient *head){
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    printf("%-20s %s\n\n", "Patient Name", "Age");
    while (head != NULL) {
        printf("%-20s %d\n", head->name, head->age);
        head = head->next;
    }
}

int main(void){

    Patient *head = NULL;

    addPatient(&head, 24, "Ali");
    addPatient(&head, 35, "Ahmet");
    addPatient(&head, 30, "Deniz");
    addPatient(&head, 22, "Defne");

    printList(head);

    return 0;
}