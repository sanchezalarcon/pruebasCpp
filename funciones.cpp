/*
 * funciones.cpp
 *
 *  Created on: 25/3/2015
 *      Author: chrono
 */

#include "funciones.h"

#include <stdio.h>
#include <stdlib.h>     /* abs */

const double PI = 3.141592653589793;

// media
double media(list *lista_reales){

   int cantidad_elementos = cantElemen(lista_reales);
   double media;

   if ( cantidad_elementos > 0 ){

      double sumatoria = 0;

      for (int i=0; i<cantidad_elementos; i++){
         node *tmp = getNodeList(lista_reales,i);
         sumatoria += getNodeVal(tmp);
      } // for

      double dividendo = static_cast<double>(cantidad_elementos);
      media = sumatoria / dividendo;

      return media;
   }else{
      return -9999;
   } // if

} // media

// desviacion
double desviacion(list *lista_reales, double media){

   int cantidad_elementos = cantElemen(lista_reales);

   if( cantidad_elementos > 1 ){

      double sumatoria_dev = 0;

      for (int i=0; i<cantidad_elementos; i++){
         node *tmp      = getNodeList(lista_reales,i);
         sumatoria_dev += pow(getNodeVal(tmp) - media, 2);
      } // for

      double dividendo_dev = static_cast<double>(cantidad_elementos-1);
      double pre_calculo = sumatoria_dev / dividendo_dev;
      double desviacion = sqrt(pre_calculo);

      return desviacion;

   }else{
      return -9999;
   } // if

} // desviacion

// regresion
nodePairDouble* regresion(listPairDouble *listPD){

   int cantidad_elementos = cantElemen(listPD);

   double  sumXY   = 0;
   double  sumPowX = 0;
   list   *listOfXs     = newList();
   list   *listOfYs     = newList();

   for (int i=0; i<cantidad_elementos; i++){

      nodePairDouble *tmp = getNodeList(listPD,i);

      // agrego a una lista simple los elementos de la lista doble
      // para calcular el promedio de dichas listas (x_avg, y_avg)
      addList(listOfXs, getNodeVal_1(tmp));
      addList(listOfYs, getNodeVal_2(tmp));

      // calculo la potencia de X, la acumulo para la sumatoria del dividendo
      // y la agrego a una lista simple para calcular el promedio x_avg^2
      double powX = pow(getNodeVal_1(tmp), 2);
      sumPowX += powX;

      sumXY += getNodeVal_1(tmp) * getNodeVal_2(tmp);
   } // for

   double mediaX = media(listOfXs);
   double mediaY = media(listOfYs);

   double divisor   = sumXY - cantidad_elementos * mediaX * mediaY;
   double dividendo = sumPowX - (cantidad_elementos * pow(mediaX, 2));

   double beta_1 = divisor / dividendo;
   double beta_0 = mediaY - beta_1 * mediaX;

   nodePairDouble *resultado = newNodePairDouble(beta_0, beta_1);

   return resultado;

} // regresion

// correlacion
nodePairDouble* correlacion(listPairDouble *listPD){

   int cantidad_elementos = cantElemen(listPD);

   double sumXY = 0;
   double sumX  = 0;
   double sumY  = 0;
   double sumPowX  = 0;
   double sumPowY  = 0;

   for (int i=0; i<cantidad_elementos; i++){

      nodePairDouble *tmp = getNodeList(listPD,i);

      sumXY += getNodeVal_1(tmp) * getNodeVal_2(tmp);
      sumX  += getNodeVal_1(tmp);
      sumY  += getNodeVal_2(tmp);
      sumPowX  += pow(getNodeVal_1(tmp), 2);
      sumPowY  += pow(getNodeVal_2(tmp), 2);
   } // for

   double divisor = cantidad_elementos * sumXY - sumX * sumY;

   double preCalc_left  = cantidad_elementos * sumPowX - pow(sumX, 2);
   double preCalc_right = cantidad_elementos * sumPowY - pow(sumY, 2);

   double dividendo = sqrt( preCalc_left * preCalc_right );

   double r_xy = divisor / dividendo;
   double rPow = pow(r_xy, 2);

   nodePairDouble *resultado = newNodePairDouble(r_xy, rPow);

   return resultado;

} // correlacion

