/******************************************************************/
/* Program Assignment:  Ejercicio8 PSP 2015 FING                  */
/* Name:                Agustin Young                             */
/* Date:                Mayo 2015                                 */
/* Description:         Programa para calcular los parametros     */
/*                       de estimación para la regresión multiple */
/******************************************************************/
/******************************************************************/
/* Listing Contents:                                              */
/*    Reuse instructions                                          */
/*        El progrma recibe como primeros parametros  wk, xk, yk  */
/*        para calcluar zk, y una cantida variable de cuaternas   */
/*        historicas para realizar el calculo                     */
/*        Para ver ejemplos de invocacion ver PruebasEjercicio8.sh*/
/*    Modification instructions                                   */
/*        La interaccion del programa se puede modificar editando */
/*        el archivo Ejercicio8.c para que por ejemplo vaya       */
/*        solicitando los parametros de entrada uno a uno.        */
/*    Compilation instructions                                    */
/*        Ejecutar makefile o el archivo PruebasEjercicio8.sh     */
/*    Class declarations:                                         */
/*       Clase Gauss                                              */
/*         Se definio esta clase con la escalerización de matrices*/
/*         Funciones disponibles:                                 */
/*           void Escalerizar(float ** M, int m, int n)           */
/*       Clase IntegrarSimpson                                    */
/*         Se definio esta clase para el calculo de la integral.  */
/*         Funciones disponibles:                                 */
/*           float Calcular(float xi, float xf, float dof)        */
/*              Realiza los calculos de la integra de Simpson.    */
/*           float CalcularX(float p, float dof)                  */
/*              Resive un resultado P de la integral y calcula    */
/*              el valor del parametro x.                         */
/*       Clase IntervaloPrediccion                                */
/*         Funciones disponibles:                                 */
/*           void CalcularMultiple(Lista * lista, float wk,       */
/*              float xk, float yk, float zk, float  b0,float b1, */
/*              float b2, float b3, float & range, float & upi,   */
/*              float & lpi)                                      */
/*           Realiza todos los calculos de rango de prediccion    */
/*       Clase Lista                                              */
/*         Se definio la clase Lista para guardar y acceder       */
/*         posteriormente a las parejas de datos ingresadas.      */
/*         Source code in Archivo.h Archivo.c                     */
/*         Funciones disponibles:                                 */
/*           int ListaLargo(); Devuelve el largo de la lista      */
/*           void ListaAgregar(ListaNodo * nodo); Agrega un nodo  */
/*           void ListaEliminar(int pos); Elimina un nodo         */
/*           ListaNodo * ObtenerListaNodo(int pos);               */
/*       Clase ListaNodo                                          */
/*         Se definio la clase ListNodo como la implementacion de */
/*         un nodo generico de la lista.                          */
/*         Funciones disponibles:                                 */
/*           ListaNodo * ObtenerSiguiente();                      */
/*           void AsignarSiguiente(ListaNodo * nodo);             */
/*       Clase ListaNodoCuatroReales                              */
/*         Se definio este nodo como una cuarteta de reales       */
/*         Funciones disponibles:                                 */
/*           float ObtenerW();                                    */
/*           float ObtenerX();                                    */
/*           float ObtenerY();                                    */
/*           float ObtenerZ();                                    */
/*           void AsignarW(float w);                              */
/*           void AsignarX(float x);                              */
/*           void AsignarY(float y);                              */
/*           void AsignarZ(float z);                              */
/*       Clase RegresionLineal                                    */
/*         Funciones disponibles:                                 */
/*           void CalcularMultiple(Lista * lista, float wk,       */
/*              float xk, float yk, float & b0, float & b1,       */
/*              float & b2, float & b3,float & rxy, float &r2,    */
/*              float & zk);                                      */
/*           Realiza todos los calculos de la regresion lineal    */
/******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Gauss.h"
#include <string.h>

Gauss::Gauss(){
}

Gauss::~Gauss(){
}
void Gauss::SwapFilas(float ** M, int m, int n, int f1, int f2){
         float * aux=(float *) malloc (n*sizeof(float));
	 memcpy(aux, M[f1],n*sizeof(float));
	 memcpy(M[f1],M[f2],n*sizeof(float));
	 memcpy(M[f2],aux,n*sizeof(float));
	 //printf("DEBUG: SwapFilas f1 [%d] f2 [%d]\n",f1,f2);
}

int Gauss::IndiceMayorValorColumna(float ** M, int m, int n, int i){
	 int maxPos=i;
	 float maxVal=abs(M[i][i]);
	 for (int y=i+1;y<m;y++){
	    if (abs(M[y][i])>maxVal){
               maxVal=abs(M[y][i]);
               maxPos = y;
            }	
	 }
	 //printf("DEBUG: IndiceMayorValorColumna Col [%d] maxVal [%f] maxPos[%d]\n",i,maxVal, maxPos);
	 return maxPos;
}

void Gauss::ImprimirMatriz(float ** M, int m, int n){
     printf("---------------------\n");
	 for (int y=0;y<m;y++){
	     for (int x=0;x<n;x++){
	        printf(" %f ",M[y][x]);	 
		 }
		 printf("\n");
	 }
	 printf("---------------------\n");
}

void Gauss::Escalerizar(float ** M, int m, int n){
    int min=m>n?n:m;
	//ImprimirMatriz(M, m, n);
    for (int i=0; i<min;i++){
	     int f=IndiceMayorValorColumna(M,m,n,i);
		 if (i!=f){
		    SwapFilas(M, m, n, i, f);
		    //ImprimirMatriz(M, m, n);
		 }
    		 for (int y=i+1;y<m;y++){
		    if (abs(M[y][i])>0){
		       float alpha = M[i][i]/M[y][i];
		       for (int x=0;x<n;x++){
                           M[y][x]=M[y][x]*alpha-M[i][x];
                       }			
	            }
		 }
		 //ImprimirMatriz(M, m, n);
    }
}


