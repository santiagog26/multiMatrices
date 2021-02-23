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
void sample_start(){
	gettimeofday(&start, NULL);
}

/* Punto de fin de medición de tiempo */
void sample_stop(){
	gettimeofday(&end, NULL);
}

/* Presentación de toma de tiempo */
void sample_end(){
    printf("%ld ms\n", ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)));
}

void initRandomMatriz(int random, int size, double matriz[][size]){
    int i, j;

	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			matriz[i][j] = rand() % random;
		}
	}

}

void multiMatriz(int size, double matrizA[][size], double matrizB[][size], double matrizC[][size]){
    int i, j, k, suma=0;
	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			for (k=0; k < size; k++){
				suma += matrizA[i][k]*matrizB[k][j];
			}
			matrizC[i][j]=suma;
			suma=0;
		}
	}
}

