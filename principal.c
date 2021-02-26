/**
 * Matrix (N*N) multiplication with multiple threads.
 * author: Shuo Yang
 */
#include "modulo.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

int size, num_threads;
double **matrix1, **matrix2, **matrix3;

int main( int argc, char *argv[] )
{
  int i;
  pthread_t * threads;

  if (argc != 3) {
    printf("Expected <matrix size> <number of threads>\n");
    return -1;
  }

  size = atoi( argv[1] );
  num_threads = atoi( argv[2] );

  if ( size % num_threads != 0 ) {
    printf("size %d must be a multiple of num of threads %d\n",
	     size, num_threads );
    return -1;
  }

  threads = (pthread_t *) malloc( num_threads * sizeof(pthread_t) );

  matrix1 = allocate_matrix( size );
  matrix2 = allocate_matrix( size );
  matrix3 = allocate_matrix( size );
  
  init_matrix( matrix1, size );
  init_matrix( matrix2, size );

  if ( size <= 10 ) {
    printf( "Matrix 1:\n" );
    print_matrix( matrix1, size );
    printf( "Matrix 2:\n" );
    print_matrix( matrix2, size );
  }

  sample_start();
  for ( i = 0; i < num_threads; ++i ) {
    int *tid;
    tid = (int *) malloc( sizeof(int) );
    *tid = i;
    pthread_create( &threads[i], NULL, worker, (void *)tid );
  }

  for ( i = 0; i < num_threads; ++i ) {
    pthread_join( threads[i], NULL );
  }
  sample_stop();
  
  if ( size <= 10 ) {
    printf( "Matrix 3:\n" );
    print_matrix( matrix3, size );
  }

  sample_end();

  printf( "Number of threads: %d\n",
          num_threads);

  return 0;
}