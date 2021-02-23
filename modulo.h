#ifndef MODULO_H_INCLUDED
#define MODULO_H_INCLUDED

extern void sample_start();
extern void sample_stop();
extern void sample_end();
/* Prototypes for the functions */
/* Inicializador aleatorio de matrices */
void initRandomMatriz(int random, int size, double matriz[][size]);
/* Multiplicacion de dos matrices y guardar resultado en otro */
void multiMatriz(int size, double matrizA[][size], double matrizB[][size], double matrizC[][size]);
#endif