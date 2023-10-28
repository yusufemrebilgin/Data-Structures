#include <stdio.h>

typedef struct {
    double real;
    double imaginary;
} ComplexNumber;

ComplexNumber addComplexNumbers(ComplexNumber a, ComplexNumber b);

int main(void){

    ComplexNumber complexNum1, complexNum2;

    printf("Enter real part for first number: ");
    scanf("%lf", &complexNum1.real);
    printf("Enter imaginary part for first number: ");
    scanf("%lf", &complexNum1.imaginary);

    printf("Enter real part for second number: ");
    scanf("%lf", &complexNum2.real);
    printf("Enter imaginary part for second number: ");
    scanf("%lf", &complexNum2.imaginary);

    ComplexNumber result = addComplexNumbers(complexNum1, complexNum2);

    printf("Result: %.2lf + %.2lfi\n", result.real, result.imaginary);

    return 0;
}

ComplexNumber addComplexNumbers(ComplexNumber a, ComplexNumber b){
    ComplexNumber result;
    result.real = a.real + b.real;
    result.imaginary = a.imaginary + b.imaginary;
    return result;
}