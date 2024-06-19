#include "input.h"

char ingresarOpcionEntre(char limiteL,char limiteR,char exit){
    char opcion;
    fflush(stdin);
    scanf("%c",&opcion);
    opcion=toupper(opcion);
    while( !(opcion>=limiteL && opcion<=limiteR) && opcion!=exit ){
        puts("opcion incorrecta");
        fflush(stdin);
        scanf("%c",&opcion);
        opcion=toupper(opcion);
    }
    fflush(stdin);
    return opcion;
}

int obtenerNumero(){
    int numero;
    fflush(stdin);
    puts("ingrese numero");
    scanf("%d",&numero);
    fflush(stdin);
    return numero;
}
