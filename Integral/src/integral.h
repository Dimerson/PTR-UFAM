#ifndef INTEGRAL_H
#define INTEGRAL_H

typedef struct Integral Integral;

// Ponteiro para a função que será integrada
typedef double (*FunctionPointer)(double);

Integral* cria_integral(FunctionPointer function, double lower_limit, double upper_limit, int num_partitions);

double calcula_integral(Integral* integral);

Integral* destroy_integral(Integral* integral);

#endif