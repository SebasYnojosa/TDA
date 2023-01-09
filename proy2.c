#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "lista.h"


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
            lista_t *listaNOrd = NULL; // Lista no ordenada
            listaNOrd = crearLista(listaNOrd);
            int op;
            do {
                printf("\nQue desea hacer con la lista no ordenada?\n\n");
                printf("1.  Agregar un elemento a la cabeza\n");
                printf("2.  Agregar un elemento al final\n");
                printf("3.  Ver si la lista esta vacia\n");
                printf("4.  Eliminar la cabeza de la lista\n");
                printf("5.  Eliminar el final de la lista\n");
                printf("6.  Eliminar la primera ocurrencia\n");
                printf("7.  Buscar un elemento en la lista\n");
                printf("8.  Vaciar la lista\n");
                printf("9.  Mostrar la lista desde la cabeza hasta el final\n");
                printf("10. Mostrar la lista desde el final hasta la cabeza\n");
                printf("11. Contar los elementos de la lista\n");
                printf("0.  Eliminar la lista y salir al menu\n");
                printf("? ");
                scanf("%i", &op);
                while (op < 0 || op > 11){
                    printf("\nQue desea hacer con la lista no ordenada?\n\n");
                    printf("1.  Agregar un elemento a la cabeza\n");
                    printf("2.  Agregar un elemento al final\n");
                    printf("3.  Ver si la lista esta vacia\n");
                    printf("4.  Eliminar la cabeza de la lista\n");
                    printf("5.  Eliminar el final de la lista\n");
                    printf("6.  Eliminar la primera ocurrencia\n");
                    printf("7.  Buscar un elemento en la lista\n");
                    printf("8.  Vaciar la lista\n");
                    printf("9.  Mostrar la lista desde la cabeza hasta el final\n");
                    printf("10. Mostrar la lista desde el final hasta la cabeza\n");
                    printf("11. Contar los elementos de la lista\n");
                    printf("0.  Eliminar la lista y salir al menu\n");
                    printf("? ");
                    scanf("%i", &op);
                    getchar();
                }
                switch (op)
                {
                    case 1:{
                        int e;
                        printf("Ingrese el valor que quiera agregar a la cabeza\n");
                        printf("? ");
                        scanf("%d", &e);
                        getchar();

                        if (insertarPrincipio(listaNOrd, e))
                            printf("Se introdujo %d a la cabeza\n",e);
                        else 
                            printf("MEMORIA INSUFICIENTE!!!\n");

                        printf("\nPresiona para continuar...\n");
                        getchar();
                        break;
                    } 
                    case 2:{
                        int e;
                        printf("Ingrese el valor que quiera agregar al final\n");
                        printf("? ");
                        scanf("%d", &e);
                        getchar();

                        if (insertarFinal(listaNOrd, e))
                            printf("Se introdujo %d al final\n",e);
                        else 
                            printf("MEMORIA INSUFICIENTE!!!\n");
                        getchar();
                        break;
                    }
                    case 3:{
                        if (esVacia(listaNOrd))
                            printf("La lista esta vacia\n");
                        else 
                            printf("La lista NO esta vacia\n");

                        printf("\nPresiona para continuar...\n");
                        getchar();
                        getchar();
                        break;
                    }
                    case 4:{
                        int i;
                        if (sacarPrincipio(listaNOrd,&i))
                            printf("Se elimino el elemento %d de la cabeza\n", i);
                        else
                            printf("La lista esta vacia, por lo tanto no se le puede quitar ningun elemento\n");

                        printf("\nPresiona para continuar...\n");
                        getchar();
                        getchar();
                        break;
                    }
                    case 5:{
                        int i;
                        if (sacarFinal(listaNOrd,&i))
                            printf("Se elimino el elemento %d del final\n", i);
                        else 
                            printf("La lista esta vacia, por lo tanto no se le puede quitar ningun elemento\n");

                        printf("\nPresiona para continuar...\n");
                        getchar();
                        getchar();
                        break;
                    }
                    case 6:{
                        int e;
                        printf("Ingrese el elemento que quiere eliminar de la lista\n");
                        printf("? ");
                        scanf("%d", &e);
                        getchar();
                        if(sacarPrimeraOcurrencia(listaNOrd,e))
                            printf("Se borro la primera ocurrencia de %d de la lista\n",e);
                        else
                            printf("No se consiguio %d en la lista, por lo tanto no se pudo realizar la operacion\n",e);
                        
                        printf("\nPresiona para continuar...\n");
                        getchar();
                        break;
                    }
                    case 7:{
                        int e;
                        printf("Ingrese el valor que desea buscar en la lista\n");
                        printf("? ");
                        scanf("%i",&e);
                        getchar();
                        if(buscar(listaNOrd,e))
                            printf("Se ha encontrado el elemento %d en la lista\n",e);
                        else 
                            printf("El elemento %d no se encuentra en la lista\n",e);

                        printf("\nPresiona para continuar...\n");
                        getchar();
                        break;
                    }
                    case 8:{
                        Inicializar(listaNOrd);
                        printf("La lista se vacio completamente\n");

                        printf("\nPresiona para continuar...\n");
                        getchar();
                        getchar();
                        break;
                    }
                    case 9:{
                        listarInicioAFinal(listaNOrd);

                        printf("\nPresiona para continuar...\n");
                        getchar();
                        getchar();
                        break;
                    }
                    case 10:{
                        listarFinalAInicio(listaNOrd);

                        printf("\nPresiona para continuar...\n");
                        getchar();
                        getchar();
                        break;
                    }
                    case 11:{
                        printf("La lista contiene %d elementos\n",contar(listaNOrd));
                        printf("\nPresiona para continuar...\n");
                        getchar();
                        getchar();
                        break;
                    }
                }
            }while (op != 0);
        }
        else if (opMenu == 2){
            lista_t *listaOrd = NULL; // La lista ordenada
            listaOrd = crearLista(listaOrd);
            int op;
            do {
                printf("\nQue desea hacer con la lista no ordenada?\n\n");
                printf("1.  Agregar un elemento a la lista\n");
                printf("2.  Ver si la lista esta vacia\n");
                printf("3.  Eliminar la cabeza de la lista\n");
                printf("4.  Eliminar el final de la lista\n");
                printf("5.  Eliminar la primera ocurrencia\n");
                printf("6.  Vaciar la lista\n");
                printf("7.  Buscar un elemento en la lista\n");
                printf("8.  Mostrar la lista desde la cabeza hasta el final\n");
                printf("9.  Mostrar la lista desde el final hasta la cabeza\n");
                printf("10. Contar los elementos de la lista\n");
                printf("0.  Eliminar la lista y salir al menu\n");
                printf("? ");
                scanf("%i", &op);
                while (op < 0 || op > 10){
                    printf("\nQue desea hacer con la lista no ordenada?\n\n");
                    printf("1.  Agregar un elemento a la lista\n");
                    printf("2.  Ver si la lista esta vacia\n");
                    printf("3.  Eliminar la cabeza de la lista\n");
                    printf("4.  Eliminar el final de la lista\n");
                    printf("5.  Eliminar la primera ocurrencia\n");
                    printf("6.  Vaciar la lista\n");
                    printf("7.  Buscar un elemento en la lista\n");
                    printf("8.  Mostrar la lista desde la cabeza hasta el final\n");
                    printf("9.  Mostrar la lista desde el final hasta la cabeza\n");
                    printf("10. Contar los elementos de la lista\n");
                    printf("0.  Eliminar la lista y salir al menu\n");
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
                        getchar();

                        if (insertarOrdenado(listaOrd,e))
                            printf("Se introdujo %d de forma ordenada en la lista\n",e);
                        else 
                            printf("MEMORIA INSUFICIENTE!!!\n");

                        printf("\nPresiona para continuar...\n");
                        getchar();
                        break;
                    }
                    case 2:{
                        if (esVacia(listaOrd))
                            printf("La lista esta vacia\n");
                        else 
                            printf("La lista NO esta vacia\n");

                        printf("\nPresiona para continuar...\n");
                        getchar();
                        getchar();
                        break;
                    }
                    case 3:{
                        int i;
                        if (sacarPrincipio(listaOrd,&i))
                            printf("Se elimino el elemento %d de la cabeza\n", i);
                        else
                            printf("La lista esta vacia, por lo tanto no se le puede quitar ningun elemento\n");

                        printf("\nPresiona para continuar...\n");
                        getchar();
                        getchar();
                        break;
                    }
                    case 4:{
                        int i;
                        if (sacarFinal(listaOrd,&i))
                            printf("Se elimino el elemento %d del final\n", i);
                        else 
                            printf("La lista esta vacia, por lo tanto no se le puede quitar ningun elemento\n");

                        printf("\nPresiona para continuar...\n");
                        getchar();
                        getchar();
                        break;
                    }
                    case 5:{
                        int e;
                        printf("Ingrese el elemento que quiere eliminar de la lista\n");
                        printf("? ");
                        scanf("%d", &e);
                        getchar();
                        if(sacarPrimeraOcurrencia(listaOrd,e))
                            printf("Se borro la primera ocurrencia de %d de la lista\n",e);
                        else
                            printf("No se consiguio %d en la lista, por lo tanto no se pudo realizar la operacion\n",e);
                        
                        printf("\nPresiona para continuar...\n");
                        getchar();
                        break;
                    }
                    case 6:{
                        Inicializar(listaOrd);
                        printf("La lista se vacio completamente\n");

                        printf("\nPresiona para continuar...\n");
                        getchar();
                        getchar();
                        break;
                    }
                    case 7:{
                        int e;
                        printf("Ingrese el valor que desea buscar en la lista\n");
                        printf("? ");
                        scanf("%i",&e);
                        getchar();
                        if(buscar(listaOrd,e))
                            printf("Se ha encontrado el elemento %d en la lista\n",e);
                        else 
                            printf("El elemento %d no se encuentra en la lista\n",e);

                        printf("\nPresiona para continuar...\n");
                        getchar();
                        break;
                    }
                    case 8:{
                        listarInicioAFinal(listaOrd);
                        printf("\nPresiona para continuar...\n");
                        getchar();
                        getchar();
                        break;
                    }
                    case 9:{
                        listarFinalAInicio(listaOrd);
                        printf("\nPresiona para continuar...\n");
                        getchar();
                        getchar();
                        break;
                    }
                    case 10:{
                        printf("La lista contiene %d elementos\n",contar(listaOrd));
                        printf("\nPresiona para continuar...\n");
                        getchar();
                        getchar();
                        break;
                    }
                }
            }while (op != 0);
        }
    }while(opMenu != 0);

    printf("\nGracias por usar este programa!!!\n");

    return 0;
}