#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#include "areas.h"
#include "volumenes.h"
#include "utils.h"

int main() {
    int seleccion; 
    char confirmacion; 
    bool confirmado;

    bool correr = true;
    
    printf("HOLA, NEO\nBIENVENIDO A LA CALCULADORA DE JOEL\n\n");
    printf("Somos una empresa que solo maneja calculadoras de areas y volumenes de un circulo/esfera y de un cuadrado/cubo\n");
    printf("Nota: Proximamente traeremos mas...\n");

    srand(time(NULL));

    while (correr) {
        do {
            seleccion = 0;
            confirmado = false;

            printf("\nMENU DE OPCIONES:\n");
            printf("\t> Opcion #1 - Ver ejemplos\n");
            printf("\t> Opcion #2 - Calcular area\n");
            printf("\t> Opcion #3 - Calcular volumen\n");
            printf("\t> Opcion #4 - Salir del sistema\n\n");

            printf("< Seleccion > : ");
            scanf("%d", &seleccion);

            do {
                printf("\n¿Esta seguro de su seleccion - Opcion #%d?\n", seleccion);
                printf("Para confirmar escriba 's', si es un error, escriba 'n': ");
                scanf(" %c", &confirmacion);
            } while (tolower(confirmacion) != 's' && tolower(confirmacion) != 'n');

            confirmado = (tolower(confirmacion) == 's');

        } while (!confirmado);

        switch (seleccion) {
            case 1: { 
                // Ejemplos
                float radioEjemploArea, ladoEjemploA, ladoEjemploB, radioEjemploVolumen, ladoEjemploC, ladoEjemploD;

                ladoEjemploA = (rand() % 60 + 1) * 0.5;
                ladoEjemploB = (rand() % 60 + 1) * 0.5;
                radioEjemploArea = (rand() % 60 + 1) * 0.5;

                printf("\nEjemplo de area del cuadrado:\n");
                printf("Una mesa tiene una base cuadrada de lado A = %.2fcm y esta sobre una alfombra de lado B = %.2fm.\n", ladoEjemploA, ladoEjemploB);
                printf("El area de la base de la mesa es %.2fcm^2\n", areaCuadrado(ladoEjemploA));
                printf("El area de la alfombra es %.2fm^2\n", areaCuadrado(ladoEjemploB));

                printf("\nEjemplo de area del circulo:\n");
                printf("Un mantel redondo tiene un radio de %.2fm\n", radioEjemploArea);
                printf("El area del mantel redondo es %.2fm^2\n", areaCirculo(radioEjemploArea));
                
                esperar();
                
                ladoEjemploC = (rand() % 60 + 1) * 0.5;
                ladoEjemploD = (rand() % 60 + 1) * 0.5;
                radioEjemploVolumen = (rand() % 60 + 1) * 0.5;

                printf("\nEjemplo de volumen del cubo:\n");
                printf("Una pecera cubica tiene una como de lado A = %.2fm y junto a ella hay una caja de carton de lado B = %.2fcm.\n", ladoEjemploC, ladoEjemploD);
                printf("El volumen de la pecera es %.2fm^3\n", areaCuadrado(ladoEjemploA));
                printf("El volumen de la caja es %.2fcm^3\n", areaCuadrado(ladoEjemploB));

                printf("\nEjemplo de volumen de la esfera:\n");
                printf("Una pelota de playa tiene un radio de %.2fcm\n", radioEjemploVolumen);
                printf("El volumen de la pelota de playa es %.2fcm^3\n", areaCirculo(radioEjemploVolumen));
                
                esperar(); break;
            }

            case 2: {
                // Calcular áreas - cm^2
                int opcionArea;
                printf("\nCalcular area en centimetros de:\n\t1. Circulo\n\t2. Cuadrado\nSeleccione: ");
                scanf("%d", &opcionArea);

                if(opcionArea == 1) {
                    float r;
                    printf("Ingrese el radio del circulo: ");
                    scanf("%fcm", &r);
                    printf("El area del circulo es %.2fcm^2\n", areaCirculo(r));
                } else if(opcionArea == 2) {
                    float l;
                    printf("Ingrese el lado del cuadrado: ");
                    scanf("%fcm", &l);
                    printf("El area del cuadrado es %.2fcm^2\n", areaCuadrado(l));
                } else {
                    printf("Opcion invalida.\n");
                }
                
                esperar(); break;
            }

            case 3: { 
                // Calcular volumenes - m^3
                int opcionVol;
                printf("\nCalcular volumen en metros de:\n\t1. Esfera\n\t2. Cubo\nSeleccione: ");
                scanf("%d", &opcionVol);

                if(opcionVol == 1) {
                    float r;
                    printf("Ingrese el radio de la esfera: ");
                    scanf("%fm", &r);
                    printf("El volumen de la esfera es %.2fm^3\n", volumenEsfera(r));
                } else if(opcionVol == 2) {
                    float l;
                    printf("Ingrese el lado del cubo: ");
                    scanf("%fm", &l);
                    printf("El volumen del cubo es %.2fm^3\n", volumenCubo(l));
                } else {
                    printf("Opcion invalida.\n");
                }
                
                esperar(); break;
            }

            case 4: { 
                // Salir de sistema
                do {
                    printf("\n¿Quieres salir de la calculadora de Joel? (s / n): ");
                    scanf(" %c", &confirmacion);
                } while (tolower(confirmacion) != 's' && tolower(confirmacion) != 'n');

                if(tolower(confirmacion) == 's') {
                    correr = false;
                    printf("Me alegro haberte visto hoy, Neo. ¡Nos vemos luego!\n");
                } else {
                    printf("Redirigiendo al menu principal...\n");
                }
                
                break;
            }

            default:
                printf("Opcion invalida.\n");
                break;
        }
    }

    return 0;
}