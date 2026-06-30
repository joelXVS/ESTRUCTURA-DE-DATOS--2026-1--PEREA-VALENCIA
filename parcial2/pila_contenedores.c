#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pila.h"

// agregar contenedor a la pila
void push(NodoPila **tope, int id, char *destino, float peso, int cant) {
    NodoPila *nuevo = (NodoPila *)malloc(sizeof(NodoPila));
    if (nuevo == NULL) {
        printf("error: no hay memoria.\n");
        return;
    }
    nuevo->id = id;
    strcpy(nuevo->destino, destino);
    nuevo->peso = peso;
    nuevo->paquetes = cant;
    
    nuevo->siguiente = *tope;
    *tope = nuevo;
    printf("contenedor %d agregado a la pila.\n", id);
}

// sacar contenedor de la pila
NodoPila* pop(NodoPila **tope) {
    if (*tope == NULL) return NULL;
    
    NodoPila *aux = *tope;
    *tope = (*tope)->siguiente;
    aux->siguiente = NULL;
    return aux;
}

// mostrar contenedores en pila
void mostrar_pila(NodoPila *tope) {
    if (tope == NULL) {
        printf("la pila esta vacia.\n");
        return;
    }
    printf("\n--- contenedores en el muelle ---\n");
    NodoPila *aux = tope;
    int pos = 1;
    while (aux != NULL) {
        printf("  [%d] Contenedor #%d -> Destino: %s | Peso: %.2f kg\n", 
               pos, aux->id, aux->destino, aux->peso);
        aux = aux->siguiente;
        pos++;
    }
}

// liberar memoria de la pila
void liberar_pila(NodoPila **tope) {
    while (*tope != NULL) {
        NodoPila *aux = *tope;
        *tope = (*tope)->siguiente;
        free(aux);
    }
}