// prediccion
double prediccion(double beta_0, double beta_1, double x_k){

   return ( beta_0 + beta_1 * x_k);

} // prediccion

// ecuacion de calculo del valor integral
double valorIntegral(double valX, double valW, double numSeg, double gradoLibertad){

   double sumatoria_1 = 0;
   for (int i = 1; i <= numSeg - 1; i = i + 2){
      sumatoria_1 += 4 * funcionFDistribucion(i * valW, gradoLibertad);
   } // for

   double sumatoria_2 = 0;
   for (int i = 2; i <= numSeg - 2; i = i + 2){
      sumatoria_2 += 2 * funcionFDistribucion(i * valW, gradoLibertad);
   } // for

   double F_0 = funcionFDistribucion(0, gradoLibertad);
   double F_X = funcionFDistribucion(valX, gradoLibertad);

   return (valW / 3) * (F_0 + sumatoria_1 + sumatoria_2 + F_X);

} // valorIntegral

// funcion que representa la distribucion t, y que se usa para integrar numericamente
double funcionFDistribucion(double valX, double gradoLibertad){

   // f = ( calc1 / calc 2 ) * calc 3

   double calc1 = gamma( (gradoLibertad + 1) / 2);
   double calc2 = pow((gradoLibertad * PI), 0.5) * gamma(gradoLibertad / 2);
   double calc3 = pow( 1 + (pow(valX, 2) / gradoLibertad), -( gradoLibertad + 1) / 2 );

   return ( calc1 / calc2 ) * calc3;

} // funcionFDistribucion

// funcion gamma
double gamma(double valX){

   if (valX == 1){
      return 1;
   } else if (valX < 1){ // valX == 0.5 o valX < 1
      return sqrt(PI);
   } else {
      return ( valX - 1 ) * gamma( valX - 1 );
   } // if

} // gamma

// ecuacion de calculo p del valor integral, para un intervalo x
double calculoPValorIntegral(double valX, double numSeg, double gradoLibertad){

   double tmp_numseg = numSeg;

   // defino valW
   double valW = valX / tmp_numseg;

   double p1 = valorIntegral(valX, valW, tmp_numseg, gradoLibertad);
   double p2 = valorIntegral(valX, valX / (tmp_numseg * 2), tmp_numseg * 2, gradoLibertad);

   while ( (p1 - p2) > Error ){
      tmp_numseg = tmp_numseg * 2;

      valW = valX / tmp_numseg;

      p1 = valorIntegral(valX, valW, tmp_numseg, gradoLibertad);
      p2 = valorIntegral(valX, valX / (tmp_numseg * 2), tmp_numseg * 2, gradoLibertad);

   } // while

   return p2;

} // calculoPValorIntegral

// ecuacion de calculo de la inversa del valor integral
double inversaValorIntegral(double valP, double numSeg, double gradoLibertad){

   if (valP == 0){
      return 0;
   } // if

   double d = 0.5;

   double x_test = 1.0;
   double p_test = calculoPValorIntegral(x_test, numSeg, gradoLibertad);

   double dif_1 = valP - p_test;

   // segundo calculo

   if(p_test < valP){    // es muy bajo
      x_test += d;       // sumo d
   }else{                // es muy alto
      x_test -= d;       // resto d
   } // if

   p_test = calculoPValorIntegral(x_test, numSeg, gradoLibertad);
   double dif_2 = valP - p_test;

   while ( pow(dif_2,2) > pow(Error,2) ){

      if(p_test < valP){  // es muy bajo

         if(dif_1 * dif_2 < 0){ // cambian de signo
            d = d / 2;
         } // if

         x_test += d;       // sumo d
      }else{                // es muy alto

         if(dif_1 * dif_2 < 0){ // cambian de signo
            d = d / 2;
         } // if

         x_test -= d;       // resto d
      } // if

      dif_1 = dif_2;

      p_test = calculoPValorIntegral(x_test, numSeg, gradoLibertad);
      dif_2 = valP - p_test;

   } // while

   return x_test;

} // inversaValorIntegral

