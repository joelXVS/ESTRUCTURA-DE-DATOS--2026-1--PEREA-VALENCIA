#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    char dato;
    struct Nodo *siguiente;
} Nodo;

// Estructura de la Cola
typedef struct Cola {
    Nodo *cab;
    Nodo *culo;
} Cola;

// inicializar la cola
void inicializarCola(Cola *c) {
    c->cab = NULL;
    c->culo = NULL;
}

// ver si cola está vacía
int estaVacia(Cola *c) {
    return (c->frente == NULL);
}

// encolar (insertar al final)
void encolar(Cola *c, int valor) {
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    if (nuevoNodo == NULL) {
        printf("Memoria llena\n");
        return;
    }
    nuevoNodo->dato = valor;
    nuevoNodo->siguiente = NULL;

    if (estaVacia(c)) {
        c->frente = nuevoNodo;
        c->fin = nuevoNodo;
    } else {
        c->fin->siguiente = nuevoNodo;
        c->fin = nuevoNodo;
    }
    printf("Encolado: %d\n", valor);
}

// desencolar (quitar del frente)
int desencolar(Cola *c) {
    if (estaVacia(c)) {
        printf("La cola esta vacia\n");
        return -1;
    }
    
    Nodo *temp = c->frente;
    int valor = temp->dato;

    c->frente = c->frente->siguiente;

    if (c->frente == NULL) {
        c->fin = NULL;
    }

    free(temp);
    return valor;
}

// mostrar los elementos de la cola
void mostrarCola(Cola *c) {
    if (estaVacia(c)) {
        printf("La cola esta vacia\n");
        return;
    }
    Nodo *actual = c->frente;
    printf("Estado de la cola: ");
    while (actual != NULL) {
        printf("%d <- ", actual->dato);
        actual = actual->siguiente;
    }
    printf("NULL\n");
}