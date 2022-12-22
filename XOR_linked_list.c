/* Lista doblemente enlazada mediante un unico puntero */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

/* Estructura de los nodos */
typedef struct nodo{
    int elemento;
    struct nodo *ant_sig; /* XOR del nodo siguiente con el anterior */
}nodo_t;

/* Estructura de la lista */
typedef struct lista{
    nodo_t *cabeza, *cola;
}lista_t;

/* Retorna el valor XOR de las direcciones de los nodos */
nodo_t* XOR(nodo_t *a, nodo_t *b){
    return (nodo_t*)((uintptr_t)(a)^(uintptr_t)(b));
}

// Inicializa ambos apuntadores de la lista en NULL
void inicializar(lista_t *Lista){
    Lista->cabeza = NULL;
    Lista->cola = NULL;
}

// Retorna 1 si la lista esta vacia o 0 si no lo esta
int esVacia(lista_t *Lista){
    if (Lista->cabeza == NULL)
        return 1;
    return 0;
}

// Inserta un nodo al inicio de la lista XOR y lo hace la nueva cabeza de la lista
void insertarPrincipio(lista_t *Lista, int e){
    // Guarda memoria para el nuevo nodo
    nodo_t *nuevo = (nodo_t*)malloc(sizeof(nodo_t));
    nuevo->elemento = e;

    // Como el nuevo elemento se ingresa al principio, ant_sig del nuevo nodo sera el XOR de la actual cabeza con NULL
    nuevo->ant_sig = XOR(Lista->cabeza, NULL);

    // Si la lista esta vacia, entonces se le asigna el nuevo a la cabeza y a la cola
    if (esVacia(Lista)){
        Lista->cabeza = nuevo;
        Lista->cola = nuevo;
    } // Si la lista no esta vacia, entonces ant_sig de la cabeza actual sera XOR del nuevo nodo y el nodo siguiente a la cabeza
    else {
        // Lista->cabeza->ant_sig sera XOR de NULL y el siguiente, entonces si hacemos XOR de ant_sig con NULL, tendremos siguiente
        nodo_t *sig = XOR(Lista->cabeza->ant_sig, NULL);
        Lista->cabeza->ant_sig = XOR(nuevo, sig);

        // Cambiamos la cabeza
        Lista->cabeza = nuevo;
    }
}

void listarInicioAFinal(lista_t Lista){
    nodo_t *actual = Lista.cabeza;
    nodo_t *previo = NULL;
    nodo_t *siguiente;

    printf("Nodos de la lista doblemente enlazada\n");

    while(actual != NULL){
        // Imprime el nodo
        printf("%d ", actual->elemento);

        /* Obtiene la direccion del siguiente nodo: actual->ant_sig
        es siguiente^previo, entonces actual->ant_sig^previo sera
        siguiente^previo^previo el cual es siguiente */
        siguiente = XOR(previo, actual->ant_sig);

        // Actualiza el previo y el actual para la siguiente iteracion
        previo = actual;
        actual = siguiente;
    }
}

// Programa de testeo
int main(void){
    lista_t listap;

    inicializar(&listap);

    if (esVacia(&listap))
        printf("La lista esta vacia\n");
    else 
        printf("La lista NO esta vacia\n");

    insertarPrincipio(&listap, 15);
    insertarPrincipio(&listap, 10);
    insertarPrincipio(&listap, 50);
    insertarPrincipio(&listap, 25);
    insertarPrincipio(&listap, 30);
    insertarPrincipio(&listap, 20);
    insertarPrincipio(&listap, 35);
    insertarPrincipio(&listap, 45);


    if (esVacia(&listap))
        printf("La lista esta vacia\n");
    else 
        printf("La lista NO esta vacia\n");

    listarInicioAFinal(listap);

    
    return 0;
}