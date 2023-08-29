#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

void imprime_matrix(Matrix* M)
{
	for (int i = 0; i < M->r; i++)
	{
		for (int j = 0; j < M->c; j++)
			printf("%.2f ", M->data[i][j]);
		printf("\n");
	}
	printf("\n");
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

// Libera Matriz
Matrix* libera_matrix(Matrix* M)
{
	for (int i = 0; i < M->r; i++)
		free(M->data[i]);

	free(M->data);
	free(M);

	return NULL;
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
	float v;
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

Matrix* transposta(Matrix* M)
{
	Matrix* trans = cria_matrix(M->c, M->r);

	for (int i = 0; i < M->c; i++)
		for(int j = 0; j < M->r; j++)
			trans->data[i][j] = M->data[j][i];

	return trans;
}

float determinante(Matrix* M)
{
    float det = 1;
    int size = M->r;
    int i, j, k;

    for (i = 0; i < size; i++) {
        // Find the maximum value in the current column for partial pivoting
        int max_row = i;
        for (j = i + 1; j < size; j++) {
            if (abs(M->data[j][i]) > abs(M->data[max_row][i])) {
                max_row = j;
            }
        }

        // Swap rows if necessary for partial pivoting
        if (max_row != i) {
            for (k = i; k < size; k++) {
                float temp = M->data[i][k];
                M->data[i][k] = M->data[max_row][k];
                M->data[max_row][k] = temp;
            }
            det *= -1.0; // Changing rows changes the sign of the determinant
        }

        // Perform Gaussian elimination
        for (j = i + 1; j < size; j++) {
            float factor = M->data[j][i] / M->data[i][i];
            for (k = i; k < size; k++) {
                M->data[j][k] -= factor * M->data[i][k];
            }
        }

        det *= M->data[i][i]; // Multiply diagonal elements to find the determinant
    }

    return det;
}

float calcula_determinante(Matrix* M)
{
	Matrix* aux = cria_matrix(M->r,M->r);

	for (int i = 0; i < M->r; i++)
		for (int j = 0; j < M->r; j++)
			aux->data[i][j] = M->data[i][j];

	float d = determinante(aux);
	libera_matrix(aux);

	return d;
}

Matrix* cofator(Matrix* M, Matrix* temp, int p, int q)
{
	int i = 0;
	int j = 0;
	int size = M->r;

	for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            // Copying into temporary matrix only those element which are not in given row and column
            if (row != p && col != q) {
                temp->data[i][j++] = M->data[row][col];
 
                // Row is filled, so increase row index and reset col index
                if (j == size - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }

    return temp;
}


Matrix* adjunta(Matrix* M)
{
	int size = M->r;
	Matrix* adj = cria_matrix(size,size);

	if (size == 1)
	{
		adj->data[0][0] = 1;
		return adj;
	}

	int sign = 1;
	Matrix* temp = cria_matrix(size-1,size-1);

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			temp = cofator(M, temp, i, j);

			if ((i + j) % 2 == 0)
				sign = 1;
			else
				sign = -1;

			adj->data[i][j] = (sign) * (calcula_determinante(temp));
		}
	}

	libera_matrix(temp);
	Matrix* adjT = transposta(adj);
	libera_matrix(adj);
	return adjT;
}

Matrix* invertida(Matrix* M)
{
	float det = calcula_determinante(M);
	if (det == 0)
	{
		printf("Matriz não inversível! \n");
		return NULL;
	}

	Matrix* adj = adjunta(M);
	Matrix* inv = cria_matrix(M->r,M->r);

	for (int i = 0; i < M->r; i++)
		for (int j = 0; j < M->r; j++)
			inv->data[i][j] = adj->data[i][j]/det;

	libera_matrix(adj);
	return inv;
}