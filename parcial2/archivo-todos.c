#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ==========================================================
// [EDWIN] Definición de Estructuras de Datos
// ==========================================================
typedef struct Paquete {
    int id;
    char cliente[50];
    float peso;
    char destino[50];
    struct Paquete *siguiente;
} NodoCola;

typedef struct Contenedor {
    int idContenedor;
    char destino[50];
    float pesoTotal;
    int cantidadPaquetes;
    struct Contenedor *siguiente;
} NodoPila;

// Punteros globales para las estructuras principales
NodoCola *frenteCola = NULL;
NodoCola *finCola = NULL;
NodoPila *topePila = NULL;
int contadorPaquetes = 0;
int contadorContenedores = 0;

// ==========================================================
// [EDWIN] Funciones de Entrada y Menú
// ==========================================================
void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void leerCadena(char *destino, int max) {
    if (fgets(destino, max, stdin) != NULL) {
        destino[strcspn(destino, "\n")] = '\0'; // Eliminar salto de línea
    }
}

void mostrarMenu() {
    printf("\n========================================\n");
    printf("   MUELLE VIRTUAL - SEVA EXPRESS\n");
    printf("========================================\n");
    printf("1. Registrar Paquete en Aduana (Cola FIFO)\n");
    printf("2. Procesar Aduana y Apilar Contenedor (Cola -> Pila)\n");
    printf("3. Ver Paquetes en Aduana (Cola)\n");
    printf("4. Ver Contenedores en Muelle (Pila)\n");
    printf("5. Buscar Contenedor en Muelle (Sin romper LIFO)\n");
    printf("6. Despachar Contenedor (Desapilar LIFO)\n");
    printf("7. Salir y Liberar Memoria\n");
    printf("========================================\n");
    printf("Seleccione una opcion: ");
}

// ==========================================================
// [VICTOR] Manejo de Memoria y Operaciones Básicas
// ==========================================================

// --- COLA (FIFO) ---
void encolarPaquete(int id, char *cliente, float peso, char *destino) {
    NodoCola *nuevo = (NodoCola *)malloc(sizeof(NodoCola));
    if (nuevo == NULL) {
        printf("Error: Memoria llena.\n");
        return;
    }
    nuevo->id = id;
    strcpy(nuevo->cliente, cliente);
    nuevo->peso = peso;
    strcpy(nuevo->destino, destino);
    nuevo->siguiente = NULL;

    if (finCola == NULL) { // Cola vacía
        frenteCola = finCola = nuevo;
    } else {
        finCola->siguiente = nuevo;
        finCola = nuevo;
    }
    printf("Paquete #%d encolado en aduana.\n", id);
}

NodoCola* desencolarPaquete() {
    if (frenteCola == NULL) return NULL;
    
    NodoCola *aux = frenteCola;
    frenteCola = frenteCola->siguiente;
    if (frenteCola == NULL) finCola = NULL; // Si quedó vacía
    
    aux->siguiente = NULL; // Desconectar para usarlo
    return aux;
}

// --- PILA (LIFO) ---
void apilarContenedor(int id, char *destino, float peso, int cant) {
    NodoPila *nuevo = (NodoPila *)malloc(sizeof(NodoPila));
    if (nuevo == NULL) {
        printf("Error: Memoria llena.\n");
        return;
    }
    nuevo->idContenedor = id;
    strcpy(nuevo->destino, destino);
    nuevo->pesoTotal = peso;
    nuevo->cantidadPaquetes = cant;
    
    nuevo->siguiente = topePila;
    topePila = nuevo;
    printf("Contenedor #%d apilado en el muelle.\n", id);
}

NodoPila* desapilarContenedor() {
    if (topePila == NULL) return NULL;
    
    NodoPila *aux = topePila;
    topePila = topePila->siguiente;
    aux->siguiente = NULL;
    return aux;
}

// ==========================================================
// [DARIN] Lógica del Negocio y Flujo Principal
// ==========================================================

void registrarPaquete() {
    limpiarBuffer();
    char cliente[50], destino[50];
    float peso;

    printf("\n--- Registrar Paquete ---\n");
    printf("Nombre del cliente: ");
    leerCadena(cliente, 50);
    printf("Peso del paquete (kg): ");
    scanf("%f", &peso);
    limpiarBuffer();
    printf("Destino: ");
    leerCadena(destino, 50);

    contadorPaquetes++;
    encolarPaquete(contadorPaquetes, cliente, peso, destino);
}

void procesarAduana() {
    if (frenteCola == NULL) {
        printf("\n[ALERTA] No hay paquetes en la cola de aduana.\n");
        return;
    }

    printf("\n--- Procesando Aduana (Agrupando en Contenedor) ---\n");
    char destinoContenedor[50];
    printf("Ingrese el destino para agrupar los paquetes: ");
    leerCadena(destinoContenedor, 50);

    float pesoTotal = 0;
    int cantPaquetes = 0;
    int encontrados = 0;
    
    // [DARIN] Lógica: Recorremos la cola. Para no romper el FIFO, 
    // desencolamos y si no es del destino, lo reencolamos al final.
    int totalEnCola = 0;
    NodoCola *temp = frenteCola;
    while(temp != NULL) { totalEnCola++; temp = temp->siguiente; }

    for (int i = 0; i < totalEnCola; i++) {
        NodoCola *paquete = desencolarPaquete();
        if (strcmp(paquete->destino, destinoContenedor) == 0) {
            pesoTotal += paquete->peso;
            cantPaquetes++;
            encontrados = 1;
            free(paquete); // Ya lo procesamos, liberamos el nodo
        } else {
            // No es el destino, se vuelve a encolar al final (Rotación FIFO)
            finCola->siguiente = paquete;
            finCola = paquete;
        }
    }

    if (encontrados) {
        contadorContenedores++;
        apilarContenedor(contadorContenedores, destinoContenedor, pesoTotal, cantPaquetes);
        printf("Contenedor creado con %d paquetes y peso total %.2f kg.\n", cantPaquetes, pesoTotal);
    } else {
        printf("No se encontraron paquetes con destino '%s' en la aduana.\n", destinoContenedor);
    }
}

