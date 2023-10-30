#ifndef MATRIX_H
#define MATRIX_H

typedef struct M
{
	int r, c;
	float **data;
} Matrix;

void imprime_matrix(Matrix* M);
Matrix* cria_matrix(int rows, int cols);									// Aloca memória e cria a Matriz
Matrix* libera_matrix(Matrix* M);											// Libera Matriz da memória (free)
Matrix* recebe_valores(Matrix* M);											// Função para o usuário digitar os valores da Matriz
Matrix* opera_escalar(Matrix* M, float escalar, int flag);					// Soma, subtrai ou multiplica a Matriz A por um escalar
Matrix* soma_escalar(Matrix* M, float escalar);
Matrix* subtrai_escalar(Matrix* M, float escalar);
Matrix* multiplica_escalar(Matrix* M, float escalar);
Matrix* soma_modulo_matrix(Matrix* A, Matrix* B, int flag);					// Soma ou subtrai as matrizes A e B
Matrix* soma_matrixes(Matrix* A, Matrix* B);
Matrix* subtrai_matrixes(Matrix* A, Matrix* B);
Matrix* multiplica_matrix(Matrix* A, Matrix* B);							// Multiplica as Matrizes A e B
Matrix* transposta(Matrix* M);												// Transpõe a Matriz
float determinante(Matrix* M);												// Calcula o determinante da Matriz (método de Gauss)
float calcula_determinante(Matrix* M);										// Chama a função determinante
Matrix* cofator(Matrix* M, Matrix* temp, int p, int q);						// Calcula a Matriz dos cofatores
Matrix* adjunta(Matrix* M);													// Retorna a Matriz adjunta
Matrix* invertida(Matrix* M);												// Retorna a Matriz Inversa
Matrix* copia_matrix(Matrix* M, int rows, int cols, float Matriz[][cols]);	// Copia os valores de uma Matriz estática em uma dinâmica


#endif