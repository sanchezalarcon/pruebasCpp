/*
 * funciones.h
 *
 *  Created on: 25/3/2015
 *      Author: chrono
 */

#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <math.h>       /* pow */

#include "list.h"
#include "listPairDouble.h"

const double Error  = 0.000001;

// media
double media(list *l);

// desviacion
double desviacion(list *l, double media);

// regresion lineal
nodePairDouble* regresion(listPairDouble *listPD);

// correlacion
nodePairDouble* correlacion(listPairDouble *listPD);

// prediccion
double prediccion(double beta_0, double beta_1, double x_k);

// ecuacion de calculo del valor integral
double valorIntegral(double valX, double valW, double numSeg, double gradoLibertad);

// funcion que representa la distribucion t, y que se usa para integrar numericamente
double funcionFDistribucion(double valX, double gradoLibertad);

// funcion gamma
double gamma(double valX);

// ecuacion de calculo p del valor integral, para un intervalo x
double calculoPValorIntegral(double valX, double numSeg, double gradoLibertad);

// ecuacion de calculo de la inversa del valor integral
double inversaValorIntegral(double valP, double numSeg, double gradoLibertad);

// ecuacion para calcular la significancia de una correlacion
double significancia(listPairDouble *listPD);

// sigma usado en el calculo del Range70%
double rangeSigma(listPairDouble *listPD, double beta_0, double beta_1);

// Calculo de range
double Range70(listPairDouble *listPD, double x_k_estimacion);

// imprime una matriz
void printMatrix(double **matriz, int rows, int cols);

// encuentra la fila a usar de pivote
int rowPivot(double **matriz, int num_rows, int init_row, int search_col);

// intercambia dos filas de una matriz
void swapRows(double **matriz, int row_1, int row_2, int cols);

// modifica la matriz a su correspondiente de la eliminacion de gauss
void Gauss(double **matriz, int rows, int cols);

double valorProyecto(double beta_0, double beta_1, double beta_2, double beta_3, double w_k, double x_k, double y_k);

double rangeSigmaSimultaneo(list *lista_w, list *lista_x, list *lista_y, list *lista_z, double beta_0, double beta_1, double beta_2, double beta_3);

double Range70Simultaneo(list *lista_w, list *lista_x, list *lista_y, list *lista_z, double beta_0, double beta_1, double beta_2, double beta_3, double w_k, double x_k, double y_k);

#endif /* FUNCIONES_H_ */
