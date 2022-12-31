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
    // El uintptr_t convierte el puntero en un entero para poder hacer la operacion XOR y luego se vuelve el cambio con nodo_t*
    return (nodo_t*)((uintptr_t)(a)^(uintptr_t)(b));
}

// Crea una nueva lista
lista_t* crearLista(lista_t *Lista){
    if ((Lista = (lista_t*)malloc(sizeof(lista_t))) == NULL){
        printf("NO HAY MEMORIA SUFICIENTE!!!\n");
        exit(1);
    }

    Lista->cabeza = NULL;
    Lista->cola = NULL;

    return Lista;
}

// Retorna 1 si la lista esta vacia o 0 si no lo esta
int esVacia(lista_t *Lista){
    if (Lista->cabeza == NULL)
        return 1;
    return 0;
}

// Inserta un nodo al inicio de la lista XOR y lo hace la nueva cabeza de la lista
int insertarPrincipio(lista_t *Lista, int e){
    nodo_t *nuevo;

    // Verifica si hay memoria suficiente para el nuevo nodo
    if ((nuevo = (nodo_t*)malloc(sizeof(nodo_t))) == NULL)
        return 0;

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

    return 1;
}

// Inserta un elemento al final de la lista
int insertarFinal(lista_t *Lista, int e){
    nodo_t *nuevo;

    // Verifica si hay memoria suficiente para el nuevo nodo
    if ((nuevo = (nodo_t*)malloc(sizeof(nodo_t))) == NULL)
        return 0;

    nuevo->elemento = e;
    // Como el nuevo elemento se ingresa al final, ant_sig del nuevo nodo sera el XOR de la actual cola con NULL
    nuevo->ant_sig = XOR(Lista->cola, NULL);

    // Si la lista esta vacia, entonces se le asigna el nuevo a la cabeza y a la cola
    if (esVacia(Lista)){
        Lista->cabeza = nuevo;
        Lista->cola = nuevo;
    }   // Si la lista no esta vacia, entonces ant_sig de la cola actual sera XOR del nuevo nodo y el nodo anterior a la cola 
    else {
        nodo_t *ant = XOR(Lista->cola->ant_sig, NULL);
        Lista->cola->ant_sig = XOR(ant, nuevo);

        //Cambiamos la cola
        Lista->cola = nuevo;
    }

    return 1;
}

// Inserta un elemento de forma ordenada en la lista
int insertarOrdenado(lista_t *Lista, int e){
    nodo_t *nuevo;

    // Verifica si hay memoria suficiente para el nuevo nodo
    if ((nuevo = (nodo_t*)malloc(sizeof(nodo_t))) == NULL)
        return 0;

    nuevo->elemento = e;
    
    if (esVacia(Lista)){ // Caso en el que la lista este vacia
        nuevo->ant_sig = XOR(Lista->cabeza, NULL);
        Lista->cabeza = nuevo;
        Lista->cola = nuevo;
    }
    else if (e <= Lista->cabeza->elemento){ // Caso en el que el elemento sea menor que cualquiera de la lista
        nuevo->ant_sig = XOR(Lista->cabeza, NULL);
        nodo_t *sig = XOR(Lista->cabeza->ant_sig, NULL);
        Lista->cabeza->ant_sig = XOR(nuevo, sig);

        Lista->cabeza = nuevo;
    }
    else if (e >= Lista->cola->elemento){ // Caso en el que el elemento sea mayor que cualquiera de la lista
        nuevo->ant_sig = XOR(Lista->cola, NULL);
        nodo_t *ant = XOR(Lista->cola->ant_sig, NULL);
        Lista->cola->ant_sig = XOR(ant, nuevo);

        Lista->cola = nuevo;
    }
    else {
        // Se busca la posicion en donde el elemento de postsiguiente sea mayor que el elemento de nuevo recorriendo la lista
        nodo_t *antprevio = NULL;
        nodo_t *previo = Lista->cabeza;
        nodo_t *siguiente = XOR(antprevio, previo->ant_sig);
        nodo_t *postsiguiente = XOR(previo, siguiente->ant_sig);

        while (e >= siguiente->elemento){
            antprevio = previo;
            previo = siguiente;
            siguiente = postsiguiente;
            postsiguiente = XOR(previo, siguiente->ant_sig);
        }

        // Cuando consiga la posicion, entonces le asignara al ant_sig de nuevo el XOR del elemento previo con el siguiente
        nuevo->ant_sig = XOR(previo, siguiente);

        // Al ant_sig de previo se le asigna el XOR de antprevio con nuevo
        previo->ant_sig = XOR(antprevio, nuevo);

        // Al ant_sig de siguiente se le asigna el XOR de nuevo con postsiguiente
        siguiente->ant_sig = XOR(nuevo, postsiguiente);
    }

    return 1;
} 


