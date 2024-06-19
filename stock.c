#include "stock.h"

int cmpNumProd(const void* d,const void* d2){
const tStock * s1=d;
const tStock * s2=d2;
return s1->numProd-s2->numProd;
}

int cmpStock(const void* d,const void* d2){
const tStock * s1=d;
const tStock * s2=d2;
return s1->stock-s2->stock;
}

void mostrarStock(void * info, unsigned tam, unsigned n, void * params){
tStock * s=info;
printf("cod:%d -despcripcion:%s -cant:%d \n",s->numProd,s->descripcion,s->stock);
}

void mostrarAntesDelNivel(void * info, unsigned tam, unsigned n, void * params){
tStock * s=info;
int *nivelFiltro=params;
if(*nivelFiltro<n)
    printf("cod:%d -despcripcion:%s -cant:%d \n",s->numProd,s->descripcion,s->stock);
}

void mostrarEnNivel(void * info, unsigned tam, unsigned n, void * params){
tStock * s=info;
int *nivelFiltro=params;
if(*nivelFiltro==n)
    printf("cod:%d -despcripcion:%s -cant:%d \n",s->numProd,s->descripcion,s->stock);
}

void mostrarDesdeNivel(void * info, unsigned tam, unsigned n, void * params){
tStock * s=info;
int *nivelFiltro=params;
if(*nivelFiltro>n)
    printf("cod:%d -despcripcion:%s -cant:%d \n",s->numProd,s->descripcion,s->stock);
}

void mostrarClaveStock(void *d){
tStock * s=d;
if(s==NULL)
    puts("sin elemento");
else
    printf("%d\n",s->numProd);
}

void imprimirClaveConForma(void * d, unsigned tam, unsigned n, void * params)
{
    tStock * s = d;
    printf("%*s->%3d\n",n*3,"", s->numProd);
}

void escribirArchBin(void * info, unsigned tam, unsigned n, void * params)
{
    fwrite(info, tam, 1, (FILE*)params);
}

void aumentarStock(void * info, unsigned tam, unsigned n, void * params){
    tStock * s = info;
    int * stock=params;
    s->stock+=*stock;
}
