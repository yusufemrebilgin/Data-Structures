/*
--------- Parentezlerin Kurallı Olup Olmadığını Kontrol Eden Program ---------
Kurallar:
    - Metin dosyasında bulunan açık ve kapalı parantez sayısı aynı olmalı
    - Kapalı parantez kullanılacaksa mutlaka ona denk açık bir parantez olmalı
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int top;
    size_t size;
    char *data;
} Stack;

// Stack işlemleri için gerekli olan fonksiyonların prototipleri
Stack *createStack(size_t size);
void push(Stack *stack, char c);
char pop(Stack *stack);
bool isEmpty(Stack *stack);
bool isFull(Stack *stack);
void freeStack(Stack *stack);

// Diğer fonksiyonların prototipleri
bool isOpenBracket(char c);
bool isCloseBracket(char c);
bool areBracketsMatching(char c1, char c2);
bool isBalanced(const char *filename);

int main(void){

    // Dosya ismi
    const char *filename = "testcode.txt";

    // Dosya içindeki parentezlerin eşitliğini kontrol eder
    if (isBalanced(filename))
        printf("Brackets are balanced\n");
    else
        printf("Brackets are not balanced\n");
    
    return 0;
}

// Dosya içinde bulunan parantezlerin kurallı olup olmadığını kontrol eder
bool isBalanced(const char *filename){

    // Stack oluşturma işlemi
    Stack *stack = createStack(20);
    // Stack oluşturma işlemi başarıyla gerçekleşmezse hata mesajı yazdırılır ve program sonlandırılır
    if (stack == NULL) {
        fprintf(stderr, "Memory allocation failed for the stack!\n");
        exit(EXIT_FAILURE);
    }
    // Dosyayı okuma modunda açma
    FILE *fp = fopen(filename,"r");
    // Dosya açma işlemi başarıyla gerçekleşmezse hata mesajı yazdırılır ve program sonlandırılır
    if (fp == NULL) {
        perror(filename);
        exit(EXIT_FAILURE);
    }
    // Dosyanın sonuna gelinceye kadar karakterleri okur  
    while (!feof(fp)) {
        char character = (char)fgetc(fp);
        // Eğer karakter açık parantez ise stack'e ekle (push işlemi)
        if (isOpenBracket(character))
            push(stack, character);
        else if (isCloseBracket(character)) {
            // Stack'te kapalı parantez ile karşılaştırılacak herhangi bir karakter yoksa 'false' döndürülür
            if (isEmpty(stack))
                return false;
            // Karakterler eşleşmiyorsa 'false' döndürülür
            if (!areBracketsMatching(pop(stack),character))
                return false;
        }
    }
    // Dosya kapama işlemi
    fclose(fp);
    // Stack boşsa bellek serbest bırakılır ve 'true' değeri döndürülür
    if (isEmpty(stack)) {
        freeStack(stack);
        return true;
    }
    else    
        return false;
}

// Verilen karakterin açık parantez olup olmadığını kontrol eder
bool isOpenBracket(char c){
    return (c == '(' || c == '{' || c == '[') ? true : false;
}

// Verilen karakterin kapalı parantez olup olmadığını kontrol eder
bool isCloseBracket(char c){
    return (c == ')' || c == '}' || c == ']') ? true : false;
}

// Verilen parentezlerin eşleşip eşleşmediğini kontrol eder
bool areBracketsMatching(char c1, char c2){
    return ((c1 == '(' && c2 == ')') || (c1 == '{' && c2 == '}') || (c1 == '[' && c2 == ']')) ? true : false;
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
    printf("Pushed item --> %c\n", c);
}

// Stack'ten eleman çıkarır
char pop(Stack *stack){
    if (isEmpty(stack)) {
        fprintf(stderr, "Stack is empty!\n");
        exit(EXIT_FAILURE);
    }
    printf("Popped item --> %c\n", stack->data[stack->top]);
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