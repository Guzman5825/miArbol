#include "arbol.h"

void crearArbol(tArbol* pa)
{
    *pa=NULL;
}

int insertarEnArbolRecursivo(tArbol*p,void *d,unsigned tam,Cmp comp)
{
    int cmp;
    if(*p)
    {
        if((cmp = comp(d,(*p)->dato)) > 0) //averigua donde pasa el arbol
            return insertarEnArbolRecursivo(&(*p)->der, d, tam, comp);
        else if(cmp < 0)
            return insertarEnArbolRecursivo(&(*p)->izq, d, tam, comp);
        else
            return CLAVE_DUP;  //en caso que cmp=0 entonces significa que que hubo una clave duplicada
    }

    tNodo* nue=(tNodo*)malloc(sizeof(tNodo));       //ya que *p=NULL, entonces existe *p, Y se le asigna un espacio de memoria
    if(nue==NULL)
        return SIN_MEMORIA;
    nue->dato=malloc(tam);
    if(nue->dato==NULL)
    {
        free(nue);
        return SIN_MEMORIA;
    }
    nue->tam=tam;
    memcpy(nue->dato,d,tam);
    nue->izq=nue->der=NULL;       //dado que es el dato es una hoja , entontes no tiene hijos por lo tanto pertenece a NULL
    *p=nue;
    return TODO_OK;
}

int insertarEnArbolIterativo(tArbol*p,void *d,unsigned tam,Cmp comp)
{
    int cmp;
    while(*p)
    {
        if( (cmp = comp(d,(*p)->dato)) < 0) //averigua donde pasa el arbol
            p=&((*p)->izq);
        else if(cmp > 0)
            p=&((*p)->der);
        else
            return CLAVE_DUP;  //en caso que cmp=0 entonces significa que que hubo una clave duplicada
    }

    tNodo* nue=(tNodo*)malloc(sizeof(tNodo));       //ya que *p=NULL, entonces existe *p, Y se le asigna un espacio de memoria
    if(nue==NULL)
        return SIN_MEMORIA;
    nue->dato=malloc(tam);
    if(nue->dato==NULL)
    {
        free(nue);
        return SIN_MEMORIA;
    }
    nue->tam=tam;
    memcpy(nue->dato,d,tam);
    nue->izq=nue->der=NULL;       //dado que es el dato es una hoja , entontes no tiene hijos por lo tanto pertenece a NULL
    *p=nue;
    return TODO_OK;
}

int esArbolVacio(const tArbol* pa){
    return *pa==NULL;

}

void mapInOrden(tArbol* pa,Accion accion)   //HPH
{
    if(!*pa)     //evalua si la lista esta vacia, ademas evalua , si es un hoja.
        return;

    mapInOrden(&(*pa)->izq,accion);
    accion((*pa)->dato);
    mapInOrden(&(*pa)->der,accion);
}

void mapInOrdenInverso(tArbol* pa,Accion accion)   //HPH
{
    if(!*pa)     //evalua si la lista esta vacia, ademas evalua , si es un hoja.
        return;

    mapInOrdenInverso(&(*pa)->der,accion);
    accion((*pa)->dato);
    mapInOrdenInverso(&(*pa)->izq,accion);
}

void mapPreOrden(tArbol* pa,Accion accion){ //PHH
    if(!*pa)     //evalua si la lista esta vacia, ademas evalua , si es un hoja.
        return;

    accion((*pa)->dato);
    mapPreOrden(&(*pa)->izq,accion);
    mapPreOrden(&(*pa)->der,accion);
}

void mapPostOrden(tArbol* pa,Accion accion){ //PHH
    if(!*pa)     //evalua si la lista esta vacia, ademas evalua , si es un hoja.
        return;

    mapPostOrden(&(*pa)->izq,accion);
    mapPostOrden(&(*pa)->der,accion);
    accion((*pa)->dato);
}


void mapInOrdenConContexto(tArbol* pa,unsigned n,void* contexto,Accion2 accion)
{
    if(!*pa)     //evalua si la lista esta vacia, ademas evalua , si es un hoja.
        return;

    mapInOrdenConContexto(&(*pa)->izq,n+1,contexto,accion);
    accion((*pa)->dato,(*pa)->tam,n,contexto);
    mapInOrdenConContexto(&(*pa)->der,n+1,contexto,accion);
}

