#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "integral.h"

// Função quadrática simples para integrar: f(x) = x^2
double quadratic_function(double x) {
    return x * x;
}

// Função cúbica simples para integrar: f(x) = x^3
double cubic_function(double x) {
    return x * x * x;
}

// Função seno para integrar: f(x) = sin(x)
double sine_function(double x) {
    return sin(x);
}

int main() {
    double lower_limit = 0.0;
    double upper_limit = 2.0;
    int num_partitions = 1000;


	Integral* integral = create_integral(quadratic_function, lower_limit, upper_limit, num_partitions);
    if (integral == NULL) {
        printf("Erro ao criar a instância da Integral.\n");
        return 1;
    }

    double result = calculate_integral_trapezoidal(integral);
    printf("Resultado da integral quadrática: %lf\n", result);

    Integral* integral_cubic = create_integral(cubic_function, lower_limit, upper_limit, num_partitions);
    if (integral_cubic == NULL) {
        printf("Erro ao criar a instância da Integral.\n");
        return 1;
    }

    double result_cubic = calculate_integral_trapezoidal(integral_cubic);
    printf("Resultado da integral cúbica: %lf\n", result_cubic);


    Integral* integral_sine = create_integral(sine_function, lower_limit, upper_limit, num_partitions);
    if (integral_sine == NULL) {
        printf("Erro ao criar a instância da Integral.\n");
        return 1;
    }

    double result_sine = calculate_integral_trapezoidal(integral_sine);
    printf("Resultado da integral do seno: %lf\n", result_sine);


    destroy_integral(integral_cubic);
    destroy_integral(integral_sine);
    destroy_integral(integral);

    return 0;
}