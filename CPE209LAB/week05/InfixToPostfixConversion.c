/*
---------------------- Infix İfadeyi Postfix İfadeye Çevirme ----------------------
Algoritma:
    - Eğer karakter operand ise:
        Karakteri postfix ifadesine ekle
    - Eğer karakter açık parantez ise:
        Karakteri stack'e ekle (push işlemi)
    - Eğer karakter kapalı parantez ise:
        Stack'te bulunan operatörleri çıkarıp postfix ifadesine ekle
        Açık ve kapalı parantezleri dahil etme
    - Eğer karakter operatör ise:
        -Eğer stack'te bulunan operatörün önceliği, operatörden büyük veya eşit ise:
            Stack'te bulunan operatörleri çıkarıp postfix ifadesine ekle
        -Aksi halde:
            Operatörü stack'e ekle (push işlemi)
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_STR_SIZE 30

typedef struct {
    int top;
    size_t size;
    char *data;
} Stack;

// Stack işlemleri için gerekli olan fonksiyonların prototipleri
Stack *createStack(size_t size);
void push(Stack *stack, char c);
char pop(Stack *stack);
char peek(Stack *stack);
bool isEmpty(Stack *stack);
bool isFull(Stack *stack);
void freeStack(Stack *stack);

// Dönüşüm için gerekli olan fonksiyonların prototipleri 
void infixToPostfix(const char *infix, char *postfix);
int precedence(char operator);
bool isOperator(char c);


int main(void){

    char infix[MAX_STR_SIZE];
    char postfix[MAX_STR_SIZE * 2]; // İfade dönüşümü sırasında olası taşmalara karşı daha büyük boyut ayrılır
    
    printf("Please enter infix expression: ");
    if ((fgets(infix, MAX_STR_SIZE, stdin)) == NULL) {
        fprintf(stderr, "Failed to read input\n");
        exit(EXIT_FAILURE);
    }

    // fgets fonksiyonu ile string sonuna eklenen yeni satır karakterini kaldırma işlemi ('\n')
    infix[strcspn(infix,"\n")] = '\0';

    infixToPostfix(infix,postfix);

    printf("Postfix expression: %s\n", postfix);

    return 0;
}

// Infix ifadeyi postfix ifadeye dönüştürür
void infixToPostfix(const char *infix, char *postfix){
    
    int len = strlen(infix);
    // İfadeyi dönüştürmek için kullanılacak olan stack'in bellek ayırma işlemi
    Stack *stack = createStack(len);
    // Bellek ayırma işlemi başarısız olursa hata mesajı yazdırılır ve program sonlanır
    if (stack == NULL) {
        fprintf(stderr, "Memory allocation failed for the stack!\n");
        exit(EXIT_FAILURE);
    }
    
    // Döngü içinde kullanılacak değişkenlerin tanımlamaları
    int i, j;
    char token, current;
    for (i = 0; i < len; i++) {
        token = infix[i];
        // Eğer karakter, sayı veya ondalık belirten nokta ise girilen tam sayıyı veya ondalık sayıyı postfix ifadesinde tutar
        if (isdigit(token) || token == '.') {
            while (isdigit(infix[i]) || infix[i] == '.')
                postfix[j++] = infix[i++];
            postfix[j++] = ' '; // Bir sonraki indise boşluk ekler
            i--; // Döngü içinde bir kez daha arttırıldığından döngü işleyişini düzeltmek için bir azaltılır
        }
        // Eğer karakter açık parantez ise
        else if (token == '(') {
            push(stack, token); // stack'e ekle (push işlemi)
        }
        // Eğer karakter kapalı parantez ise stack'te bulunan operatörleri çıkarıp postfix ifadesine ekler
        else if (token == ')') {
            while ((current = pop(stack)) != '(') {
                postfix[j++] = current;
                postfix[j++] = ' ';
            }
        }
        else if (isOperator(token)) {
            /* Eğer karakter operatör ise operatör önceliğine ve stack'in boş olmama durumuna göre stack'ten operatörleri
               çıkarıp postfix ifadesine ekler */
            while (!isEmpty(stack) && precedence(peek(stack)) >= precedence(token)) {
                postfix[j++] = pop(stack);
                postfix[j++] = ' ';
            }
            push(stack, token); // stack'e ekle (push işlemi)
        }
    }
    // Stack'te kalan ifadeleri postfix ifadesine ekler
    while (!isEmpty(stack)) {
        postfix[j++] = pop(stack);
        postfix[j++] = ' ';
    }
    postfix[j] = '\0';
    freeStack(stack); // Belleği serbest bırakır
}

int precedence(char operator){
    // Döndürülen sayı ne kadar büyükse öncelik seviyesi o kadar fazladır
    if (operator == '+' || operator == '-')
        return 1;
    else if (operator == '*' || operator == '/')
        return 2;
    else if (operator == '^')
        return 3;
    else
        return 0; // Geçersiz operatör olma durumunda
}

bool isOperator(char c){
    // Verilen karakterin operatör olup olmadığını kontrol eder
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') ? true : false;
}

// Verilen boyutta stack oluşturur
Stack *createStack(size_t size){
    Stack *stack = malloc(sizeof(Stack));
    if (stack != NULL) {
        stack->data = malloc(sizeof(char) * size);
        if (stack->data != NULL) {
            stack->top = -1;
            stack->size = size;
        }
        // 'stack->data' için bellek ayırma işlemi başarısız olursa 'stack' için ayrılan bellek serbest bırakılır
        else
            free(stack);
    }
    return stack;
}

// Stack'e eleman ekler
void push(Stack *stack, char c){
    if (isFull(stack)) {
        fprintf(stderr, "Stack is full!\n");
        return;
    }
    stack->data[++stack->top] = c;
}

// Stack'ten eleman çıkarır
char pop(Stack *stack){
    if (isEmpty(stack)) {
        fprintf(stderr, "Stack is empty!\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top--];
}

// Stack'in en üstündeki elemanı döndürür
char peek(Stack *stack){
    if (isEmpty(stack)) {
        fprintf(stderr, "Stack is empty!\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top];
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