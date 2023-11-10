/*
---------------------- Postfix İfadelerin Değerlendirilmesi ----------------------
Algoritma:
    - Eğer karakter operand ise:
        Karakteri stack'e ekle (push işlemi)
    - Eğer karakter operatör ise:
        Stack'ten iki eleman çıkar ve çıkarılan iki elemana operatörü uygula
        Sonucu stack'e ekle (push)
    Postfix ifadesindeki bütün karakterleri okuduktan sonra stack'te kalan eleman
    döndürülür
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define STR_SIZE 30

typedef struct {
    int top;
    size_t size;
    int *data;
} Stack;

// Stack işlemleri için gerekli olan fonksiyonların prototipleri
Stack *createStack(size_t size);
void push(Stack *stack, int value);
int pop(Stack *stack);
bool isEmpty(Stack *stack);
bool isFull(Stack *stack);
void freeStack(Stack *stack);

// Postfix ifadesinin değerlendirilmesi için gerekli olan fonksiyonların prototipleri
int postfixEvaluation(const char *exp);
int power(int base, int power);

int main(void){

    char postfix[STR_SIZE];
    printf("Please enter a postfix expression: ");
    if ((fgets(postfix, STR_SIZE, stdin)) == NULL) {
        fprintf(stderr, "Failed to read input!\n");
        exit(EXIT_FAILURE);
    }

    // fgets fonksiyonu ile stringe eklenen '\n' karakterini kaldırma işlemi
    postfix[strcspn(postfix,"\n")] = '\0';

    printf("The result is: %d\n", postfixEvaluation(postfix));

    return 0;
}

// Postfix ifadesini değerlendirir
int postfixEvaluation(const char *exp){
    // İfadede bulunan operandlar için stack'i oluşturma işlemi
    Stack *stack = createStack(strlen(exp));
    int i;
    for (i = 0; exp[i] != '\0'; i++) {
        // Eğer karakter sayı ise stack'e eklenir
        if (isdigit(exp[i])) {
            // Karakteri tamsayıya çevirmek için '0' karakterinin değerini ifadeden çıkarırız
            push(stack, exp[i] - '0');
        }
        else if (exp[i] == ' ') // Karakter boşluksa devam et
            continue;
        else {
            // Karakter operatör ise stack'ten çıkarılan iki operand, operatör ile işleme sokulup stack'e eklenir
            int operand1 = pop(stack);
            int operand2 = pop(stack);
            switch (exp[i]) {
            case '+':
                push(stack, operand2 + operand1);
                break;
            case '-':
                push(stack, operand2 - operand1);
                break;
            case '*':
                push(stack, operand2 * operand1);
                break;
            case '/':
                push(stack, operand2 / operand1);
                break;
            case '^':
                push(stack, power(operand2, operand1));
                break;
            }
        }
    }
    // Stack'te kalan değer postfix ifadesinin sonucu olur 
    int result = pop(stack);
    // Ayrılan belleği serbest bırakmak için fonksiyon çağrılır
    freeStack(stack);
    return result;
}

// Tamsayılar için üs fonksiyonu
int power(int base, int power){
    int i, result = 1;
    for (i = 0; i < power; i++)
        result *= base;
    return result;
}

// Verilen boyutta stack oluşturur
Stack *createStack(size_t size){
    Stack *stack = malloc(sizeof(Stack));
    if (stack != NULL) {
        stack->data = malloc(sizeof(int) * size);
        if (stack->data != NULL) {
            stack->top = -1;
            stack->size = size;
        }
        // 'stack->data' için bellek ayırma işlemi başarısız olursa 'stack' için ayrılan bellek serbest bırakılır
        else {
            free(stack);
            return NULL;
        }
    }
    return stack;
}

// Stack'e eleman ekler
void push(Stack *stack, int value){
    if (isFull(stack)) {
        fprintf(stderr, "Stack is full!\n");
        return;
    }
    stack->data[++stack->top] = value;
}

// Stack'ten eleman çıkarır
int pop(Stack *stack){
    if (isEmpty(stack)) {
        fprintf(stderr, "Stack is empty!\n");
        return -1;
    }
    return stack->data[stack->top--];
}

// Stack'in boş olup olmadığını kontrol eder
bool isEmpty(Stack *stack){
    return stack->top == -1;
}

// Stack'in dolu olup olmadığını kontrol eder
bool isFull(Stack *stack){
    return stack->top == stack->size - 1;
}

// Stack için bellekten ayrılan alanı serbest bırakır
void freeStack(Stack *stack){
    if (stack != NULL) {
        free(stack->data);
        free(stack);
    }
}
