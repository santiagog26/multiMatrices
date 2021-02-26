/**
 * File: principal.c
 * Description: Matrix (N*N) multiplication with multiple threads and parallel programming
 * Author: Shuo Yang
 * Modified: Juan Bueno and Santiago Gutiérrez
 * Date: 15 - Feb - 2021
 */
#include "modulo.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

int main( int argc, char *argv[] )
{
  int i;
  pthread_t * threads;

  // Validación del número de argumentos ingresados
  if (argc != 3) {
    printf("Expected <matrix size> <number of threads>\n");
    return -1;
  }

  // Obtención de valores de los argumentos
  size = atoi( argv[1] );
  num_threads = atoi( argv[2] );
  
  // Validación de que el tamaño sea divisible por el número de hilos
  if ( size % num_threads != 0 ) {
    printf("Size %d must be a multiple of num of threads %d\n",
	     size, num_threads );
    return -1;
  }

  // Asignación de memoria para los hilos y matrices
  threads = (pthread_t *) malloc( num_threads * sizeof(pthread_t) );

  matrix1 = allocate_matrix( size );
  matrix2 = allocate_matrix( size );
  matrix3 = allocate_matrix( size );
  
  // Inicialización de matrices en 1
  init_matrix( matrix1, size );
  init_matrix( matrix2, size );

  // Impresión de matrices en el caso de que el tamaño sea menor o igual a 10
  if ( size <= 10 ) {
    printf( "Matrix 1:\n" );
    print_matrix( matrix1, size );
    printf( "Matrix 2:\n" );
    print_matrix( matrix2, size );
  }

  // Comienzo de conteo de tiempo
  sample_start();
  for ( i = 0; i < num_threads; ++i ) {
    int *tid;
    tid = (int *) malloc( sizeof(int) );
    *tid = i;
    // Creación del hilo con el worker de multiplicación de matrices
    pthread_create( &threads[i], NULL, worker, (void *)tid );
  }

  for ( i = 0; i < num_threads; ++i ) {
    // Inicio de los hilos
    pthread_join( threads[i], NULL );
  }
  // Stop del tiempo
  sample_stop();
  
  // Impresión de matrices en el caso de que el tamaño sea menor o igual a 10
  if ( size <= 10 ) {
    printf( "Matrix 3:\n" );
    print_matrix( matrix3, size );
  }

  // Impresión del tiempo que se gastó en la multiplicación y el número de hilos
  sample_end();

  printf( "Number of threads: %d\n", num_threads);

  return 0;
}