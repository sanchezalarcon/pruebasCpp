#include "funciones.h"

#include <string>
#include <stdlib.h>     /* atof */
#include <iostream>
using namespace std;

int main() {

   list *lista_w = newList();
   list *lista_x = newList();
   list *lista_y = newList();
   list *lista_z = newList();

   double Wk = 0;
   double Xk = 0;
   double Yk = 0;

   double sumW = 0;
   double sumX = 0;
   double sumY = 0;
   double sumZ = 0;

   double sumPowW = 0;
   double sumPowX = 0;
   double sumPowY = 0;

   double sumWX = 0;
   double sumWY = 0;
   double sumWZ = 0;
   double sumXY = 0;
   double sumXZ = 0;
   double sumYZ = 0;

   string entrada_w = "";
   string entrada_x = "";
   string entrada_y = "";
   string entrada_z = "";

   // leer las cuatro columnas de datos
   cout << "Por favor, ingrese las filas, cada valor separado por espacios" << endl;
   cout << " y cada fila separada por 'enters'." << endl;
   cout << "Para finalizar ingrese: fin" << endl;

   cin >> entrada_w;
   if ( entrada_w.compare("fin") ){
      cin >> entrada_x;
      cin >> entrada_y;
      cin >> entrada_z;
   } // if

   while ( entrada_w.compare("fin") ){
      // W
      double valW = atof(entrada_w.c_str());
      addList(lista_w, valW);
      sumW += valW;
      sumPowW += pow(valW,2);

      // X
      double valX = atof(entrada_x.c_str());
      addList(lista_x, valX);
      sumX += valX;
      sumPowX += pow(valX,2);

      // Y
      double valY = atof(entrada_y.c_str());
      addList(lista_y, valY);
      sumY += valY;
      sumPowY += pow(valY,2);

      // Z
      double valZ = atof(entrada_z.c_str());
      addList(lista_z, valZ);
      sumZ += valZ;

      // calculo los coeficientes de la matriz
      sumWX += valW * valX;
      sumWY += valW * valY;
      sumWZ += valW * valZ;
      sumXY += valX * valY;
      sumXZ += valX * valZ;
      sumYZ += valY * valZ;

      cin >> entrada_w;
      if ( entrada_w.compare("fin") ){
         cin >> entrada_x;
         cin >> entrada_y;
         cin >> entrada_z;
      } // if

   } // while

   // todas las columnas tienen que tener mas de cuatro elementos
   if( cantElemen(lista_w) > 4 ){

      // leer las tres estimaciones K
      cout << "Ingrese las estimaciones Wk Xk Yk separadas por un espacio." << endl;
      cin >> entrada_w;
      cin >> entrada_x;
      cin >> entrada_y;
      Wk = atof(entrada_w.c_str());
      Xk = atof(entrada_x.c_str());
      Yk = atof(entrada_y.c_str());

      // creo la matriz de datos
      int rows = 4;
      int cols = 5;
      double **matriz = new double*[rows];
      for (int i = 0; i < rows; ++i){
         matriz[i] = new double[cols];
      } // for

      matriz[0][0] = cantElemen(lista_w);
      matriz[0][1] = sumW;
      matriz[0][2] = sumX;
      matriz[0][3] = sumY;
      matriz[0][4] = sumZ;

      matriz[1][0] = sumW;
      matriz[1][1] = sumPowW;
      matriz[1][2] = sumWX;
      matriz[1][3] = sumWY;
      matriz[1][4] = sumWZ;

      matriz[2][0] = sumX;
      matriz[2][1] = sumWX;
      matriz[2][2] = sumPowX;
      matriz[2][3] = sumXY;
      matriz[2][4] = sumXZ;

      matriz[3][0] = sumY;
      matriz[3][1] = sumWY;
      matriz[3][2] = sumXY;
      matriz[3][3] = sumPowY;
      matriz[3][4] = sumYZ;

      //printMatrix(matriz, rows, cols);

      // despejar los beta de la matriz usando gauss
      Gauss(matriz, rows, cols);

      //printMatrix(matriz, rows, cols);

      double beta_3 = matriz[3][4] / matriz[3][3];
      double beta_2 = (matriz[2][4] - matriz[2][3]*beta_3) / matriz[2][2];
      double beta_1 = (matriz[1][4] - matriz[1][3]*beta_3 - matriz[1][2]*beta_2) / matriz[1][1];
      double beta_0 = (matriz[0][4] - matriz[0][3]*beta_3 - matriz[0][2]*beta_2 - matriz[0][1]*beta_1) / matriz[0][0];

      cout << "beta_0: " << beta_0 << endl;
      cout << "beta_1: " << beta_1 << endl;
      cout << "beta_2: " << beta_2 << endl;
      cout << "beta_3: " << beta_3 << endl;

      // calcular zk con los beta y los k restantes
      double Zk = valorProyecto(beta_0, beta_1, beta_2, beta_3, Wk, Xk, Yk);
      cout << "La estimacion final es: " << Zk << " horas." << endl;

      // calcular el range usando las columnas, los betas, y el zk
      double range = Range70Simultaneo(lista_w, lista_x, lista_y, lista_z, beta_0, beta_1, beta_2, beta_3, Wk, Xk, Yk);
      cout << "El rango de estimacion es: " << range << endl;

      // la estimacion final es zk
      // el intervalo de prediccion de <range> horas significa que la estimacion esta entre
      // zk - <range> y zk + <range> horas
      cout << "El intervalo de prediccion de " << range << " horas significa que" << endl;
      cout << " la estimacion esta entre " << Zk - range << " y " << Zk + range << " horas." << endl;
      cout << "UPI (70%): " <<  Zk + range << endl;
      cout << "LPI (70%): " <<  Zk - range << endl;

      for (int i = 0; i < rows; ++i){
         delete[] matriz[i];
      } // for
      delete[] matriz;

   } else {
      cout << "No se puede realizar el calculo con menos de cinco elementos por columna" << endl;
   } // if

   deleteList(lista_w);
   deleteList(lista_x);
   deleteList(lista_y);
   deleteList(lista_z);

   // borrar la matriz

   // fin del programa
   return 0;

} // main
