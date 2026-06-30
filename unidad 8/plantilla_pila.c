#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Nodo{
    int dato;
    struct Nodo *sig;
}Nodo;

// definir estructura de Pila
typedef struct{
    Nodo *tope;
    int tam;
}Pila;

// iniciar la Pila
void inicializarPila(Pila *p){
    p->tope = NULL;
    p->tam = 0;
}

// verificar pila vacia
bool pilaVacia(Pila *p){
    return p->tope == NULL;
}

// Definir la estructura de la Pila
void push(Pila *p, int valor){
    Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));

    if(nuevo == NULL){
        printf("Error de memoria.\n");
        return;
    }

    nuevo->dato = valor;
    nuevo->sig = p->tope;

    p->tope = nuevo;
    p->tam++;
}

// Definir la estructura de la Pila
int pop(Pila *p){
    if(pilaVacia(p)){
        printf("La pila esta vacia.\n");
        return -1;
    }

    Nodo *aux = p->tope;

    int valor = aux->dato;
    p->tope = aux->sig;
    free(aux);

    p->tam--;
    return valor;
}

// Definir la estructura de la Pila
int peek(Pila *p){
    if(pilaVacia(p)){
        printf("La pila esta vacia.\n");
        return -1;
    }

    return p->tope->dato;
}

// Obtener tamaño de la Pila
int size(Pila *p){
    return p->tam;
}

// mostrar pila
void mostrarPila(Pila *p){

    if(pilaVacia(p)){
        printf("\nPila vacia.\n");
        return;
    }

    Nodo *aux = p->tope;

    printf("\nTOPE\n");
    printf("----\n");

    while(aux != NULL){
        printf("| %d |\n",aux->dato);
        aux = aux->sig;
    }

    printf("----\n");
}

// vaciar la pila
void vaciarPila(Pila *p){

    while(!pilaVacia(p)){
        pop(p);
    }
}

// buscar item en la Pila
bool buscarEnPila(Pila *p,int valor){
    Nodo *aux = p->tope;

    while(aux!=NULL){
        if(aux->dato==valor)
            return true;
        aux=aux->sig;
    }

    return false;
}

// contar elementos/itema de la Pila
int contarItemsPila(Pila *p,int valor){
    int contador=0;

    Nodo *aux=p->tope;

    while(aux!=NULL){
        if(aux->dato==valor)
            contador++;
        aux=aux->sig;
    }

    return contador;
}

// copiar toda la Pila
Pila copiarPila(Pila *origen){
    Pila copia;
    inicializarPila(&copia);

    if(pilaVacia(origen))
        return copia;

    Pila auxiliar;
    inicializarPila(&auxiliar);

    Nodo *aux=origen->tope;

    while(aux!=NULL){
        push(&auxiliar,aux->dato);
        aux=aux->sig;
    }

    while(!pilaVacia(&auxiliar)){
        int x=pop(&auxiliar);
        push(&copia,x);
    }

    return copia;
}

// destruir la Pila
void destruirPila(Pila *p){
    vaciar(p);
    p->tope=NULL;
    p->tam=0;
}