void mapInOrdenInversoConContexto(tArbol* pa,unsigned n,void* contexto,Accion2 accion)
{
    if(!*pa)     //evalua si la lista esta vacia, ademas evalua , si es un hoja.
        return;

    mapInOrdenInversoConContexto(&(*pa)->der,n+1,contexto,accion);
    accion((*pa)->dato,(*pa)->tam,n,contexto);
    mapInOrdenInversoConContexto(&(*pa)->izq,n+1,contexto,accion);
}

void mapPreOrdenConContexto(tArbol* pa,unsigned n,void* contexto,Accion2 accion)
{
    if(!*pa)
        return;

    accion((*pa)->dato,(*pa)->tam,n,contexto);
    mapPreOrdenConContexto(&(*pa)->izq,n+1,contexto,accion);
    mapPreOrdenConContexto(&(*pa)->der,n+1,contexto,accion);
}

void mapPostOrdenConContexto(tArbol* pa,unsigned n,void* contexto,Accion2 accion)
{
    if(!*pa)
        return;


    mapPostOrdenConContexto(&(*pa)->izq,n+1,contexto,accion);
    mapPostOrdenConContexto(&(*pa)->der,n+1,contexto,accion);
}

int recorrerHojas(tArbol* pa,unsigned n,void* contexto,Accion2 accion){
    int cantHojas=0;
    if(!*pa)    /// en casos que sea null
        return 0;

    cantHojas+=recorrerHojas(&(*pa)->izq,n+1,contexto,accion);
    if((*pa)->izq==NULL && (*pa)->der ==NULL) {     ///si no es null significa que tiene algun nodo
        if(accion)
            accion((*pa)->dato,(*pa)->tam,n,contexto);
        cantHojas++;
    }
    cantHojas+=recorrerHojas(&(*pa)->der,n+1,contexto,accion);
    return cantHojas;
}



int vaciarArbol(tArbol *pa)
{
    int cantNodos=0;
    if(!*pa)
        return 0;
    if((*pa)->izq)
        cantNodos+=vaciarArbol(&(*pa)->izq);
    if((*pa)->der)
        cantNodos+=vaciarArbol(&(*pa)->der);
    free( (*pa)->dato );
    free(*pa);
    *pa=NULL;

    return cantNodos+1;
}

tNodo** buscarNodo(tNodo** pa,void *d,Cmp cmp)
{
    if(*pa!=NULL)
        {
    if(cmp(d,(*pa)->dato)==0)
        return pa;
    if(cmp(d,(*pa)->dato) <0)
        return buscarNodo(&(*pa)->izq,d,cmp);
    if(cmp(d,(*pa)->dato) >0)
        return buscarNodo(&(*pa)->der,d,cmp);
        }
    return NULL;
}

int obtenerDatoPorClaveArbol(tArbol *pa,void *d,unsigned tam,Cmp cmp){
    tNodo** nodo=buscarNodo(pa,d,cmp);        //busca el PUNTERO DEL PUNTERO DEL ELEMENTO A ELIMINAR
    if(nodo==NULL)    //si no lo encontro le devuelve un 0
        return 0;   //FALSO

    memcpy(d,(*nodo)->dato, MINIMO((*nodo)->tam,tam));

    return TODO_OK;
}

int borrarHojas(tArbol *pa){
    if(!*pa)
        return 0;

    if( (*pa)->izq==NULL && (*pa)->der==NULL ){
        free( (*pa)->dato );
        free( *pa );
        *pa=NULL;
        return 1;
    }

    return borrarHojas( &(*pa)->izq ) + borrarHojas( &(*pa)->der);
}

void recorrerHastaNivelEnOrden(tArbol* pa,unsigned n,void* contexto,Accion2 accion){
    if(*pa==NULL || n<=-1)
        return;
    recorrerHastaNivelEnOrden( &(*pa)->izq,n-1,contexto,accion);
    accion((*pa)->dato,(*pa)->tam,n,contexto);
    recorrerHastaNivelEnOrden( &(*pa)->der,n-1,contexto,accion);
}


tNodo** buscarNodoMayor(tArbol* pa)
{
    if(*pa==NULL)
        return NULL;
    while((*pa)->der!=NULL)
        pa=&(*pa)->der;
    return pa;
}

tNodo** buscarNodoMenor(tArbol* pa)
{
    if(*pa==NULL)
        return NULL;
    while((*pa)->izq!=NULL)
        pa=&(*pa)->izq;
    return pa;
}

