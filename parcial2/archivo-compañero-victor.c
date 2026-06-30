#include <stdio.h>
#define MAX 6

int pila[MAX];
int cima = -1;

// Agregar elemento
void push(int dato) {
    if (cima == MAX - 1) {
        printf("La pila esta llena.\n");
    } else {
        cima++;
        pila[cima] = dato;
        printf("%d agregado a la pila.\n", dato);
    }
}

// Eliminar elemento
void pop() {
    if (cima == -1) {
        printf("La pila esta vacia.\n");
    } else {
        printf("%d eliminado de la pila.\n", pila[cima]);
        cima--;
    }
}

// Mostrar pila
void mostrar() {
    if (cima == -1) {
        printf("La pila esta vacia.\n");
    } else {
        printf("\nPila:\n");
        for (int i = cima; i >= 0; i--) {
            printf("%d\n", pila[i]);
        }
    }
}

int main() {
    int nC;
    int opcion ;
    int  revisadoAduana;
    do{ 
        printf("bienvenido al muelle virtual\n");
        printf("que deseas hacer\n");
        printf("1.registrar cliente y pedido\n");
        printf("2. organizar paquetes en una cola\n");
        printf("3. almacenar contenedores en una pila\n");
        printf("4. salir\n");
        scanf("%d",&opcion);
        switch (opcion)
        {
        case 1: printf("registrar cliente");
            break;
        
        case 2: 
                revisadoAduana = 0;
                printf("la verdad no sabia que poner aqui");
          
                break;
        case 3: 
                printf("ingresa los contedenores a almacenar\n");
                scanf("%d",&nC);
                push(nC);
                mostrar();
                printf("deseas ingresar otro contenedor\n");
                printf("1. si ");
                printf("2. no");
             
        }
    
    }while(opcion!=4);
return 0;
}