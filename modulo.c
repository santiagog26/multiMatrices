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
	double exectime;
	exectime = (end.tv_sec - start.tv_sec) * 1000.0; // sec to ms
  	exectime += (end.tv_usec - start.tv_usec) / 1000.0; // us to ms
	printf("Time: %f ms\n", exectime);
}

/* Inicializador de matrices */
void init_matrix( double **matrix, int size )
{
  int i, j;

  for (i = 0; i < size; ++i) {
    for (j = 0; j < size; ++j) {
      matrix[ i ][ j ] = 1.0;
    }
  }
}

/* Imprime la matriz */ 
void print_matrix( double **matrix, int size )
{
  int i, j;

  for (i = 0; i < size; ++i) {
    for (j = 0; j < size-1; ++j) {
      printf( "%lf, ", matrix[ i ][ j ] );
    }
    printf( "%lf", matrix[ i ][ j ] );
    putchar( '\n' );
  }
}

/* Multiplicacion de dos matrices y guardar resultado en otro */
void * worker( void *arg )
{
  int i, j, k, tid, portion_size, row_start, row_end;
  double sum=0;
  
  tid = *(int *)(arg); // get the thread ID assigned sequentially.
  portion_size = size / num_threads;
  row_start = tid * portion_size;
  row_end = (tid+1) * portion_size;

  for (i = row_start; i < row_end; ++i) { // hold row index of 'matrix1'
    for (j = 0; j < size; ++j) { // hold column index of 'matrix2'
      sum = 0; // hold value of a cell
      /* one pass to sum the multiplications of corresponding cells
	 in the row vector and column vector. */
      for (k = 0; k < size; ++k) { 
        sum += matrix1[ i ][ k ] * matrix2[ k ][ j ];
      }
      matrix3[ i ][ j ] = sum;
    }
  }
  return NULL;
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