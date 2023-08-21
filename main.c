#include <stdio.h>
#include <stdlib.h>

typedef struct M
{
	int r, c;
	float **data;
} Matrix;

void imprime_matrix(Matrix* M)
{
	for (int i = 0; i < M->r; i++)
	{
		for (int j = 0; j < M->c; j++)
			printf("%.2f ", M->data[i][j]);
		printf("\n");
	}
}

// Aloca memória e cria a Matriz
Matrix* cria_matrix(int rows, int cols)
{
	Matrix* M = (Matrix*)malloc(sizeof(Matrix));
	M->r = rows;
	M->c = cols;

	M->data = (int**)malloc(rows * sizeof(int*));
	for (int i = 0; i < rows; i++)
		M->data[i] = (int*)malloc(cols * sizeof(int));

	return M;
}

// Função para o usuário digitar os valores da Matriz
Matrix* recebe_valores(Matrix* M)
{
	for (int i = 0; i < M->r; i++)
		for (int j = 0; j < M->c; j++)
			scanf("%f", &M->data[i][j]);

	return M;
}

// Soma, subtrai ou multiplica a matriz A por um escalar
Matrix* opera_escalar(Matrix* M, float escalar, int flag)
{
	Matrix* aux = cria_matrix(M->r, M->c);

	for (int i = 0; i < M->r; i++)
	{
		for (int j = 0; j < M->c; j++)
		{
			if (flag == 0)
				aux->data[i][j] = M->data[i][j] + escalar;
			else
			{
				if (flag == 1)
					aux->data[i][j] = M->data[i][j] - escalar;
				else
					aux->data[i][j] = M->data[i][j] * escalar;
			}
		}
	}

	return aux;
}

Matrix* soma_escalar(Matrix* M, float escalar)
{
	return opera_escalar(M,escalar,0);
}

Matrix* subtrai_escalar(Matrix* M, float escalar)
{
	return opera_escalar(M,escalar,1);
}

Matrix* multiplica_escalar(Matrix* M, float escalar)
{
	return opera_escalar(M,escalar,2);
}

// Soma ou subtrai as matrizes A e B
Matrix* soma_modulo_matrix(Matrix* A, Matrix* B, int flag)
{
	if(A->r != B->r || A->c != B->c)
		return NULL;

	Matrix* aux = cria_matrix(A->r,A->c);

	for (int i = 0; i < A->r; i++)
	{
		for (int j = 0; j < A->c; j++)
		{
			if(flag == 0)
				aux->data[i][j] = A->data[i][j] + B->data[i][j];
			else
				aux->data[i][j] = A->data[i][j] - B->data[i][j];
		}
	}

	return aux;
}

Matrix* soma_matrixes(Matrix* A, Matrix* B)
{
	return soma_modulo_matrix(A,B,0);
}

Matrix* subtrai_matrixes(Matrix* A, Matrix* B)
{
	return soma_modulo_matrix(A,B,1);
}

// Multiplica as matrizes A e B
Matrix* multiplica_matrix(Matrix* A, Matrix* B)
{
	int v;
	if (A->c != B->r)
		return NULL;

	Matrix* aux = cria_matrix(A->r,B->c);

	for (int i = 0; i < A->r; i++)
	{
		for (int j = 0; j < B->c; j++)
		{
			v = 0;

			for (int k = 0; k < A->c; k++)
				v = v + A->data[i][k] * B->data[k][j];

			aux->data[i][j] = v;
		}
	}

	return aux;
}



Matrix* clona(Matrix* A, float **vetor)
{
	for (int i = 0; i < A->r; i++)
		for (int j = 0; j < A->c; j++)
		{
			A->data[i][j] = vetor[i][j];
			printf("%.2f",vetor[i][j]);
		}

	return A;
}

int main()
{
	printf("comecou aqui\n\n");
	float v1[3][2] = {{1,2},{3,4},{5,6}};
	float v2[3][2] = {{6,5},{4,3},{2,1}};
	float v3[2][4] = {{7,9,11,13},{8,10,12,14}};
	printf("comecou\n\n");

	Matrix* M1 = cria_matrix(3,2);
	Matrix* M2 = cria_matrix(3,2);
	Matrix* M3 = cria_matrix(2,4);
	printf("criou\n\n");

	M1 = clona(M1,v1);
	M2 = clona(M2,v2);
	M3 = clona(M3,v3);
	printf("clonou\n\n");

	printf("Soma escalar:\n\n");
	imprime_matrix(soma_escalar(M1,2));
	printf("\n\n");
	printf("Subtrai escalar:\n\n");
	imprime_matrix(subtrai_escalar(M1,2));
	printf("\n\n");
	printf("Multiplica escalar:\n\n");
	imprime_matrix(multiplica_escalar(M1,2));
	printf("\n\n");

	printf("Soma matrizes:\n\n");
	imprime_matrix(soma_matrixes(M1,M2));
	printf("\n\n");
	printf("Subtrai matrizes:\n\n");
	imprime_matrix(subtrai_matrixes(M1,M2));
	printf("\n\n");
	printf("Multiplica matrizes:\n\n");
	imprime_matrix(multiplica_matrix(M1,M2));
	printf("\n\n");

	return 0;
}