// ecuacion para calcular la significancia de una correlacion
double significancia(listPairDouble *listPD){

   nodePairDouble *resultado = correlacion(listPD);
   double r_xy  = getNodeVal_1(resultado);
   double r_pow = getNodeVal_2(resultado);
   double n     = static_cast<double>(cantElemen(listPD));

   double x = ( fabs(r_xy) * sqrt(n-2) ) / sqrt(1 - r_pow);

   double p = calculoPValorIntegral(x, n, n-2);

   double area = 1 - (2 * p);

   //cout << "r_xy: " << r_xy << endl;
   //cout << "r_pow: " << r_pow << endl;
   //cout <<scientific<< "x: " << x << endl;
   //cout <<scientific<< "p: " << p << endl;
   //cout <<scientific<< "area: " << area << endl;

   return area;

} // significancia

// sigma usado en el calculo del Range70%
double rangeSigma(listPairDouble *listPD, double beta_0, double beta_1){

   double n = cantElemen(listPD);

   double sumatoria = 0;

   for (int i=0; i<n; i++){

      nodePairDouble *tmp = getNodeList(listPD,i);

      double x_i = getNodeVal_1(tmp);
      double y_i = getNodeVal_2(tmp);

      sumatoria += pow(y_i - beta_0 - (beta_1 * x_i), 2);
   } // for

   double sigma = sqrt( (1/(n-2)) * sumatoria);

   return sigma;

} // rangeSigma

// Calculo de range
double Range70(listPairDouble *listPD, double x_k_estimacion){

   nodePairDouble *val_regresion = regresion(listPD);

   double beta_0 = getNodeVal_1(val_regresion);
   double beta_1 = getNodeVal_2(val_regresion);
   double n      = cantElemen(listPD);

   // calcular x_Avg
   double sumX = 0;
   for (int i=0; i<n; i++){
      nodePairDouble *tmp = getNodeList(listPD,i);
      sumX += getNodeVal_1(tmp);
   } // for
   double x_avg = sumX / n;

   double t_p_dof = inversaValorIntegral(0.35, n, n-2);
   double sigma   = rangeSigma(listPD, beta_0, beta_1);

   // calcular sumatoria
   double sumatoria = 0;
   for (int i=0; i<n; i++){
      nodePairDouble *tmp = getNodeList(listPD,i);
      sumatoria += pow(getNodeVal_1(tmp) - x_avg, 2);
   } // for

   double operando3 = sqrt(1 + (1/n) + ( pow(x_k_estimacion - x_avg, 2) / sumatoria) );

   double range = t_p_dof * sigma * operando3;

   return range;

} // Rage70

void printMatrix(double **matriz, int rows, int cols){

   for(int i=0; i<rows; i++){
      for(int j=0; j<cols; j++){
         cout << matriz[i][j] << " ";
      }
      cout << endl;
   }
   cout << endl;

} // Gauss

int rowPivot(double **matriz, int num_rows, int init_row, int search_col){

   // buscar a partir de init_row de forma creciente hasta < num_rows

   int pivot_val = matriz[init_row][search_col];
   int row_pivot = init_row;

   for(int i=init_row+1; i<num_rows; i++){
      if(fabs(matriz[i][search_col]) >= fabs(pivot_val)){
         pivot_val = matriz[i][search_col];
         row_pivot = i;
      } // if
   } // for

   return row_pivot;

} // Gauss

void swapRows(double **matriz, int row_1, int row_2, int cols){

   double tmp_j = 0;

   for(int j=0; j<cols; j++){
      tmp_j = matriz[row_1][j];
      matriz[row_1][j] = matriz[row_2][j];
      matriz[row_2][j] = tmp_j;
   } // for

} // Gauss

