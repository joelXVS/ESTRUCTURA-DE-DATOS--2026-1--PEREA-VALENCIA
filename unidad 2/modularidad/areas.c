#include <math.h>
#include "areas.h"

#define PI 3.1416

float areaCirculo(float radioCirculo) {
    float area = PI * pow(radioCirculo, 2);
    return area;
}

float areaCuadrado(float ladoCuadrado) {
    float area = pow(ladoCuadrado, 2);
    return area;
}