#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MINIMO(x,y) ( (x)<(y)? (x) : (y) )

#define FALSE 0
#define TRUE 1
#define SIN_MEMORIA 3
#define SIN_ELEMENTOS 2
#define TODO_OK 1
#define ERROR 0
#define INGRESO_MAS_ELEMENTO 5
#define ELIMINARON_ELEMENTOS 4
#define NO_ENCONTRADO 0
#define CLAVE_DUP 6
#define ERROR_ARCH 0
typedef struct sNodo_a
{
    void* dato;
    unsigned tam;
    struct sNodo_a* izq;        //hijo izquierdo
    struct sNodo_a* der;          //hijo derecho
}tNodo;

typedef tNodo* tArbol;

typedef int (*Cmp)(const void*,const void*);
typedef void (*Accion)(void*);                  //solo acciona con respecto al dato del nodo (mostrar)
///Accion2:dato del nodo actual,tamanio del nodo,nivel de nodo, parametros si es que se quiere escribir por otro lado
typedef void (*Accion2)(void*,unsigned,unsigned,void*);
typedef void (*fReduce)(void*,const void*);    //dato a acumular- dato de la lista

///Leer: dirrecion donde se lee, info donde se destina la informacion, tamanio de info, posicion
typedef int (*Leer) (void *,void*,unsigned,unsigned );


void crearArbol(tArbol* pa);
int insertarEnArbolRecursivo(tArbol*p,void *d,unsigned tam,Cmp comp);
int insertarEnArbolIterativo(tArbol*p,void *d,unsigned tam,Cmp comp);
int esArbolVacio(const tArbol* pa);

//mapPreOrdenIterativoConContexto(tArbol* pa,unsigned n,void* contexto,Accion2 accion);

void mapInOrden(tArbol* pa,Accion accion);
void mapInOrdenInverso(tArbol* pa,Accion accion);
void mapPreOrden(tArbol* pa,Accion accion);
void mapPostOrden(tArbol* pa,Accion accion);

void mapInOrdenConContexto(tArbol* pa,unsigned n,void* contexto,Accion2 accion);
void mapInOrdenInversoConContexto(tArbol* pa,unsigned n,void* contexto,Accion2 accion);
void mapPreOrdenConContexto(tArbol* pa,unsigned n,void* contexto,Accion2 accion);
void mapPostOrdenConContexto(tArbol* pa,unsigned n,void* contexto,Accion2 accion);

void mapPreOrdenIterativoConContexto(tArbol* pa,unsigned n,void* contexto,Accion2 accion);

int recorrerHojas(tArbol* pa,unsigned n,void* contexto,Accion2 accion);

int vaciarArbol(tArbol *pa);
int obtenerDatoPorClaveArbol(tArbol *pa,void *d,unsigned tam,Cmp cmp);
///obtener sub arbol aatraves de una clave

int borrarHojas(tArbol *pa);

void recorrerHastaNivelEnOrden(tArbol* pa,unsigned n,void* contexto,Accion2 accion);

int buscarMenorNoClave(tArbol *pa,tArbol **menor,Cmp cmp);
int obtenerDatoNoClaveMenor(tArbol *pa,void *d,unsigned tam,Cmp cmp);   ///recorrido pre orden

//--- eliminacion de dato
unsigned alturaArbol(tArbol * pa);
tNodo** buscarNodo(tArbol* pa,void*dato, Cmp cmp);
tNodo** buscarNodoMayor(tArbol* pa);
tNodo** buscarNodoMenor(tArbol* pa);
int eliminarNodoRaiz(tArbol* pa);

int eliminarPorClave(tArbol* pa,void *dato,unsigned tam,Cmp cmp);
//--- lectura de datos inorden
int leerDesdeArchivoBin(void* pf, void * dato, unsigned tam, unsigned pos);
int cargarDesdeDatosOrdenadosRec(tArbol *pa,void* datoFuente,unsigned tamDato,Leer leer,int li,int ls);
int cargarArchBinOrdenadoAArbol(tArbol* pa,const char* nombreArchivo,unsigned tamDato);
#endif // ARBOL_H_INCLUDED
