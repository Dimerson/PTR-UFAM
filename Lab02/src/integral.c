#include <stdlib.h>
#include "integral.h"

struct Integral {
    FunctionPointer function;
    double lower_limit;
    double upper_limit;
    int num_partitions;
};

Integral* cria_integral(double (*function)(double), double lower_limit, double upper_limit, int num_partitions) {
    Integral* integral = (Integral*)malloc(sizeof(Integral));
    if (integral) {
        integral->function = function;
        integral->lower_limit = lower_limit;
        integral->upper_limit = upper_limit;
        integral->num_partitions = num_partitions;
    }
    return integral;
}

// Função para calcular a integral usando o método do trapézio
double calcula_integral(Integral* integral) {
    double h = (integral->upper_limit - integral->lower_limit) / integral->num_partitions;
    double result = 0.0;

    for (int i = 0; i < integral->num_partitions; i++) {
        double x0 = integral->lower_limit + i * h;
        double x1 = x0 + h;
        result += 0.5 * h * (integral->function(x0) + integral->function(x1));
    }

    return result;
}

// Função para liberar a memória da Integral
Integral* destroy_integral(Integral* integral) {
    free(integral);
    return NULL;
}