// Muestra la lista de inicio a fin
void listarInicioAFinal(lista_t *Lista){
    nodo_t *actual = Lista->cabeza;
    nodo_t *previo = NULL;
    nodo_t *siguiente;

    printf("Nodos de la lista doblemente enlazada\n");

    printf("cabeza-->");
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
    printf("\b<--cola\n\n");
}

// Muestra la lista desde el final hasta el inicio
void listarFinalAInicio(lista_t *Lista){
    nodo_t *actual = Lista->cola;
    nodo_t *siguiente = NULL;
    nodo_t *previo;

    printf("Nodos de la lista doblemente enlazada\n");

    printf("cola-->");
    while (actual != NULL){
        printf("%d ", actual->elemento);

        previo = XOR(siguiente, actual->ant_sig);

        siguiente = actual;
        actual = previo;
    }
    printf("\b<--cabeza\n\n");
}

int buscar(lista_t *Lista, int e){
    nodo_t *actual = Lista->cabeza;
    nodo_t *previo = NULL;
    nodo_t *siguiente;

    while (actual != NULL){
        if (actual->elemento == e){
            printf("Se consiguio el elemento %d en la lista\n", e);
            return 1;
        } else {
            siguiente = XOR(previo, actual->ant_sig);

            previo = actual;
            actual = siguiente;
        }
    }
    printf("No se consiguio el elemento %d\n", e);
    return 0;
}

// Programa de testeo
int main(void){
    lista_t *lista1, *lista2, *lista3;

    lista1 = crearLista(lista1);
    lista2 = crearLista(lista2);
    lista3 = crearLista(lista3);

    if (esVacia(lista1))
        printf("La lista esta vacia\n");
    else 
        printf("La lista NO esta vacia\n");

    if (esVacia(lista2))
        printf("La lista esta vacia\n");
    else 
        printf("La lista NO esta vacia\n");

    insertarFinal(lista1, 5);
    insertarFinal(lista2, 3);
    insertarPrincipio(lista1, 15);
    insertarFinal(lista2, 9);
    insertarPrincipio(lista1, 10);
    insertarPrincipio(lista2, 12);
    insertarPrincipio(lista1, 50);
    insertarPrincipio(lista2, 6);
    insertarFinal(lista1, 25);
    insertarPrincipio(lista2, 15);


    if (esVacia(lista1))
        printf("La lista esta vacia\n");
    else 
        printf("La lista NO esta vacia\n");

    if (esVacia(lista2))
        printf("La lista esta vacia\n");
    else 
        printf("La lista NO esta vacia\n");

    listarInicioAFinal(lista1);
    listarInicioAFinal(lista2);
    listarFinalAInicio(lista1);
    listarFinalAInicio(lista2);

    buscar(lista1, 25);
    buscar(lista2, 9);
    buscar(lista1, 3);
    buscar(lista1, 50);
    printf("\n");

    insertarOrdenado(lista3, 16);
    insertarOrdenado(lista3, 32);
    insertarOrdenado(lista3, 64);
    insertarOrdenado(lista3, 128);
    insertarOrdenado(lista3, 256);
    insertarOrdenado(lista3, 127);
    insertarOrdenado(lista3, 17);
    insertarOrdenado(lista3, 15);
    insertarOrdenado(lista3, 280);


    listarInicioAFinal(lista3);
    listarFinalAInicio(lista3);
    
    return 0;
}