#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <math.h>
#include "vetor.h"
#include "matrix.h"
#include "dstring.h"
#include "integral.h"
#include "modelo.h"

typedef struct
{
    float t;
} ThreadArgs;

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


pthread_mutex_t lock;
Matrix *u, *estado, *xt, *yt, *yf, *ym, *i, *auxy;
volatile sig_atomic_t running = 1;
Vetor *vetor_seno, *vetor_cosseno, *vetor_angulo;
const float D = 0.6;

void *tarefa1(void *arg) {
	ThreadArgs *args = (ThreadArgs *)arg;
	Integral *integral_angulo;
    while(running) {
    	printf("%.6f\n", args->t);

    	
        pthread_mutex_lock(&lock);
        integral_angulo = cria_integral(u_k, args->t, args->t+0.03, 100);
        u->data[0][1] = calcula_integral(integral_angulo); // Operação da thread A na variável compartilhada
        vetor_angulo = add_elemento(vetor_angulo,u->data[0][1]);
        args->t = args->t + 0.03;
        //printf("Thread A: %d\n", sharedVariable);
        pthread_mutex_unlock(&lock);
        integral_angulo = destroy_integral(integral_angulo);
        printf("Seno: %.6f, Cosseno: %.6f, Angulo: %.6f\n", yf->data[0][0], yf->data[1][0], yf->data[2][0]);
        vetor_seno = add_elemento(vetor_seno, yf->data[0][0]);
        vetor_cosseno = add_elemento(vetor_cosseno, yf->data[1][0]);
        vetor_angulo = add_elemento(vetor_angulo, yf->data[2][0]);
        usleep(30000); // Aguarda 30ms
        args->t = args->t + 0.03;
    }
    return NULL;
}

void *tarefa2(void *arg) {
	ThreadArgs *args = (ThreadArgs *)arg;
	Integral *integral_seno, *integral_cosseno;
	Matrix *auxsoma, *auxprod;
    while(running) {
    	printf("Entrou thread B: %.2f\n", args->t);

        pthread_mutex_lock(&lock);
        integral_seno = cria_integral(seno, args->t, args->t + 0.05, 100);
		integral_cosseno = cria_integral(coss, args->t, args->t + 0.05, 100);
		estado->data[0][0] = calcula_integral(integral_seno);
		estado->data[1][0] = calcula_integral(integral_cosseno);
		xt = multiplica_matrix(estado,u);
		auxy->data[0][0] = 0.5*D*coss(args->t);
		auxy->data[1][1] = 0.5*D*seno(args->t);
		auxprod = multiplica_matrix(auxy,xt);
		auxsoma = soma_matrixes(xt,auxprod);
		yf = libera_matrix(yf);
		yf = auxsoma;
        //printf("Thread B: %d\n", sharedVariable);
        vetor_seno = add_elemento(vetor_seno,yt->data[0][0]);
		vetor_cosseno = add_elemento(vetor_cosseno,yt->data[1][0]);
        pthread_mutex_unlock(&lock);
        auxprod = libera_matrix(auxprod);
        integral_seno = destroy_integral(integral_seno);
        integral_cosseno = destroy_integral(integral_cosseno);

        args->t = args->t + 0.05;
        usleep(50000); // Aguarda 50ms
    }
    return NULL;
}

void sigHandler(int signo) {
    if (signo == SIGALRM) {
        running = 0;
    }
}

int main() {
	u = cria_matrix(2,1);
	estado = cria_matrix(3,2);
	xt = cria_matrix(3,1);
	yt = cria_matrix(3,1);
	yf = cria_matrix(3,1);
	auxy = cria_matrix(3,3);
	i = cria_matrix(3,3);

	vetor_seno = NULL;
	vetor_cosseno = NULL;
	vetor_angulo = NULL;

	float V1[2][1] = {{1},{0}};
	float V2[3][2] = {{0,0}, {0,0}, {0,1}};
	float V3[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
	float V4[3][1] = {{0},{0},{0}};

	u = copia_matrix(u, 2, 1, V1);
	estado = copia_matrix(estado, 3, 2, V2);
	i = copia_matrix(i, 3, 3, V3);
	xt = copia_matrix(xt, 1, 1, V4);
	yt = copia_matrix(yt, 1, 1, V4);
	yf = copia_matrix(yf, 2, 1, V4);
	auxy = copia_matrix(auxy, 2, 1, V4);


	ThreadArgs *argt1 = (ThreadArgs *)malloc(sizeof(ThreadArgs));
	argt1->t = 0;

	ThreadArgs *argt2 = (ThreadArgs *)malloc(sizeof(ThreadArgs));
	argt2->t = 0;

    pthread_t thread_idA, thread_idB;

    pthread_mutex_init(&lock, NULL);

    signal(SIGALRM, sigHandler);
    alarm(20); // Configura um alarme para 20 segundos

    if (pthread_create(&thread_idA, NULL, tarefa1, (void *)argt1) != 0)
    {
    	fprintf(stderr, "Erro ao criar a thread 1.\n");
    	return 1;
    }

    if (pthread_create(&thread_idB, NULL, tarefa2, (void *)argt2) != 0)
    {
    	fprintf(stderr, "Erro ao criar a thread 2.\n");
    	return 1;
    }

    pthread_join(thread_idA, NULL);
    pthread_join(thread_idB, NULL);

    pthread_mutex_destroy(&lock);

    u = libera_matrix(u);
    estado = libera_matrix(estado);
    xt = libera_matrix(xt);
    yt = libera_matrix(yt);
    yf = libera_matrix(yf);
    i = libera_matrix(i);
    auxy = libera_matrix(auxy);


    printa_vetor(vetor_seno);
    printf("\n\n");
    printa_vetor(vetor_cosseno);
    printf("\n\n");
    printa_vetor(vetor_angulo);
    printf("\n\n");

    FILE *arquivo;
    arquivo = fopen("files/saida.txt", "w");

    escrever_saida(arquivo,vetor_seno);
    fprintf(arquivo,"\n\n");
    escrever_saida(arquivo,vetor_cosseno);
    fprintf(arquivo,"\n\n");
    escrever_saida(arquivo,vetor_angulo);
    fprintf(arquivo,"\n\n");

    vetor_seno = libera_vetor(vetor_seno);
    vetor_cosseno = libera_vetor(vetor_cosseno);
    vetor_angulo = libera_vetor(vetor_angulo);

    return 0;
}
