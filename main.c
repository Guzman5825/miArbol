#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "arbol.h"
#include "stock.h"

void cargarDatosAArbol(tArbol* arbol);
void grabarArchBinEnPreOrden(tArbol *arbol,char *nombre,unsigned tam);  ///enviar por parametro el orden
void leerArchBinEnPreOrden(tArbol *arbol);
void insertarNuevoStock(tArbol *arbol);
void accionesRecorrerArbol(tArbol* arbol);
void opcionesMostrarLista(tArbol* arbol);
void opcionesGrabarArbol(tArbol* arbol);
void opcionesModificarDatos(tArbol * arbol);
void opcionesOperarHojas(tArbol * arbol);
void opcionEliminarDatoPorClave(tArbol *arbol);
void opcionCargarArchivoBin(tArbol *arbol);
int main()
{
    tArbol arbol;
    tStock menor;
    crearArbol(&arbol);

    char opcion;
    do
    {
        puts("arbol actual...");

        if(!esArbolVacio(&arbol))
            mapInOrdenInversoConContexto(&arbol,0,NULL,imprimirClaveConForma);
        else
            puts("no hay arbol");

        puts("opciones...");
        puts("A)insertar nuevo stock");
        puts("B)acciones de recorrer arbol");
        puts("C)recuperar arbol de archivo pre orden");
        puts("D)acciones de buscar");
        puts("E)borrar hojas");
        puts("F)vaciar arbol");
        puts("G)eliminar por clave");
        puts("H)cargar arbol desde un archivo ordenado");
        puts("I)mostrar el menor stock siendo no clave");
        puts("X)salir");

        opcion=ingresarOpcionEntre('A','I','X');

        switch(opcion)
        {
        case 'A':
            insertarNuevoStock(&arbol);
            break;
        case 'B':
            accionesRecorrerArbol(&arbol);
            break;
        case 'C':
            leerArchBinEnPreOrden(&arbol);
            break;
        case 'D':
            puts("se eligio la opcion D");
            break;
        case 'E':
            printf("cant hojas borradas: %d\n",borrarHojas(&arbol));
            //vaciarArbol(&arbol);
            break;
        case 'F':
            printf("cant nodos borrados: %d\n",vaciarArbol(&arbol));
            break;
        case 'G':
            opcionEliminarDatoPorClave(&arbol);
            break;
        case 'H':
            opcionCargarArchivoBin(&arbol);
            break;
        case 'I':
            obtenerDatoNoClaveMenor(&arbol,&menor,sizeof(tStock),cmpStock);
            mostrarStock(&menor,sizeof(tStock),0,NULL);
            break;
        case 'X':
            puts("saliendo del programa...");
            break;
        }
        fflush(stdin);
        puts("ingrese una tecla para continuar...");
        getchar();
        system("cls");
    }
    while(opcion!='X');


    vaciarArbol(&arbol);
    puts("fin del programa...");

    return 0;
}

void cargarDatosAArbol(tArbol* arbol)
{
    tStock stocks[] =
    {
        {31, "goma de borrar", 60},
        {15, "cuaderno A5 100 hojas", 20},
        {47, "marcador azul", 25},
        {9,  "papel america x 500", 10},
        {22, "bolígrafo azul", 75},
        {37, "regla 30 cm", 40},
        {60, "cuaderno de dibujo", 20},
        {5,  "papel ledesma x 500", 10},
        {12, "cuaderno A4 80 hojas", 15},
        {18, "lápiz HB", 100},
        {25, "bolígrafo negro", 80},
        {34, "sacapuntas", 55},
        {41, "tijeras escolares", 30},
        {56, "corrector líquido", 25},
        {63, "calculadora científica", 10}
    };

    for(int i=0; i<sizeof(stocks)/sizeof(tStock); i++)
        insertarEnArbolRecursivo(arbol,&(stocks[i]),sizeof(tStock),cmpNumProd );
}

void insertarNuevoStock(tArbol *arbol)
{
    tStock stock;
    puts("ingrese numero producto (clave)");
    scanf("%d",&stock.numProd);
    puts("ingrese nombre del producto o descripcion (sin espacios)");
    scanf("%s",stock.descripcion);
    puts("ingrese la cantidad o stock");
    scanf("%d",&stock.stock);

    if( insertarEnArbolRecursivo(arbol,&stock,sizeof(tStock),cmpNumProd) == TODO_OK)
        puts("se ha ingresado correctamente");
    else
        puts("se ha modificado el producto");

    fflush(stdin);
}

void accionesRecorrerArbol(tArbol* arbol)
{
    char opcion;
    do
    {
        puts("opciones de recorrido...");
        puts("A)mostrar stocks  -B)grabar  -C)modificar datos  -D)operar hojas  -X)salir");
        opcion=ingresarOpcionEntre('A','D','X');
    }
    while(!(opcion>='A' && opcion<='D') && opcion!='X');

    switch(opcion)
    {
    case 'A':
        opcionesMostrarLista(arbol);
        break;
    case 'B':
        opcionesGrabarArbol(arbol);
        break;
    case 'C':
        opcionesModificarDatos(arbol);
        break;
    case 'D':
        opcionesOperarHojas(arbol);
        break;
    case 'X':
        puts("saliendo...");
        break;
    }
}

