/* Fecha: 23 - Feb 2021
 * Autor: Santiago Gutierrez Orjuela y Juan Bueno
 * Basado en programa de: Shuo Yang
 * Programa: principal.c, Multiplicación de matrices del mismo tamaño con pthreads
 * Asignatura: Computación paralela y distribuida
 * Asunto: Multiplicación de matrices, con argumentos de entrada al ejecutable
 * 1 - Ingreso del tamaño de la matriz
 * 2 - El número de hilos
 * 3 - Ingreso del valor de aleatoriedad 
 * */

#include "modulo.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

struct thread_args *args1;

int main(int argc, char **argv)
{
    // Control de números de argumentos ingresados
    if (argc != 4)
    {
        fprintf(stderr, "Args expected <matrix size> <number of threads> <random value>\n");
        return -1;
    }

    int size, num_threads, R, i;
    double **matrix1, **matrix2, **matrix3;
    size = atoi(argv[1]);
    num_threads = atoi(argv[2]);
    R = (int)atof(argv[3]);
    pthread_t * threads;

    // Control de que el tamaño sea divisible por el número de hilos
    if (size % num_threads != 0)
    {
        fprintf(stderr, "size %d must be a multiple of num of threads %d\n",
                size, num_threads);
        return -1;
    }

    time_t t;
    /* Inicializa random number generator */
    srand((unsigned)time(&t));

    threads = (pthread_t *)malloc(num_threads * sizeof(pthread_t));

    matrix1 = allocate_matrix(size);
    matrix2 = allocate_matrix(size);
    matrix3 = allocate_matrix(size);

    /* Se inicializan las matrices aleatoriamente*/
    initRandomMatriz(R, size, matrix1);
    initRandomMatriz(R, size, matrix2);

    // Se muestra si la matriz tiene un tamaño menor a 10
    if (size <= 10)
    {
        printf("Matrix 1:\n");
        print_matrix(matrix1, size);
        printf("Matrix 2:\n");
        print_matrix(matrix2, size);
    }

    args1 = malloc (sizeof (struct thread_args));
    args1->matrix1 = matrix1;
    args1->matrix2 = matrix2;
    args1->matrix3 = matrix3;
    args1->size = size;
    args1->num_threads = num_threads;

    /* Se multiplican las matrices A y B, guardando el resultado en la matriz C*/
    sample_start();
    for (i = 0; i < num_threads; ++i)
    {
        int *tid;
        tid = (int *)malloc(sizeof(int));
        *tid = i;
        args1->tid = *tid;
        pthread_create(&threads[i], NULL, multiMatriz, (void *)args1);
    }

    for (i = 0; i < num_threads; ++i)
    {
        pthread_join(threads[i], NULL);
    }
    sample_stop();
    
    // Se muestra si la matriz tiene un tamaño menor a 10
    if ( size <= 10 ) {
        printf( "Matrix 3:\n" );
        print_matrix( matrix3, size );
    }

    printf( "Number of threads: %d\n", num_threads);
    sample_end();

    return 0;
}