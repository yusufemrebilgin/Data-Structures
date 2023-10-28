#include <stdio.h>

unsigned long long factorial(int);

int main(void){

    int num;
    printf("Please enter a number: ");
    scanf("%d", &num);

    printf("Factorial (%d!) : %llu\n", num, factorial(num));

    return 0;
}

unsigned long long factorial(int n){
    return (n <= 1) ? 1 : n * factorial(n-1);
}   