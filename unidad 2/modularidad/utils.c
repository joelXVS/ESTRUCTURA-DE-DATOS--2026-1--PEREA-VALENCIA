#include <stdio.h>

void esperar() {
    while(getchar() != '\n');

    printf("\nPresiona ENTER para continuar...");
    getchar();
}