#include <stdio.h>

#define MAX 100

int vectorSinOrden[MAX];
int vectorOrdenado[MAX];

int n = 0;
int datosIngresados = 0;

// Funcion para esperar
void esperar() {
    while(getchar() != '\n');
    
    printf("\nPresiona ENTER para continuar...");
    getchar();
}

// Funcion para reiniciar vector
void reiniciarVector() {
    for (int i = 0; i < n; i++) {
        vectorOrdenado[i] = vectorSinOrden[i];
    }
}

// Funcion para mostrar array guardado
void mostrarArraySinOrden() {
    if (!datosIngresados) {
        printf("\nPrimero debe ingresar los datos del array.\n");
        return;
    }

    printf("Array guardado: \n\t [ ");
    for (int i = 0; i < n; i++) {
        printf("%d ", vectorSinOrden[i]);
    }
    printf("]\n");
}

// Funcion para mostrar array ordenado
void mostrarArrayOrdenado() {
    if (!datosIngresados) {
        printf("\nPrimero debe ingresar los datos del array.\n");
        return;
    }

    printf("Array ordenado: \n\t [ ");
    for (int i = 0; i < n; i++) {
        printf("%d ", vectorOrdenado[i]);
    }
    printf("]\n");
}

// Burbuja
void ordBubble() {
    if (!datosIngresados) {
        printf("\nPrimero debe ingresar los datos del array.\n");
        return;
    }
    
    reiniciarVector();
    int aux;
    
    printf("\n============ METODO BURBUJA ============\n");

    for (int i = 0; i < n - 1; i++) {
        printf("\n--- CICLO %d ---\n", i + 1);

        for (int j = 0; j < n - i - 1; j++) {
            printf("\nDato %d es mayor que %d: %s", vectorOrdenado[j], vectorOrdenado[j + 1], (vectorOrdenado[j] > vectorOrdenado[j + 1]) ? "Verdadero" : "Falso");
            if (vectorOrdenado[j] > vectorOrdenado[j + 1]) {
                aux = vectorOrdenado[j];
                printf("\nDato tomado es %d", aux);
                printf("\nDato tomado %d ahora esta en la posicion del dato %d", vectorOrdenado[j], vectorOrdenado[j + 1]);
                vectorOrdenado[j] = vectorOrdenado[j + 1];
                printf("\nDato tomado %d ahora esta en la posicion del dato %d", vectorOrdenado[j + 1], aux);
                vectorOrdenado[j + 1] = aux;

                printf("\n\nIntercambio en el ");
                mostrarArrayOrdenado();
            }
        }

        printf("\nFin del ciclo %d -  ", i + 1);
        mostrarArrayOrdenado();
    }
}

// Selección
void ordSelection() {
    if (!datosIngresados) {
        printf("\nPrimero debe ingresar los datos del array.\n");
        return;
    }
    
    reiniciarVector();
    int min, aux;
    
    printf("\n============ METODO SELECCION ============\n");

    for (int i = 0; i < n - 1; i++) {
        min = i;
        printf("\n--- CICLO %d ---\n", i + 1);
        printf("\nDato menor seleccionado: %d", vectorOrdenado[min]);
        
        for (int j = i + 1; j < n; j++) {
            printf("\nDato menor seleccionado %d es menor que %d: %s", vectorOrdenado[j], vectorOrdenado[min], (vectorOrdenado[j] < vectorOrdenado[min]) ? "Verdadero" : "Falso");
            if (vectorOrdenado[j] < vectorOrdenado[min]) {
                min = j;
                printf("\nNuevo dato menor: %d", vectorOrdenado[min]);
            }
        }
        
        if (min != i) {
            aux = vectorOrdenado[i];
            printf("\nDato auxiliar: %d", aux);
            
            printf("\nEl dato %d ahora esta en la posición del dato menor %d", vectorOrdenado[i], vectorOrdenado[min]);
            vectorOrdenado[i] = vectorOrdenado[min];
            
            printf("\nEl dato %d ahora esta en la posicion del dato mayor %d", vectorOrdenado[min], aux);
            vectorOrdenado[min] = aux;

            printf("\nIntercambio en el ");
            mostrarArrayOrdenado();
        }

        printf("\nFin del ciclo %d - ", i + 1);
        mostrarArrayOrdenado();
    }
}

