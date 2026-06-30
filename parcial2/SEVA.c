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
    printf("\n--- muelle virtual ---\n");
    printf("1. registrar paquete\n");
    printf("2. procesar aduana (crear contenedor)\n");
    printf("3. ver paquetes en cola\n");
    printf("4. ver contenedores en pila\n");
    printf("5. buscar contenedor\n");
    printf("6. despachar contenedor\n");
    printf("7. salir\n");
    printf("elige una opcion: ");
}

// registrar paquete
void registrar() {
    limpiar();
    char cliente[50], destino[50];
    float peso;

    printf("\n--- registrar paquete ---\n");
    printf("nombre del cliente: ");
    leer(cliente, 50);
    printf("peso (kg): ");
    scanf("%f", &peso);
    limpiar();
    printf("destino: ");
    leer(destino, 50);

    contadorPaquetes++;
    enqueue(&frente, &fin, contadorPaquetes, cliente, peso, destino);
}

// procesar aduana
void procesar() {
    if (frente == NULL) {
        printf("\nno hay paquetes en la cola.\n");
        return;
    }

    limpiar();
    printf("\n--- procesar aduana ---\n");
    char destino[50];
    printf("destino para agrupar: ");
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
        printf("contenedor creado con %d paquetes, peso %.2f kg.\n", cant, pesoTotal);
    } else {
        printf("no hay paquetes con ese destino.\n");
    }
}

// despachar contenedor
void despachar() {
    if (tope == NULL) {
        printf("\nno hay contenedores para despachar.\n");
        return;
    }
    NodoPila *despachado = pop(&tope);
    printf("\ncontenedor #%d a %s ha zarpado.\n", despachado->id, despachado->destino);
    free(despachado);
}

// buscar contenedor (usando pila temporal para no romper LIFO)
void buscar() {
    if (tope == NULL) {
        printf("\nla pila esta vacia.\n");
        return;
    }

    limpiar();
    char destino[50];
    printf("\n--- buscar contenedor ---\n");
    printf("destino a buscar: ");
    leer(destino, 50);

    NodoPila *pilaTemp = NULL;
    int encontro = 0;

    // pasamos todo a la pila temporal
    while (tope != NULL) {
        NodoPila *aux = pop(&tope);
        
        if (!encontro && strcmp(aux->destino, destino) == 0) {
            printf("\ncontenedor encontrado:\n");
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
        printf("no se encontro ese destino.\n");
    }
}

int main() {
    int opcion;

    do { 
        menu();
        if (scanf("%d", &opcion) != 1) {
            printf("entrada invalida.\n");
            limpiar();
            continue;
        }
        limpiar();

        switch (opcion) {
            case 1: registrar(); break;
            case 2: procesar(); break;
            case 3: mostrar_cola(frente); break;
            case 4: mostrar_pila(tope); break;
            case 5: buscar(); break;
            case 6: despachar(); break;
            case 7: break;
            default: printf("opcion no valida.\n");
        }
    } while (opcion != 7);

    // liberar todo antes de salir
    liberar_cola(&frente);
    liberar_pila(&tope);
    printf("\nmemoria liberada. cerrando programa.\n");

    return 0;
}