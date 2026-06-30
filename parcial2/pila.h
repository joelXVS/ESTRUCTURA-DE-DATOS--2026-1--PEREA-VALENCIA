#ifndef PILA_H
#define PILA_H

// estructura del contenedor
typedef struct Contenedor {
    int id;
    char destino[50];
    float peso;
    int paquetes;
    struct Contenedor *siguiente;
} NodoPila;

// funciones de la pila
void push(NodoPila **tope, int id, char *destino, float peso, int cant);
NodoPila* pop(NodoPila **tope);
void mostrar_pila(NodoPila *tope);
void liberar_pila(NodoPila **tope);

#endif