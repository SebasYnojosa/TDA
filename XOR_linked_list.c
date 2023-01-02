/* Lista doblemente enlazada mediante un unico puntero */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
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

// Borra el primer elemento de la lista
int borrarPrimero(lista_t *Lista, int *e){
    if (esVacia(Lista)) return 0;

    if (Lista->cabeza == Lista->cola){
        free(Lista->cabeza);
        Lista->cabeza = NULL;
        Lista->cola = NULL;
        return 1;
    }
    // Se crea un puntero para el elemento que se va a borrar
    nodo_t *eliminado = Lista->cabeza;
    *e = eliminado->elemento;
    
    Lista->cabeza = Lista->cabeza->ant_sig;

    Lista->cabeza->ant_sig = XOR(eliminado, Lista->cabeza->ant_sig);
    

    free(eliminado);

    return 1;
}

// Borra el ultimo elemento de la lista
int borrarFinal(lista_t *Lista, int *e){
    if (esVacia(Lista)) return 0;

    if (Lista->cola == Lista->cabeza){
        free(Lista->cola);
        Lista->cabeza = NULL;
        Lista->cola = NULL;
        return 1;
    }

    nodo_t *eliminado = Lista->cola;
    *e = eliminado->elemento;

    Lista->cola = Lista->cola->ant_sig;

    Lista->cola->ant_sig = XOR(eliminado, Lista->cola->ant_sig);

    free(eliminado);

    return 1;
}

// Vacia la lista eliminando todos los elementos de esta
int vaciarLista(lista_t *Lista){
    int i;
    if(esVacia(Lista)) return 0;

    while(borrarPrimero(Lista,&i));
    return 1;
}

// Elimina la lista dada
void eliminarLista(lista_t *Lista){
    // Primero elimina todos los elementos de la lista
    vaciarLista(Lista);

    // Luego directamente elimina los apuntadores de la lista
    free(Lista);
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
            return 1;
        } else {
            siguiente = XOR(previo, actual->ant_sig);

            previo = actual;
            actual = siguiente;
        }
    }
    return 0;
}

