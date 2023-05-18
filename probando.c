#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int funcion1();
int funcion2();
void funcion3(int num1, int num2);

void main(){
    funcion3(funcion1(), funcion2());
}
int funcion1(){
    printf("1");
    return 1;
}
int funcion2(){
    printf("2");
    return 2;
}
void funcion3(int num1, int num2){
    printf("3");
}