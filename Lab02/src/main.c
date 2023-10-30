#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vetor.h"
#include "matrix.h"
#include "dstring.h"
#include "integral.h"

// Função seno para integrar: f(x) = sin(x)
double seno(double x) {
    return sin(x);
}


int main()
{
	Matrix *X, *Y;
	int n_divisoes, iteracoes;
	float tam_janela;
	iteracoes = 1;
	double resultado;
	Integral* integral_seno;
	float x1, x2;

	float V[3][3] = {{1,0,0},{0,1,0},{0,0,1}};

	X = cria_matrix(3,2);
	Y = cria_matrix(3,3);

	Y = copia_matrix(Y,3,3,V);

	X = libera_matrix(X);
	Y = libera_matrix(Y);

	printf("Escolha o número de divisões: ");
	scanf("%d", &n_divisoes);
	printf("\n\n");
	tam_janela = (float)10/n_divisoes;

	for(x1 = 0, x2 = tam_janela; x2 < 10; x1 = x2, x2 = x2+tam_janela)
	{
		integral_seno = cria_integral(seno, (x1*M_PI)/180, (x2*M_PI)/180, 1000);
		resultado = calcula_integral(integral_seno);
		printf("A integral de %.2f até %.2f é: %.6f\n", x1,x2,resultado);
		destroy_integral(integral_seno);
	}

	return 0;

}