// Inserción
void ordInsertion() {
    if (!datosIngresados) {
        printf("\nPrimero debe ingresar los datos del array.\n");
        return;
    }

    reiniciarVector();
    int key, j;
    
    printf("\n============ METODO INSERCION ============\n");

    for (int i = 1; i < n; i++) {
        key = vectorOrdenado[i];
        j = i - 1;

        printf("\n--- CICLO %d ---", i);
        printf("\nNumero a insertar: %d\n", key);
        printf("Estado actual del ");
        mostrarArrayOrdenado();

        while (j >= 0 && vectorOrdenado[j] > key) {

            printf("\nEl dato del vector %d es mayor que %d: %s", vectorOrdenado[j], key, (vectorOrdenado[j] > key) ? "Verdadero" : "Falso");
            printf("\nMueve %d a la derecha", vectorOrdenado[j]);

            vectorOrdenado[j + 1] = vectorOrdenado[j];
            j--;

            printf("\nMovimiento en el ");
            mostrarArrayOrdenado();
        }

        printf("\nInsertando %d en la posicion %d", key, j + 1);

        vectorOrdenado[j + 1] = key;

        printf("\nFin del ciclo %d - ", i);
        mostrarArrayOrdenado();
    }
}

// Registrar datos
void registrarDatos() {

    int opcion;
    int cantidad;

    if (datosIngresados) {

        printf("\nYa existen %d datos en el vector\n", n);
        printf("1. Ingresar desde 0\n");
        printf("2. Agregar nuevos valores\n");
        printf("3. Cancelar\n");
        printf("Opcion: ");

        while (scanf("%d", &opcion) != 1 || opcion < 1 || opcion > 3) {
            printf("Entrada de opción invalida. Procure ingresar 1, 2 o 3: ");
            while (getchar() != '\n');
        }

    } else {
        opcion = 1;
    }

    if (opcion == 1) {

        printf("\nCantidad de datos a ingresar (máximo 100): ");

        while (scanf("%d", &n) != 1 || n <= 0 || n > MAX) {
            printf("Entrada de cantidad invalida. Ingrese un número entre 1 y %d: ", MAX);
            while (getchar() != '\n');
        }

        for (int i = 0; i < n; i++) {

            printf("Ingrese el numero %d: ", i + 1);

            while (scanf("%d", &vectorSinOrden[i]) != 1) {
                printf("Entrada para el array invalida. Ingrese un número válido: ");
                while (getchar() != '\n');
            }
        }
    
    } else if (opcion == 2) {

        printf("\nCantidad de nuevos datos para el array: ");

        while (scanf("%d", &cantidad) != 1 || cantidad <= 0 || (n + cantidad) > MAX) {
            printf("Entrada invalida para el valor máximo disponible - MÁX: %d\n", MAX - n);
            printf("Ingrese la cantidad de nuevos datos para el array: ");
            while (getchar() != '\n');
        }

        for (int i = n; i < n + cantidad; i++) {

            printf("Ingrese el numero %d: ", i + 1);

            while (scanf("%d", &vectorSinOrden[i]) != 1) {
                printf("Entrada para el array invalida. Ingrese un número válido: ");
                while (getchar() != '\n');
            }
        }
        
        n += cantidad;
    
    } else if (opcion == 3) {
        printf("Acción cancelada. \n");
        return;
    }

    reiniciarVector();
    datosIngresados = 1;

    printf("\nDatos registrados en el array correctamente\n");
}

int main() {

    int opcion;

    do {
        printf("\n========== MENU OPCIONES ==========\n");
        printf("1. Registrar datos en el array - DATOS GUARDADOS: %d/%d\n", n, MAX);
        printf("2. Mostrar array guardado\n");
        printf("3. Ordenar por Metodo Burbuja\n");
        printf("4. Ordenar por Metodo Seleccion\n");
        printf("5. Ordenar por Metodo Insercion\n");
        printf("6. Salir / Cerrar\n");
        printf("\n\tOpcion: ");
        scanf("%d", &opcion);

        switch (opcion) {

            case 1:
                registrarDatos();
                esperar();
                break;
                
            case 2:
                mostrarArraySinOrden();
                esperar();
                break;
                
            case 3:
                ordBubble();
                esperar();
                break;
                
            case 4:
                ordSelection();
                esperar();
                break;
                
            case 5:
                ordInsertion();
                esperar();
                break;
                
            case 6:
                printf("\nSaliendo del programa...\n");
                break;
                
            default:
                printf("\nEntrada de opción invalida\n");
                esperar();
        }

    } while (opcion != 6);

    return 0;
}