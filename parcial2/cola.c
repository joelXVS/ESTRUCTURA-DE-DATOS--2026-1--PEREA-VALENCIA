#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cola.h"

// agregar paquete a la cola
void enqueue(NodoCola **frente, NodoCola **fin, int id, char *cliente, float peso, char *destino) {
    NodoCola *nuevo = (NodoCola *)malloc(sizeof(NodoCola));
    if (nuevo == NULL) {
        printf("Error: no hay datos en memoria.\n");
        return;
    }
    nuevo->id = id;
    strcpy(nuevo->cliente, cliente);
    nuevo->peso = peso;
    strcpy(nuevo->destino, destino);
    nuevo->siguiente = NULL;

    if (*fin == NULL) { // cola vacia
        *frente = *fin = nuevo;
    } else {
        (*fin)->siguiente = nuevo;
        *fin = nuevo;
    }
    printf("Paquete %d agregado a la cola.\n", id);
}

// sacar paquete de la cola
NodoCola* dequeue(NodoCola **frente, NodoCola **fin) {
    if (*frente == NULL) return NULL;
    
    NodoCola *aux = *frente;
    *frente = (*frente)->siguiente;
    if (*frente == NULL) *fin = NULL;
    
    aux->siguiente = NULL;
    return aux;
}

// mostrar paquetes en cola
void mostrar_cola(NodoCola *frente) {
    if (frente == NULL) {
        printf("La cola está vacía.\n");
        return;
    }
    printf("\n--- Paquetes en aduana ---\n");
    NodoCola *aux = frente;
    while (aux != NULL) {
        printf("[ID: %d] Cliente: %s | Peso: %.2f | Destino: %s\n", 
               aux->id, aux->cliente, aux->peso, aux->destino);
        aux = aux->siguiente;
    }
}

// liberar memoria de la cola
void liberar_cola(NodoCola **frente) {
    while (*frente != NULL) {
        NodoCola *aux = *frente;
        *frente = (*frente)->siguiente;
        free(aux);
    }
}