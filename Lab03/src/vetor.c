#include <stdio.h>
#include <stdlib.h>
#include "vetor.h"

Vetor* printa_elemento(Vetor *lista)
{
	if (lista == NULL)
	{
		printf("Lista vazia!!!");
		return lista;
	}

	if (lista->prox == NULL)
	{
		printf("%.4f", lista->valor);
		return lista;
	}

	printf("%.4f ", lista->valor);
	printa_elemento(lista->prox);
}

void printa_vetor(Vetor *lista)
{
	printf("[");
	printa_elemento(lista);
	printf("]");
}

Vetor* cria_cedula(Vetor *lista, double value)
{
	Vetor* aux = (Vetor*)malloc(sizeof(Vetor));
	aux->valor = value;
	aux->prox = NULL;
	return aux;
}

Vetor* add_elemento(Vetor *lista, double elemento)
{
	if (lista == NULL)
		return cria_cedula(lista, elemento);

	lista->prox = add_elemento(lista->prox, elemento);
	return lista;
}

Vetor* libera_vetor(Vetor *lista)
{
	if (lista == NULL)
		return lista;

	lista->prox = libera_vetor(lista->prox);
	free(lista);
	return NULL;
}