#ifndef MODULO_H_INCLUDED
#define MODULO_H_INCLUDED

/* Prototypes for the functions */
/* Funciones para calcular el tiempo */
extern void sample_start();
extern void sample_stop();
extern void sample_end();
/* Inicializador aleatorio de matrices */
void initRandomMatriz(int random, int size, double **matriz);
/* Multiplicacion de dos matrices y guardar resultado en otro */
void * multiMatriz(struct thread_args *argsm);
/* Estructura para guardar datos necesarios para la multiplicaión */
typedef struct thread_args;
/* Asignar dirección de memoria a las matrices */
double ** allocate_matrix(int size);
#endif