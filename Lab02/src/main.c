#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vetor.h"
#include "matrix.h"
#include "dstring.h"
#include "integral.h"
#include "modelo.h"

// Função seno para integrar: f(x) = sin(x)
double seno(double x)
{
    return sin(x);
}

double coss(double x)
{
	return cos(x);
}

Vetor* escrever_saida(FILE *f, Vetor* V)
{
	if (V == NULL)
		return V;

	fprintf(f,"%.5f ", V->valor);
	escrever_saida(f,V->prox);
	return V;
}


int main()
{
	Matrix *estado, *u, *xt, *ym, *yt;
	int n_divisoes, iteracoes;
	float tam_janela;
	iteracoes = 1;
	double resultado, x3;
	Integral *integral_seno, *integral_cosseno, *integral_angulo;
	float t;
	Vetor* vetor_seno = NULL;
	Vetor* vetor_cos = NULL;
	Vetor* vetor_deg = NULL;
	Dstring* nome_arquivo;
	char armazena_nome[50];

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
	printf("\nDigite o nome do arquivo de saída (já com a extensão): ");
	scanf("%s",armazena_nome);

	nome_arquivo = aloca_dstring("files/");
	nome_arquivo = append_dstring(nome_arquivo,armazena_nome);

	printf("\n\n");
	tam_janela = (float)20/n_divisoes;

	for(t = 0 + tam_janela; t <= 20; t = t + tam_janela)
	{
		x3 = u_k(t);
		integral_seno = cria_integral(seno, t-tam_janela, t, 100);
		integral_cosseno = cria_integral(coss, t-tam_janela, t, 100);
		integral_angulo = cria_integral(u_t, t-tam_janela, t, 100);
		estado->data[0][0] = calcula_integral(integral_seno);
		estado->data[1][0] = calcula_integral(integral_cosseno);
		u->data[1][0] = calcula_integral(integral_angulo);
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

	FILE *arquivo;
    arquivo = fopen(nome_arquivo->data, "w");

    escrever_saida(arquivo,vetor_seno);
    fprintf(arquivo,"\n\n");
    escrever_saida(arquivo,vetor_cos);
    fprintf(arquivo,"\n\n");
    escrever_saida(arquivo,vetor_deg);
    fprintf(arquivo,"\n\n");

    vetor_seno = libera_vetor(vetor_seno);
    vetor_cos = libera_vetor(vetor_cos);
    vetor_deg = libera_vetor(vetor_deg);
    nome_arquivo = libera_dstring(nome_arquivo);


	return 0;
}