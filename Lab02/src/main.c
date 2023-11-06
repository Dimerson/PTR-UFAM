#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vetor.h"
#include "matrix.h"
#include "dstring.h"
#include "integral.h"
#include "modelo.h"

// Função seno para integrar: f(x) = sin(x)
double seno(double x) {
    return sin(x);
}


int main()
{
	Matrix *estado, *u, *xt, *ym, *yt;
	int n_divisoes, iteracoes;
	float tam_janela;
	iteracoes = 1;
	double resultado, x3;
	Integral* integral_seno;
	float t;
	Vetor* vetor_seno = NULL;
	Vetor* vetor_cos = NULL;
	Vetor* vetor_deg = NULL;

	float V1[2][1] = {{1},{1}};
	float V2[3][3] = {{1,0,0},{0,1,0},{0,0,1}};
	float V3[3][2] = {{1,0},{1,0},{0,1}};

	/*
	float V1[3][3] = {{1,0,0},{0,1,0},{0,0,1}};
	float V2[3][2] = {{0, 0},{0, 0},{0, 1}};

	X = cria_matrix(3,2);
	Y = cria_matrix(3,3);

	Y = copia_matrix(Y,3,3,V1);
	X = copia_matrix(X,3,3,V2);

	X = libera_matrix(X);
	Y = libera_matrix(Y);
	*/

	u = cria_matrix(2,1);
	u = copia_matrix(u,2,1,V1);
	ym = cria_matrix(3,3);
	ym = copia_matrix(ym,3,3,V2);
	estado = cria_matrix(3,2);
	estado = copia_matrix(estado,3,2,V3);
	xt = cria_matrix(3,1);
	yt = cria_matrix(3,1);

	printf("Escolha o número de divisões: ");
	scanf("%d", &n_divisoes);
	printf("\n\n");
	tam_janela = (float)20/n_divisoes;

	for(t = 0; t <= 20; t = t + tam_janela)
	{
		x3 = u_k(t);
		estado->data[0][0] = seno(x3);
		estado->data[1][0] = cos(x3);
		u->data[1][0] = x3;
		xt = multiplica_matrix(estado,u);
		yt = multiplica_matrix(ym,xt);

		vetor_seno = add_elemento(vetor_seno,yt->data[0][0]);
		vetor_cos = add_elemento(vetor_cos,yt->data[1][0]);
		vetor_deg = add_elemento(vetor_deg,yt->data[2][0]);

		/*
		integral_seno = cria_integral(seno, (x1*M_PI*0.2), (x2*M_PI*0.2), 1000);
		resultado = calcula_integral(integral_seno);
		printf("A integral de %.2f até %.2f é: %.4f\n", x1,x2,resultado);
		vetor = add_elemento(vetor,resultado);
		destroy_integral(integral_seno);
		*/
	}

	u = libera_matrix(u);
	estado = libera_matrix(estado);
	xt = libera_matrix(xt);
	ym = libera_matrix(ym);
	yt = libera_matrix(yt);

	printf("Seno: \n");
	printa_vetor(vetor_seno);
	printf("\n\n");

	printf("Cosseno: \n");
	printa_vetor(vetor_cos);
	printf("\n\n");

	printf("Grau: \n");
	printa_vetor(vetor_deg);
	printf("\n\n");


	return 0;
}