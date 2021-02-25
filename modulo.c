/* Fecha: 11 - Feb 2021
 * Autor: Santiago Gutierrez Orjuela
 * Asignatura: Computación paralela y distribuida
 * Asunto: Programa compilación por separado Modulo de inicialización aleatoria de matrices y multiplicadas
 * */

#include "modulo.h"
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

struct timeval start, end;

/* Punto de inicio de medición de tiempo */
void sample_start()
{
	gettimeofday(&start, NULL);
}

/* Punto de fin de medición de tiempo */
void sample_stop()
{
	gettimeofday(&end, NULL);
}

/* Presentación de toma de tiempo */
void sample_end()
{
	printf("%ld ms\n", ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)));
}

/* Inicializador aleatorio de matrices */
void initRandomMatriz(int random, int size, double **matriz)
{
	int i, j;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			matriz[i][j] = rand() % random;
		}
	}
}

/* Estructura para guardar datos necesarios para la multiplicaión */
typedef struct thread_args{
	double **matrix1;
    double **matrix2;
    double **matrix3;
    int size, num_threads;
    int *tid;
} args;

/* Multiplicacion de dos matrices y guardar resultado en otro */
void * multiMatriz(struct thread_args *argsm)
{
	int i, j, k, tid, size, num_threads, portion_size, row_start, row_end;
	double sum;
	double **matrix1, **matrix2, **matrix3;

	tid = *(int *)(argsm->tid);
	size = argsm->size;
	num_threads = argsm->num_threads;
	matrix1 = argsm->matrix1;
    matrix2 = argsm->matrix2;
    matrix3 = argsm->matrix3;
	portion_size = size / num_threads;
	row_start = tid * portion_size;
	row_end = (tid + 1) * portion_size;

	for (i = row_start; i < row_end; ++i)
	{ // hold row index of 'matrix1'
		for (j = 0; j < size; ++j)
		{			 // hold column index of 'matrix2'
			sum = 0; // hold value of a cell
			/* one pass to sum the multiplications of corresponding cells
	 		in the row vector and column vector. */
			for (k = 0; k < size; ++k)
			{
				sum += matrix1[i][k] * matrix2[k][j];
			}
			matrix3[i][j] = sum;
		}
	}
}

/* Asignar dirección de memoria a las matrices */
double **allocate_matrix(int size){
	/* Allocate 'size' * 'size' doubles contiguously. */
	double *vals = (double *)malloc(size * size * sizeof(double));

	/* Allocate array of double* with size 'size' */
	double **ptrs = (double **)malloc(size * sizeof(double *));

	int i;
	for (i = 0; i < size; ++i){
		ptrs[i] = &vals[i * size];
	}

	return ptrs;
}