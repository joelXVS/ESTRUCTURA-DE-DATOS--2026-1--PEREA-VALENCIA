#include <math.h>
#include "volumenes.h"

#define PI 3.1416

float volumenEsfera(float radioEsfera) {
    float volumen = (4.0/3.0) * PI * pow(radioEsfera, 3);
    return volumen;
}

float volumenCubo(float ladoCubo) {
    float volumen = pow(ladoCubo, 3);
    return volumen;
}