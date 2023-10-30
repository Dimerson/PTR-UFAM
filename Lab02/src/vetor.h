#ifndef VETOR_H
#define VETOR_H

typedef struct v
{
	double valor;
	struct v *prox;
} Vetor;

void printa_vetor(Vetor *lista);
Vetor* printa_elemento(Vetor *lista);
Vetor* cria_cedula(Vetor *lista);
Vetor* add_elemento(Vetor *lista, double elemento);
Vetor* libera_vetor(Vetor *lista);

#endif