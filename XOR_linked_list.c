/* Lista doblemente enlazada mediante un unico puntero */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

/* Estructura de los nodos */
typedef struct nodo{
    int elemento;
    struct nodo *ant_sig; /* XOR del nodo siguiente con el anterior */
}nodo_t;

/* Retorna el valor XOR de las direcciones de los nodos */
nodo_t* XOR(nodo_t *a, nodo_t *b){
    return (nodo_t*)((uintptr_t)(a)^(uintptr_t)(b));
}

/* Inserta un nodo al inicio de la lista XOR y lo hace la nueva cabeza de la lista */
void insert(nodo_t **cabeza_ref, int e){
    nodo_t *nuevo = (nodo_t*)malloc(sizeof(nodo_t));
    nuevo->elemento = e;

    /* Como el nuevo nodo se inserta al inicio, ant_sig del nuevo nodo siempre sera XOR de la actual cabeza con NULL */
    nuevo->ant_sig = XOR(*cabeza_ref,NULL);

    /* Si la lista no esta vacia, entonces ant_sig de la cabeza actual sera XOR del nuevo nodo y el nodo siguiente a la cabeza */
    if (*cabeza_ref != NULL){
        /* (*cabeza_ref)->ant_sig sera XOR de NULL y el siguiente 
        Entonces si hacemos XOR de ant_sig con NULL, tendremos siguiente */
        nodo_t *sig = XOR((*cabeza_ref)->ant_sig, NULL);
        (*cabeza_ref)->ant_sig = XOR(nuevo, sig);
    }

    /* Cambiamos la cabeza */
    *cabeza_ref = nuevo;
}

/* Imprime el contenido de la lista hacia adelante */
void printList(nodo_t *cabeza){
    nodo_t *actual = cabeza;
    nodo_t *previo = NULL;
    nodo_t *siguiente;

    printf("Nodos de la lista doblemente enlazada\n");

    while (actual != NULL){
        // Imprime el nodo
        printf("%d<-->", actual->elemento);

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
    /* Crea la siguiente lista
    cabeza-->50<-->40<-->30<-->20<-->10 */

    nodo_t *cabeza = NULL;
    insert(&cabeza, 10);
    insert(&cabeza, 20);
    insert(&cabeza, 30);
    insert(&cabeza, 40);
    insert(&cabeza, 50);

    // Imprime la lista
    printList(cabeza);

    return 0;
}