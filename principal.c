/* Fecha: 11 - Feb 2021
 * Autor: Santiago Gutierrez Orjuela
 * Programa: principal.c, Multiplicación de matrices del mismo tamaño
 * Asignatura: Computación paralela y distribuida
 * Asunto: Multiplicación de matrices, con argumentos de entrada al ejecutable
 * 1 - Ingreso del tamaño por consola
 * 2 - Ingreso del valor de aleatoriedad por consola
 * */

#include "modulo.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

int main(int argc, char **argv){
    int SZ; /*Ingreso del tamaño del vector*/
    int R; /*Ingreso del valor de aleatoriedad*/
    SZ = (int) atof(argv[1]);
    R = (int) atof(argv[2]);

    time_t t;
    /* Inicializa random number generator */
    srand((unsigned) time(&t));

    double matrizA[SZ][SZ], matrizB[SZ][SZ], matrizC[SZ][SZ]; /*Declaro las matrices*/
    
    /* Se inicializan las matrices aleatoriamente*/
    initRandomMatriz(R, SZ, matrizA);
    initRandomMatriz(R, SZ, matrizB); 

    /* Se multiplican las matrices A y B, guardando el resultado en la matriz C*/
    sample_start();
    multiMatriz(SZ, matrizA, matrizB, matrizC);
    sample_stop();
    sample_end();

    return 0;
}