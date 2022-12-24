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

// Funcion que guarda memoria y crea un nodo para la lista
nodo_t* crearNodo(nodo_t *Nodo, int e){
    // Guarda memoria para el nuevo nodo
    Nodo = (nodo_t*)malloc(sizeof(nodo_t));
    Nodo->elemento = e;

    return Nodo;
}

// Crea una nueva lista
void crearLista(lista_t *Lista){
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
    nodo_t *nuevo = crearNodo(nuevo, e);

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

    printf("Se ingreso el elemento %d al inicio de la lista\n", e);
}

// Inserta un elemento al final de la lista
void insertarFinal(lista_t *Lista, int e){
    nodo_t *nuevo = crearNodo(nuevo, e);

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

    printf("Se ingreso el elemento %d al final de la lista\n", e);
}

// Muestra la lista de inicio a fin
void listarInicioAFinal(lista_t Lista){
    nodo_t *actual = Lista.cabeza;
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
    printf("\b<--cola\n");
}

// Muestra la lista desde el final hasta el inicio
void listarFinalAInicio(lista_t Lista){
    nodo_t *actual = Lista.cola;
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
    printf("\b<--cabeza\n");
}

int buscar(lista_t Lista, int e){
    nodo_t *actual = Lista.cabeza;
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
    lista_t lista1, lista2;

    crearLista(&lista1);
    crearLista(&lista2);

    if (esVacia(&lista1))
        printf("La lista esta vacia\n");
    else 
        printf("La lista NO esta vacia\n");

    if (esVacia(&lista2))
        printf("La lista esta vacia\n");
    else 
        printf("La lista NO esta vacia\n");

    insertarFinal(&lista1, 5);
    insertarFinal(&lista2, 3);
    insertarPrincipio(&lista1, 15);
    insertarFinal(&lista2, 9);
    insertarPrincipio(&lista1, 10);
    insertarPrincipio(&lista2, 12);
    insertarPrincipio(&lista1, 50);
    insertarPrincipio(&lista2, 6);
    insertarFinal(&lista1, 25);
    insertarPrincipio(&lista2, 15);


    if (esVacia(&lista1))
        printf("La lista esta vacia\n");
    else 
        printf("La lista NO esta vacia\n");

    if (esVacia(&lista2))
        printf("La lista esta vacia\n");
    else 
        printf("La lista NO esta vacia\n");

    listarInicioAFinal(lista1);
    printf("\n");
    listarInicioAFinal(lista2);
    printf("\n");
    listarFinalAInicio(lista1);
    printf("\n");
    listarFinalAInicio(lista2);

    buscar(lista1, 25);
    buscar(lista2, 9);
    buscar(lista1, 3);
    buscar(lista1, 50);

    
    return 0;
}