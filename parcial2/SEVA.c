#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cola.h"
#include "pila.h"

// variables globales
NodoCola *frente = NULL;
NodoCola *fin = NULL;
NodoPila *tope = NULL;
int contadorPaquetes = 0;
int contadorContenedores = 0;

// limpiar buffer
void limpiar() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// leer cadena
void leer(char *texto, int max) {
    if (fgets(texto, max, stdin) != NULL) {
        texto[strcspn(texto, "\n")] = '\0';
    }
}

// menu principal
void menu() {
    printf("\n--- Muelle Virtual SEVA Express---\n");
    printf("1. Registrar nuevo paquete/pedido\n");
    printf("2. Procesar pedidos a la Aduana\n");
    printf("3. Ver paquetes en cola de espera\n");
    printf("4. Ver contenedores apilados\n");
    printf("5. Buscar ubicación de contenedor\n");
    printf("6. Despachar contenedor\n");
    printf("7. Cerrar sistema\n");
    printf("Seleccione una opcion: ");
}

// registrar paquete
void registrar() {
    limpiar();
    char cliente[50], destino[50];
    float peso;

    printf("\n--- Registrar nuevo paquete ---\n");
    printf("Nombre del cliente: ");
    leer(cliente, 50);
    printf("Peso (kg): ");
    scanf("%f", &peso);
    limpiar();
    printf("Destino (país): ");
    leer(destino, 50);

    contadorPaquetes++;
    enqueue(&frente, &fin, contadorPaquetes, cliente, peso, destino);
}

// procesar aduana
void procesar() {
    if (frente == NULL) {
        printf("\nNo hay paquetes en la cola de espera.\n");
        return;
    }

    limpiar();
    printf("\n--- Procesar pedidos a la aduana ---\n");
    char destino[50];
    printf("Destino para agrupar paquetes (país): ");
    leer(destino, 50);

    float pesoTotal = 0;
    int cant = 0;
    int encontro = 0;
    
    // contamos cuantos hay en la cola
    int total = 0;
    NodoCola *temp = frente;
    while(temp != NULL) { total++; temp = temp->siguiente; }

    // recorremos la cola
    for (int i = 0; i < total; i++) {
        NodoCola *paq = dequeue(&frente, &fin);
        if (strcmp(paq->destino, destino) == 0) {
            pesoTotal += paq->peso;
            cant++;
            encontro = 1;
            free(paq); // liberamos porque ya lo procesamos
        } else {
            // lo volvemos a meter a la cola
            paq->siguiente = NULL;
            if (fin == NULL) {
                frente = fin = paq;
            } else {
                fin->siguiente = paq;
                fin = paq;
            }
        }
    }

    if (encontro) {
        contadorContenedores++;
        push(&tope, contadorContenedores, destino, pesoTotal, cant);
        printf("Contenedor creado con %d paquetes, peso %.2f kg.\n", cant, pesoTotal);
    } else {
        printf("No hay paquetes con este país de destino ingresado.\n");
    }
}

// despachar contenedor
void despachar() {
    if (tope == NULL) {
        printf("\nNo hay contenedores para despachar.\n");
        return;
    }
    NodoPila *despachado = pop(&tope);
    printf("\nContenedor #%d a %s ha zarpado y esta en camino al país de destino.\n", despachado->id, despachado->destino);
    free(despachado);
}

// buscar contenedor (usando pila temporal para no romper LIFO)
void buscar() {
    if (tope == NULL) {
        printf("\nNo hay contenedores en la pila.\n");
        return;
    }

    limpiar();
    char destino[50];
    printf("\n--- Buscar ubicación de contenedor ---\n");
    printf("Destino a buscar (país): ");
    leer(destino, 50);

    NodoPila *pilaTemp = NULL;
    int encontro = 0;

    // pasamos todo a la pila temporal
    while (tope != NULL) {
        NodoPila *aux = pop(&tope);
        
        if (!encontro && strcmp(aux->destino, destino) == 0) {
            printf("\nContenedor encontrado:\n");
            printf("ID: %d | Destino: %s | Peso: %.2f kg | Paquetes: %d\n", 
                   aux->id, aux->destino, aux->peso, aux->paquetes);
            encontro = 1;
        }
        
        // apilamos en la temporal
        aux->siguiente = pilaTemp;
        pilaTemp = aux;
    }

    // regresamos todo a la pila original
    while (pilaTemp != NULL) {
        NodoPila *aux = pilaTemp;
        pilaTemp = pilaTemp->siguiente;
        
        aux->siguiente = tope;
        tope = aux;
    }

    if (!encontro) {
        printf("No se encontró ese destino.\n");
    }
}

int main() {
    int opcion;

    do { 
        menu();
        if (scanf("%d", &opcion) != 1) {
            printf("La entrada fue invalida.\n");
            limpiar();
            continue;
        }

        switch (opcion) {
            case 1: registrar(); break;
            case 2: procesar(); break;
            case 3: mostrar_cola(frente); break;
            case 4: mostrar_pila(tope); break;
            case 5: buscar(); break;
            case 6: despachar(); break;
            case 7: break;
            default: printf("La opcion no es valida.\n");
        }
    } while (opcion != 7);

    // liberar todo antes de salir
    liberar_cola(&frente);
    liberar_pila(&tope);
    printf("\nMemoria liberada. Estamos cerrando el programa.\n");
    printf("\nGracias por usar nuestro sistema.\n\tAtt: SEVA EXPRESS\n");

    return 0;
}