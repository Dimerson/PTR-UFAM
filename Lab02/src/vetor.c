#include <stdio.h>
#include <stdlib.h>
#include "vetor.h"

Vetor* printa_elemento(Vetor *lista)
{
	if (lista == NULL)
	{
		print("Lista vazia!!!");
		return lista;
	}

	if (lista->prox == NULL)
	{
		print("%.5f", lista->valor);
		return lista;
	}

	print("%.5f ", lista->valor);
	printa_elemento(lista->prox);
}

void printa_vetor(Vetor *lista)
{
	print("[");
	printa_elemento(Lista);
	print("]");
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
	if (Lista == NULL)
		return cria_cedula(Lista, elemento);

	lista->prox = add_elemento(lista->prox);
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