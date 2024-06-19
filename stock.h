#ifndef STOCK_H_INCLUDED
#define STOCK_H_INCLUDED

#include <stdio.h>

#define MAX_DESC 50

typedef struct{
    int numProd;
    char descripcion[MAX_DESC];
    int stock;
}tStock;

int cmpNumProd(const void* d,const void* d2);
void mostrarStock(void * info, unsigned tam, unsigned n, void * params);
void mostrarClaveStock(void *d);
void imprimirClaveConForma(void * info, unsigned tam, unsigned n, void * params);
void escribirArchBin(void * info, unsigned tam, unsigned n, void * params);
void aumentarStock(void * info, unsigned tam, unsigned n, void * params);
void mostrarAntesDelNivel(void * info, unsigned tam, unsigned n, void * params);
void mostrarEnNivel(void * info, unsigned tam, unsigned n, void * params);
void mostrarDesdeNivel(void * info, unsigned tam, unsigned n, void * params);
int cmpStock(const void* d,const void* d2);


#endif // STOCK_H_INCLUDED
