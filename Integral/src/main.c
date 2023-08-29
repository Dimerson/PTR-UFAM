#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "integral.h"

// Função quadrática simples para integrar: f(x) = x^2
double funcao_quadratica(double x) {
    return x * x;
}

// Função cúbica simples para integrar: f(x) = x^3
double funcao_cubica(double x) {
    return x * x * x;
}

// Função seno para integrar: f(x) = sin(x)
double funcao_seno(double x) {
    return sin(x);
}

int main() {
	double resultado;
    double lower_limit = 0.0;
    double upper_limit = 2.0;
    int num_partitions = 1000;


	Integral* integral_quadratica = cria_integral(funcao_quadratica, lower_limit, upper_limit, num_partitions);
    resultado = calcula_integral(integral_quadratica);
    printf("Resultado da integral quadrática: %lf\n", resultado);

    Integral* integral_cubica = cria_integral(funcao_cubica, lower_limit, upper_limit, num_partitions);
    resultado = calcula_integral(integral_cubica);
    printf("Resultado da integral cúbica: %lf\n", resultado);

    Integral* integral_seno = cria_integral(funcao_seno, lower_limit, upper_limit, num_partitions);
    resultado = calcula_integral(integral_seno);
    printf("Resultado da integral do seno: %lf\n", resultado);


    destroy_integral(integral_cubica);
    destroy_integral(integral_seno);
    destroy_integral(integral_quadratica);

    return 0;
}