int main(void){
    int opMenu;
    printf("Universidad Catolica Andres Bello\n");
    printf("Algoritmos y Programacion II\n");
    printf("Proyecto 2 sobre Tipos de Datos Abstractos\n");
    printf("Listas doblemente enlazadas mediante XOR\n\n");

    do {
        printf("Que le gustaria hacer?\n\n");
        printf("1. Crear una lista sin orden\n");
        printf("2. Crear una lista auto-ordenada\n");
        printf("0. Salir del programa\n");
        printf("? ");
        scanf("%i",&opMenu);
        while (opMenu < 0 || opMenu > 2){
            printf("\nOpcion invalida\n");
            printf("Que le gustaria hacer?\n\n");
            printf("1. Crear una lista sin orden\n");
            printf("2. Crear una lista auto-ordenada\n");
            printf("0. Salir del programa\n");
            printf("? ");
            scanf("%i",&opMenu);
        }   
        if (opMenu == 1){
            lista_t *listaNOrd; // Lista no ordenada
            listaNOrd = crearLista(listaNOrd);
            int op;
            do {
                printf("\nQue desea hacer con la lista no ordenada?\n\n");
                printf("1. Agregar un elemento a la cabeza\n");
                printf("2. Agregar un elemento al final\n");
                printf("3. Ver si la lista esta vacia\n");
                printf("4. Eliminar la cabeza de la lista\n");
                printf("5. Eliminar el final de la lista\n");
                printf("6. Buscar un elemento en la lista\n");
                printf("7. Vaciar la lista\n");
                printf("8. Mostrar la lista desde la cabeza hasta el final\n");
                printf("9. Mostrar la lista desde el final hasta la cabeza\n");
                printf("0. Eliminar la lista y salir al menu\n");
                printf("? ");
                scanf("%i", &op);
                while (op < 0 || op > 8){
                    printf("Opcion Invalida!!!\n");
                    printf("\nQue desea hacer con la lista no ordenada?\n\n");
                    printf("1. Agregar un elemento a la cabeza\n");
                    printf("2. Agregar un elemento al final\n");
                    printf("3. Ver si la lista esta vacia\n");
                    printf("4. Eliminar la cabeza de la lista\n");
                    printf("5. Eliminar el final de la lista\n");
                    printf("6. Buscar un elemento en la lista\n");
                    printf("7. Vaciar la lista\n");
                    printf("8. Mostrar la lista desde la cabeza hasta el final\n");
                    printf("9. Mostrar la lista desde el final hasta la cabeza\n");
                    printf("0. Eliminar la lista y salir al menu\n");
                    printf("? ");
                    scanf("%i", &op);
                }
                switch (op)
                {
                    case 1:{
                        int e;
                        printf("Ingrese el valor que quiera agregar a la cabeza\n");
                        printf("? ");
                        scanf("%d", &e);

                        if (insertarPrincipio(listaNOrd, e))
                            printf("Se introdujo %d a la cabeza\n",e);
                        else 
                            printf("MEMORIA INSUFICIENTE!!!\n");
                        getch();
                        break;
                    } 
                    case 2:{
                        int e;
                        printf("Ingrese el valor que quiera agregar al final\n");
                        printf("? ");
                        scanf("%d", &e);

                        if (insertarFinal(listaNOrd, e))
                            printf("Se introdujo %d al final\n",e);
                        else 
                            printf("MEMORIA INSUFICIENTE!!!\n");
                        getch();
                        break;
                    }
                    case 3:{
                        if (esVacia(listaNOrd))
                            printf("La lista esta vacia\n");
                        else 
                            printf("La lista NO esta vacia\n");
                        getch();
                        break;
                    }
                    case 4:{
                        int i;
                        if (borrarPrimero(listaNOrd,&i))
                            printf("Se elimino el elemento %d de la cabeza\n", i);
                        else
                            printf("La lista esta vacia, por lo tanto no se le puede quitar ningun elemento\n");
                        getch();
                        break;
                    }
                    case 5:{
                        int i;
                        if (borrarFinal(listaNOrd,&i))
                            printf("Se elimino el elemento %d del final\n", i);
                        else 
                            printf("La lista esta vacia, por lo tanto no se le puede quitar ningun elemento\n");
                        getch();
                        break;
                    }
                    case 6:{
                        int e;
                        printf("Ingrese el valor que desea buscar en la lista\n");
                        printf("? ");
                        scanf("%i",&e);
                        if(buscar(listaNOrd,e))
                            printf("Se ha encontrado el elemento %d en la lista\n",e);
                        else 
                            printf("El elemento %d no se encuentra en la lista\n",e);

                        getch();
                        break;
                    }
                    case 7:{
                        vaciarLista(listaNOrd);
                        printf("La lista se vacio completamente\n");
                        getch();
                        break;
                    }
                    case 8:{
                        listarInicioAFinal(listaNOrd);
                        getch();
                        break;
                    }
                    case 9:{
                        listarFinalAInicio(listaNOrd);
                        getch();
                        break;
                    }

                }
            }while (op != 0);
        }
        else if (opMenu == 2){
            lista_t *listaOrd; // La lista ordenada
            listaOrd = crearLista(listaOrd);
            int op;
            do {
                printf("\nQue desea hacer con la lista no ordenada?\n\n");
                printf("1. Agregar un elemento a la lista\n");
                printf("2. Ver si la lista esta vacia\n");
                printf("3. Eliminar la cabeza de la lista\n");
                printf("4. Eliminar el final de la lista\n");
                printf("5. Vaciar la lista\n");
                printf("6. Buscar un elemento en la lista\n");
                printf("7. Mostrar la lista desde la cabeza hasta el final\n");
                printf("8. Mostrar la lista desde el final hasta la cabeza\n");
                printf("0. Eliminar la lista y salir al menu\n");
                printf("? ");
                scanf("%i", &op);
                while (op < 0 || op > 7){
                    printf("Opcion Invalida!!!\n");
                    printf("\nQue desea hacer con la lista no ordenada?\n\n");
                    printf("1. Agregar un elemento a la lista\n");
                    printf("2. Ver si la lista esta vacia\n");
                    printf("3. Eliminar la cabeza de la lista\n");
                    printf("4. Eliminar el final de la lista\n");
                    printf("5. Vaciar la lista\n");
                    printf("6. Buscar un elemento en la lista\n");
                    printf("7. Mostrar la lista desde la cabeza hasta el final\n");
                    printf("8. Mostrar la lista desde el final hasta la cabeza\n");
                    printf("0. Eliminar la lista y salir al menu\n");
                    printf("? ");
                    scanf("%i", &op);
                }
                switch (op)
                {
                    case 1:{
                        int e;
                        printf("Ingrese el valor que quiera agregar a la lista\n");
                        printf("? ");
                        scanf("%d", &e);

                        if (insertarOrdenado(listaOrd,e))
                            printf("Se introdujo %d de forma ordenada en la lista\n",e);
                        else 
                            printf("MEMORIA INSUFICIENTE!!!\n");
                        getch();
                        break;
                    }
                    case 2:{
                        if (esVacia(listaOrd))
                            printf("La lista esta vacia\n");
                        else 
                            printf("La lista NO esta vacia\n");
                        getch();
                        break;
                    }
                    case 3:{
                        int i;
                        if (borrarPrimero(listaOrd,&i))
                            printf("Se elimino el elemento %d de la cabeza\n", i);
                        else
                            printf("La lista esta vacia, por lo tanto no se le puede quitar ningun elemento\n");
                        getch();
                        break;
                    }
                    case 4:{
                        int i;
                        if (borrarFinal(listaOrd,&i))
                            printf("Se elimino el elemento %d del final\n", i);
                        else 
                            printf("La lista esta vacia, por lo tanto no se le puede quitar ningun elemento\n");
                        getch();
                        break;
                    }
                    case 5:{
                        vaciarLista(listaOrd);
                        printf("La lista se vacio completamente\n");
                        getch();
                        break;
                    }
                    case 6:{
                        int e;
                        printf("Ingrese el valor que desea buscar en la lista\n");
                        printf("? ");
                        scanf("%i",&e);
                        if(buscar(listaOrd,e))
                            printf("Se ha encontrado el elemento %d en la lista\n",e);
                        else 
                            printf("El elemento %d no se encuentra en la lista\n",e);

                        getch();
                        break;
                    }
                    case 7:{
                        listarInicioAFinal(listaOrd);
                        getch();
                        break;
                    }
                    case 8:{
                        listarFinalAInicio(listaOrd);
                        getch();
                        break;
                    }

                }
            }while (op != 0);
        }
    }while(opMenu != 0);

    printf("\nGracias por usar este programa!!!\n");

    return 0;
}