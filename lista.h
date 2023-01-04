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
nodo_t* XOR(nodo_t *a, nodo_t *b);
// Crea una nueva lista
lista_t* crearLista(lista_t *Lista);
// Retorna 1 si la lista esta vacia o 0 si no lo esta
int esVacia(lista_t *Lista);
// Inserta un nodo al inicio de la lista XOR y lo hace la nueva cabeza de la lista
int insertarPrincipio(lista_t *Lista, int e);
// Inserta un elemento al final de la lista
int insertarFinal(lista_t *Lista, int e);
// Inserta un elemento de forma ordenada en la lista
int insertarOrdenado(lista_t *Lista, int e);
// Borra el primer elemento de la lista
int borrarPrimero(lista_t *Lista, int *e);
// Borra el ultimo elemento de la lista
int borrarFinal(lista_t *Lista, int *e);
// Borra la primera aparicion del elemento dado
int borrarPrimeraOcurrencia(lista_t *Lista, int e);
// Vacia la lista eliminando todos los elementos de esta
void Inicializar(lista_t *Lista);
// Elimina la lista dada
void eliminarLista(lista_t *Lista);
// Muestra la lista de inicio a fin
void listarInicioAFinal(lista_t *Lista);
// Muestra la lista desde el final hasta el inicio
void listarFinalAInicio(lista_t *Lista);
// Buscar la primera aparicion del elemento dado
int buscar(lista_t *Lista, int e);