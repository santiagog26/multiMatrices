#ifndef MODULO_H_INCLUDED
#define MODULO_H_INCLUDED

/* Prototypes for the functions */
/* Funciones para calcular el tiempo */
extern void sample_start();
extern void sample_stop();
extern void sample_end();

int size, num_threads;
double **matrix1, **matrix2, **matrix3;
double ** allocate_matrix( int size );
void init_matrix( double **matrix, int size );
void print_matrix( double **matrix, int size );
void * worker( void *arg );
#endif