void despacharContenedor() {
    if (topePila == NULL) {
        printf("\n[ALERTA] No hay contenedores en el muelle para despachar.\n");
        return;
    }
    NodoPila *despachado = desapilarContenedor();
    printf("\n[DESPACHO] Contenedor #%d con destino a %s ha zarpado.\n", 
           despachado->idContenedor, despachado->destino);
    free(despachado); // Liberamos memoria del contenedor despachado
}

// ==========================================================
// [JOSE ANGEL] Integración Compleja, Búsqueda LIFO y Limpieza
// ==========================================================

// [JOSE ANGEL] Esta es la función clave para la rúbrica.
// Demuestra que NO accedemos directamente a la pila, sino que 
// usamos una pila temporal para respetar el LIFO estrictamente.
void buscarContenedorEnPila() {
    if (topePila == NULL) {
        printf("\n[ALERTA] El muelle está vacío.\n");
        return;
    }

    limpiarBuffer();
    char destinoBuscar[50];
    printf("\n--- Buscar Contenedor por Destino ---\n");
    printf("Ingrese destino a buscar: ");
    leerCadena(destinoBuscar, 50);

    NodoPila *pilaTemporal = NULL; // Pila auxiliar para no romper LIFO
    int encontrado = 0;

    // Desapilamos todo hacia la pila temporal
    while (topePila != NULL) {
        NodoPila *aux = desapilarContenedor();
        
        if (!encontrado && strcmp(aux->destino, destinoBuscar) == 0) {
            printf("\n[EXITO] Contenedor encontrado:\n");
            printf("ID: %d | Destino: %s | Peso: %.2f kg | Paquetes: %d\n", 
                   aux->idContenedor, aux->destino, aux->pesoTotal, aux->cantidadPaquetes);
            encontrado = 1;
        }
        
        // Apilamos en la temporal
        aux->siguiente = pilaTemporal;
        pilaTemporal = aux;
    }

    // Restauramos la pila original (Invirtiendo la temporal)
    while (pilaTemporal != NULL) {
        NodoPila *aux = pilaTemporal;
        pilaTemporal = pilaTemporal->siguiente;
        
        aux->siguiente = topePila;
        topePila = aux;
    }

    if (!encontrado) {
        printf("\n[INFO] No se encontró ningún contenedor con destino '%s'.\n", destinoBuscar);
    }
}

void mostrarCola() {
    if (frenteCola == NULL) {
        printf("\n[INFO] La cola de aduana está vacía.\n");
        return;
    }
    printf("\n--- Paquetes en Aduana (FIFO) ---\n");
    NodoCola *aux = frenteCola;
    while (aux != NULL) {
        printf("[ID: %d] Cliente: %s | Peso: %.2f | Destino: %s\n", 
               aux->id, aux->cliente, aux->peso, aux->destino);
        aux = aux->siguiente;
    }
}

void mostrarPila() {
    if (topePila == NULL) {
        printf("\n[INFO] El muelle está vacío.\n");
        return;
    }
    printf("\n--- Contenedores en Muelle (LIFO - Tope a Base) ---\n");
    NodoPila *aux = topePila;
    int pos = 1;
    while (aux != NULL) {
        printf("  [%d] Contenedor #%d -> Destino: %s | Peso: %.2f kg\n", 
               pos, aux->idContenedor, aux->destino, aux->pesoTotal);
        aux = aux->siguiente;
        pos++;
    }
}

// [JOSE ANGEL] Liberación total de memoria (Requisito de la rúbrica)
void liberarMemoriaTotal() {
    // Liberar Cola
    while (frenteCola != NULL) {
        NodoCola *aux = frenteCola;
        frenteCola = frenteCola->siguiente;
        free(aux);
    }
    // Liberar Pila
    while (topePila != NULL) {
        NodoPila *aux = topePila;
        topePila = topePila->siguiente;
        free(aux);
    }
    printf("\n[SYSTEM] Toda la memoria dinámica ha sido liberada. Cerrando sistema.\n");
}

// ==========================================================
// [DARIN / JOSE ANGEL] Main y Control de Flujo
// ==========================================================
int main() {
    int opcion;

    do {
        mostrarMenu();
        if (scanf("%d", &opcion) != 1) {
            printf("Error: Entrada inválida. Ingrese un número.\n");
            limpiarBuffer();
            continue;
        }
        limpiarBuffer();

        switch (opcion) {
            case 1: registrarPaquete(); break;
            case 2: procesarAduana(); break;
            case 3: mostrarCola(); break;
            case 4: mostrarPila(); break;
            case 5: buscarContenedorEnPila(); break;
            case 6: despacharContenedor(); break;
            case 7: break; // Salir
            default: printf("Opción no válida.\n");
        }
    } while (opcion != 7);

    liberarMemoriaTotal();
    return 0;
}