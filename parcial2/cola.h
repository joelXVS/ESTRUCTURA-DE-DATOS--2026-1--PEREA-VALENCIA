#ifndef COLA_H
#define COLA_H

// estructura del paquete
typedef struct Paquete {
    int id;
    char cliente[50];
    float peso;
    char destino[50];
    struct Paquete *siguiente;
} NodoCola;

// funciones de la cola
void enqueue(NodoCola **frente, NodoCola **fin, int id, char *cliente, float peso, char *destino);
NodoCola* dequeue(NodoCola **frente, NodoCola **fin);
void mostrar_cola(NodoCola *frente);
void liberar_cola(NodoCola **frente);

#endif