int eliminarNodoRaiz(tArbol* pa)
{
    tNodo* eliminar;
    tNodo** reemplazar;
    //si no hay nada, vovler
    if(*pa==NULL)
        return 0;
    //liberar
    free( (*pa)->dato );
    if( (*pa)->izq==NULL &&  (*pa)->der==NULL )     //
    {
        free(*pa);
        *pa=NULL;
        return 1;
    }
    int hi,hd;

    hi=alturaArbol(&(*pa)->izq);    //calculo alturas
    hd=alturaArbol(&(*pa)->der);

    if(hi>hd)
        reemplazar=buscarNodoMayor( &(*pa)->izq );
    else
        reemplazar=buscarNodoMenor( &(*pa)->der );
    (*pa)->dato=(*reemplazar)->dato;    //ni bien encuentro al dato, se coloca
    (*pa)->tam=(*reemplazar)->tam;

    eliminar=*reemplazar;   //se le da el nodo que se va a eliminar

    if( (*reemplazar)->izq!=NULL )
        *reemplazar=eliminar->izq;
    else
        *reemplazar=eliminar->der;
    free(eliminar);//eliminar el dato no se hace por que ya lo tiene

    return 1;
}

unsigned alturaArbol(tArbol * pa)
{
    unsigned hi,hd;
    if(*pa==NULL)
        return 0;
    hi=alturaArbol(  &(*pa)->izq  );
    hd=alturaArbol(  &(*pa)->der );
    return hi>hd? hi+1: hd+1;
}

int eliminarPorClave(tArbol* pa,void *dato,unsigned tam,Cmp cmp){
    tArbol* elim;
    elim=buscarNodo(pa,dato,cmp);
    if(elim==NULL)
        return 0;
    memcpy(dato,(*elim)->dato,tam);     ///hay que poner el minimo
    return eliminarNodoRaiz(elim);
}

int leerDesdeArchivoBin(void* pf, void * dato, unsigned tam, unsigned pos)
{
    FILE * pfile=pf;
    fseek(pfile, pos*tam, SEEK_SET);

    return fread(dato, tam, 1, pfile)!=EOF;
}

int cargarDesdeDatosOrdenadosRec(tArbol *pa,void* datoFuente,unsigned tamDato,Leer leer,int li,int ls){
    ///obtengo las posicionse que necesito
    int m = (li+ls)/2,  //se obtiene la posicion del medio
        r;
    if (li>ls)  //si li o ls apuntal mismo elemento o estan fuera de rango, terminar
        return TODO_OK;

    ///reservar memoria , lo mismo de siempre
    tNodo* nue=malloc(sizeof(tNodo) );
    if(nue==NULL)
        return SIN_MEMORIA;
    nue->dato=malloc(tamDato);
    if(nue->dato==NULL)
        return SIN_MEMORIA;
    nue->izq=NULL;
    nue->der=NULL;
    ///intento leer el dato
    if(!leer(datoFuente,nue->dato,tamDato,m))
    {
        free(nue->dato);
        free(nue);
        return ERROR_ARCH;
    }
    *pa=nue;
    ///intento insertar los siguiente datos
    r=cargarDesdeDatosOrdenadosRec(&(*pa)->izq,datoFuente,tamDato,leer,li,m-1);
    if(r!=TODO_OK)  ///verifico si pudo con el lado izquierdo
        return r;

    return cargarDesdeDatosOrdenadosRec(&(*pa)->der,datoFuente,tamDato,leer,m+1,ls);
}

int cargarArchBinOrdenadoAArbol(tArbol* pa,const char* nombreArchivo,unsigned tamDato){
    int cantReg,r;
    FILE *pf=fopen(nombreArchivo, "rb");
    if(pf==NULL)
        return ERROR;
    fseek(pf,0L,SEEK_END);

    cantReg=ftell(pf)/tamDato;

    r=cargarDesdeDatosOrdenadosRec(pa,pf,tamDato,leerDesdeArchivoBin,0,cantReg-1);

    fclose(pf);

    return r;
}

int buscarMenorNoClave(tArbol *pa,tArbol **menor,Cmp cmp){
    if(*pa==NULL)
        return 0;
    if(cmp((*pa)->dato,(**menor)->dato)<0)
        *menor=pa;
    ///preorden
    buscarMenorNoClave(&(*pa)->izq,menor,cmp);
    buscarMenorNoClave(&(*pa)->der,menor,cmp);
    return TODO_OK;
}

int obtenerDatoNoClaveMenor(tArbol *pa,void *d,unsigned tam,Cmp cmp){
    tArbol *menor=pa;
    if(*pa==NULL)
        return ERROR;
    buscarMenorNoClave(pa,&menor,cmp);
    memcpy(d,(*menor)->dato,tam);
    return TODO_OK;
}





