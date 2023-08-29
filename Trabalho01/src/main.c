#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"
#include "dstring.h"
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

int main()
{
	// Teste de Dstring
	Dstring *texto = aloca_dstring("Hello, ");
    texto = append_dstring(texto, "world!");
    print_dstring(texto);
    printf("\n");
    texto = libera_dstring(texto);

    Dstring* texto2 = aloca_dstring(NULL);
    print_dstring(texto2);
    texto2 = append_dstring(texto2, "Apenas um teste!");
    print_dstring(texto2);
    texto2 = libera_dstring(texto2);
    printf("\n\n");


    // Teste de Matriz
	float v1[3][2] = {{1,2},{3,4},{5,6}};
	float v2[3][2] = {{6,5},{4,3},{2,1}};
	float v3[2][4] = {{7,9,11,13},{8,10,12,14}};
	float v4[4][4] = {{10,2,3,4},{5,6,-7,8},{9,10,11,12},{13,14,15,16}};
	float v5[3][3] = {{1,0,0},{1,3,1},{1,2,0}};
	float d;

	Matrix *M1, *M2, *M3, *M4, *M5, *aux;

	M1 = cria_matrix(3,2);
	M2 = cria_matrix(3,2);
	M3 = cria_matrix(2,4);
	M4 = cria_matrix(4,4);
	M5 = cria_matrix(3,3);

	for (int i = 0; i < 3; i++)
		for(int j = 0; j < 2; j++)
		{
			M1->data[i][j] = v1[i][j];
			M2->data[i][j] = v2[i][j];
		}

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 4; j++)
			M3->data[i][j] = v3[i][j];

	for (int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			M4->data[i][j] = v4[i][j];

	for (int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			M5->data[i][j] = v5[i][j];


	printf("Matriz 1 (M1):\n\n");
	imprime_matrix(M1);
	printf("\n\n");
	printf("Matriz 2 (M2):\n\n");
	imprime_matrix(M2);
	printf("\n\n");
	printf("Matriz 3 (M3):\n\n");
	imprime_matrix(M3);
	printf("\n\n");
	printf("Matriz 4 (M4):\n\n");
	imprime_matrix(M4);
	printf("\n\n");
	printf("Matriz 5 (M5):\n\n");
	imprime_matrix(M5);
	printf("\n\n");


	printf("Soma escalar (M1 + 2):\n\n");
	aux = soma_escalar(M1,2);
	imprime_matrix(aux);
	libera_matrix(aux);
	printf("\n\n");

	printf("Subtrai escalar (M1 - 2):\n\n");
	aux = subtrai_escalar(M1,2);
	imprime_matrix(aux);
	printf("\n\n");
	libera_matrix(aux);

	printf("Multiplica escalar (M1 * 2):\n\n");
	aux = multiplica_escalar(M1,2);
	imprime_matrix(aux);
	printf("\n\n");
	libera_matrix(aux);

	printf("Soma matrizes (M1 + M2):\n\n");
	aux = soma_matrixes(M1,M2);
	imprime_matrix(aux);
	printf("\n\n");
	libera_matrix(aux);

	printf("Subtrai matrizes (M1 - M2):\n\n");
	aux = subtrai_matrixes(M1,M2);
	imprime_matrix(aux);
	printf("\n\n");
	libera_matrix(aux);

	printf("Multiplica matrizes (M1 * M3):\n\n");
	aux = multiplica_matrix(M1,M3);
	imprime_matrix(aux);
	printf("\n\n");
	libera_matrix(aux);

	printf("Transposta de M3:\n\n");
	aux = transposta(M3);
	imprime_matrix(aux);
	printf("\n\n");
	libera_matrix(aux);

	d = calcula_determinante(M4);
	printf("O Determinante de M4 eh: %.2f\n\n", d);

	printf("Invertida de M5:\n\n");
	aux = invertida(M5);
	imprime_matrix(aux);
	libera_matrix(aux);

	M1 = libera_matrix(M1);
	M2 = libera_matrix(M2);
	M3 = libera_matrix(M3);
	M4 = libera_matrix(M4);
	M5 = libera_matrix(M5);



	// Teste Integral
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