void Gauss(double **matriz, int rows, int cols){

   int max_index = 0;
   double multiplicador = 0;

   for(int k = 0; k < min(rows, cols); k++){
      max_index = rowPivot(matriz,rows,k,k);
      swapRows(matriz, k, max_index, cols);

      for(int i=k+1; i < rows; i++){
         for(int j=k+1; j < cols; j++){
            matriz[i][j] = matriz[i][j] - matriz[k][j] * ( matriz[i][k] / matriz[k][k] );
         } // for

         matriz[i][k] = 0;
      } // for

      multiplicador = matriz[k][k];
      for(int j=k; j < cols; j++){
         matriz[k][j] = matriz[k][j] / multiplicador;
      } // for

      //printMatrix(matriz, rows, cols);

   } // for

} // Gauss

// prediccion
double valorProyecto(double beta_0, double beta_1, double beta_2, double beta_3, double w_k, double x_k, double y_k){

   return ( beta_0 + beta_1 * w_k + beta_2 * x_k + beta_3 * y_k);

} // valorProyecto

// sigma usado en el calculo del Range70%
double rangeSigmaSimultaneo(list *lista_w, list *lista_x, list *lista_y, list *lista_z, double beta_0, double beta_1, double beta_2, double beta_3){

   double n = cantElemen(lista_w);

   double sumatoria = 0;

   for (int i=0; i<n; i++){

      node *w_tmp = getNodeList(lista_w,i);
      node *x_tmp = getNodeList(lista_x,i);
      node *y_tmp = getNodeList(lista_y,i);
      node *z_tmp = getNodeList(lista_z,i);

      double w_i = getNodeVal(w_tmp);
      double x_i = getNodeVal(x_tmp);
      double y_i = getNodeVal(y_tmp);
      double z_i = getNodeVal(z_tmp);

      sumatoria += pow(z_i - beta_0 - (beta_1 * w_i) - (beta_2 * x_i) - (beta_3 * y_i), 2);
   } // for

   double sigma = sqrt( (1/(n-4)) * sumatoria);

   return sigma;

} // rangeSigmaSimultaneo

// Calculo de range
double Range70Simultaneo(list *lista_w, list *lista_x, list *lista_y, list *lista_z, double beta_0, double beta_1, double beta_2, double beta_3, double w_k, double x_k, double y_k){

   double n = cantElemen(lista_w);

   double w_avg = media(lista_w);
   double x_avg = media(lista_x);
   double y_avg = media(lista_y);

   double t_p_dof = inversaValorIntegral(0.35, n, n-4);
   double sigma   = rangeSigmaSimultaneo(lista_w, lista_x, lista_y, lista_z, beta_0, beta_1, beta_2, beta_3);

   // calcular simultaneamente las tres sumatorias
   double sumatoria_w = 0;
   double sumatoria_x = 0;
   double sumatoria_y = 0;
   for (int i=0; i<n; i++){
      node *w_tmp = getNodeList(lista_w,i);
      node *x_tmp = getNodeList(lista_x,i);
      node *y_tmp = getNodeList(lista_y,i);

      double w_i = getNodeVal(w_tmp);
      double x_i = getNodeVal(x_tmp);
      double y_i = getNodeVal(y_tmp);

      sumatoria_w += pow(w_i - w_avg, 2);
      sumatoria_x += pow(x_i - x_avg, 2);
      sumatoria_y += pow(y_i - y_avg, 2);
   } // for

   double operando_w = pow(w_k - w_avg, 2) / sumatoria_w;
   double operando_x = pow(x_k - x_avg, 2) / sumatoria_x;
   double operando_y = pow(y_k - y_avg, 2) / sumatoria_y;

   double operando3 = sqrt(1 + (1/n) + operando_w + operando_x + operando_y );

   double range = t_p_dof * sigma * operando3;

   return range;

} // Range70Simultaneo
