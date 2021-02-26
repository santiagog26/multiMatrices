/**
 * File: modulo.c
 * Description: Declarations for functions of modulo.c
 * Author: Shuo Yang
 * Modified: Juan Bueno and Santiago Gutiérrez
 * Date: 15 - Feb - 2021
 */

#ifndef MODULO_H_INCLUDED
#define MODULO_H_INCLUDED

/* Prototypes for the functions */
/* Funciones para calcular el tiempo */
extern void sample_start();
extern void sample_stop();
extern void sample_end();
/* Se declaran las variables globales necesitadas en worker */
int size, num_threads;
double **matrix1, **matrix2, **matrix3;
/* Función asignar dirección de memoria a las matrices */
double ** allocate_matrix( int size );
/* Inicializador de matrices */
void init_matrix( double **matrix, int size );
/* Impresión de matrices */
void print_matrix( double **matrix, int size );
/* Multiplicacion de dos matrices y guardar resultado en otro */
void * worker( void *arg );
#endif