void opcionesMostrarLista(tArbol* arbol)
{
    Accion2 acc;
    char opcion;
    int nivel;
    do
    {
        puts("nivel...");
        puts("A)todo  -B)antes del nivel   -C)solo el nivel  -D)desde el nivel  -X)salir");
        opcion=ingresarOpcionEntre('A','D','X');
    }
    while(!(opcion>='A' && opcion<='D') && opcion!='X');

    switch(opcion)
    {
    case 'A': acc=mostrarStock;
        break;
    case 'B': acc=mostrarAntesDelNivel;
        break;
    case 'C': acc=mostrarEnNivel;
        break;
    case 'D': acc=mostrarDesdeNivel;
        break;
    case 'X':
        puts("saliendo...");
        return;
    }

    if(opcion!='A'){
        puts("ingresar nivel");
        nivel = obtenerNumero();
    }

    do{
        puts("modo recorrido...");
        puts("A)preOrden  -B)postOrden   -C)en Orden  -D)orden inversion  -X)salir");
        opcion=ingresarOpcionEntre('A','D','X');
    }
    while(!(opcion>='A' && opcion<='D') && opcion!='X');

    switch(opcion)
    {
    case 'A':
        mapPreOrdenConContexto(arbol,0,&nivel,acc);
        break;
    case 'B':
        mapPostOrdenConContexto(arbol,0,&nivel,acc);
        break;
    case 'C':
        mapInOrdenConContexto(arbol,0,&nivel,acc);
        break;
    case 'D':
        mapInOrdenInversoConContexto(arbol,0,&nivel,acc);
        break;
    case 'X':
        puts("saliendo...");
        break;
    }
}

void opcionesGrabarArbol(tArbol* arbol)
{
    FILE* arch;
    char opcion,nombreArch[100];
    do
    {
        puts("modo recorrido...");
        puts("A)preOrden  -  B)postOrden   -  C)en Orden   -  X)salir");
        opcion=ingresarOpcionEntre('A','C','X');
    }
    while(!(opcion>='A' && opcion<='C') && opcion!='X');

    puts("escriba el nombre del archivo binario, incluya la extension.bin");
    scanf("%s",nombreArch);
    fflush(stdin);

    arch=fopen(nombreArch,"wb");

    switch(opcion)
    {
    case 'A':
        mapPreOrdenConContexto(arbol,0,arch,escribirArchBin);
        break;
    case 'B':
        mapPostOrdenConContexto(arbol,0,arch,escribirArchBin);
        break;
    case 'C':
        mapInOrdenConContexto(arbol,0,arch,escribirArchBin);
        break;
    case 'X':
        puts("saliendo...");
        break;
    }
    fclose(arch);
}



void opcionesModificarDatos(tArbol * arbol){
    int valor;
    char opcion;
    do
    {
        puts("acciones...");
        puts("A)aumentarStock  -X)salir");
        opcion=ingresarOpcionEntre('A','A','X');
    }
    while(!(opcion>='A' && opcion<='A') && opcion!='X');

    switch(opcion)
    {
    case 'A':
        valor=obtenerNumero();
        mapPreOrdenConContexto(arbol,0,&valor,aumentarStock);
        break;
    case 'X':
        puts("saliendo...");
        break;
    }

}

void opcionesOperarHojas(tArbol * arbol){
    char opcion;
    do
    {
        puts("acciones...");
        puts("A)contar  B)mostrar dato  X)salir");
        opcion=ingresarOpcionEntre('A','B','X');
    }
    while(!(opcion>='A' && opcion<='B') && opcion!='X');

    switch(opcion)
    {
    case 'A':
        printf("cantidad de hojas %d\n",recorrerHojas(arbol,0,NULL,NULL));
        break;
    case 'B':
        recorrerHojas(arbol,0,NULL,mostrarStock);
        break;
    case 'X':

        puts("saliendo...");
        break;
    }

}

void leerArchBinEnPreOrden(tArbol *arbol)
{
    FILE* arch;
    tStock stock;
    int cantReg,i;
    char nombreArch[100];

    puts("escriba el nombre del archivo binario, incluya la extension.bin");
    scanf("%s",nombreArch);
    fflush(stdin);

    arch=fopen(nombreArch,"rb");
    if(arch==NULL)
    {
        puts("ARCHIVO NO ENCOTRADO.");
        return;
    }

    fseek(arch,0L,SEEK_END);
    cantReg=ftell(arch)/sizeof(tStock);

    for(i=0; i<cantReg; i++)
    {
        fseek(arch,i*sizeof(tStock),SEEK_SET);
        fread(&stock,sizeof(tStock),1,arch);
        insertarEnArbolRecursivo(arbol,&stock,sizeof(tStock),cmpNumProd);
    }
    puts("arbol Recuperado");
    fclose(arch);
}



void opcionEliminarDatoPorClave(tArbol *arbol){
    tStock stock;
    puts("ingrese la clave del producto a eliminar");
    scanf("%d",&(stock.numProd) );

    if(eliminarPorClave(arbol,&stock,sizeof(tStock),cmpNumProd))
        puts("se elimino correctamente");
    else
        puts("no se encontro clave de stock");
}

void opcionCargarArchivoBin(tArbol *arbol){
    char nombreArch[1000];
    puts("ingrese nombre archivo");
    scanf("%s",nombreArch);
    if(cargarArchBinOrdenadoAArbol(arbol,nombreArch,sizeof(tStock))==TODO_OK)
        puts("arbol cargado correctamente");
    else
        puts("no se pudo cargar el arbol");
}
