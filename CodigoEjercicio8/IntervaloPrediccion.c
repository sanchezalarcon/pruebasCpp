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
#include "IntervaloPrediccion.h"
#include "ListaNodoCuatroReales.h"
#include "IntegrarSimpson.h"

IntervaloPrediccion::IntervaloPrediccion(){
}

IntervaloPrediccion::~IntervaloPrediccion(){
}

float IntervaloPrediccion::SumatoriaW(Lista * lista){
      float ret=0;
      ListaNodoCuatroReales * nodo;
      for(int i=1;i<=lista->ListaLargo();i++){
             nodo=(ListaNodoCuatroReales *)lista->ObtenerListaNodo(i);
             ret+=nodo->ObtenerW();
          }
          return ret;
}

float IntervaloPrediccion::SumatoriaX(Lista * lista){
      float ret=0;
      ListaNodoCuatroReales * nodo;
      for(int i=1;i<=lista->ListaLargo();i++){
	     nodo=(ListaNodoCuatroReales *)lista->ObtenerListaNodo(i);
	     ret+=nodo->ObtenerX();
	  }
	  return ret;
}

float IntervaloPrediccion::SumatoriaY(Lista * lista){
      float ret=0;
      ListaNodoCuatroReales * nodo;
      for(int i=1;i<=lista->ListaLargo();i++){
             nodo=(ListaNodoCuatroReales *)lista->ObtenerListaNodo(i);
             ret+=nodo->ObtenerY();
          }
          return ret;
}

float IntervaloPrediccion::SumatoriaWWA2(Lista * lista,float wa){
      float ret=0;
      ListaNodoCuatroReales * nodo;
      for(int i=1;i<=lista->ListaLargo();i++){
	     nodo=(ListaNodoCuatroReales *)lista->ObtenerListaNodo(i);
	     ret+=pow(nodo->ObtenerW()-wa,2);
	  }
	  return ret;
}

float IntervaloPrediccion::SumatoriaXXA2(Lista * lista,float xa){
      float ret=0;
      ListaNodoCuatroReales * nodo;
      for(int i=1;i<=lista->ListaLargo();i++){
	     nodo=(ListaNodoCuatroReales *)lista->ObtenerListaNodo(i);
	     ret+=pow(nodo->ObtenerX()-xa,2);
	  }
	  return ret;
}

float IntervaloPrediccion::SumatoriaYYA2(Lista * lista,float ya){
      float ret=0;
      ListaNodoCuatroReales * nodo;
      for(int i=1;i<=lista->ListaLargo();i++){
	     nodo=(ListaNodoCuatroReales *)lista->ObtenerListaNodo(i);
	     ret+=pow(nodo->ObtenerY()-ya,2);
	  }
	  return ret;
}

float IntervaloPrediccion::CalcularDesviacion(Lista * lista, float b0,float b1){
      float ret =0;
      ListaNodoCuatroReales * nodo;
      for(int i=1;i<=lista->ListaLargo();i++){
	    nodo=(ListaNodoCuatroReales *)lista->ObtenerListaNodo(i);
            ret+=pow(nodo->ObtenerY()-b0-b1*nodo->ObtenerX(),2);
      }
      if (ret!=0){
            ret=sqrt(ret/(lista->ListaLargo()-2));
      }
      return ret; 
}

float IntervaloPrediccion::CalcularDesviacionMultiple(Lista * lista, float b0,float b1, float b2, float b3){
      float ret =0;
      ListaNodoCuatroReales * nodo;
      for(int i=1;i<=lista->ListaLargo();i++){
	    nodo=(ListaNodoCuatroReales *)lista->ObtenerListaNodo(i);
            ret+=pow(nodo->ObtenerZ()-b0-b1*nodo->ObtenerW()-b2*nodo->ObtenerX()-b3*nodo->ObtenerY(),2);
      }
      if (ret!=0){
            ret=sqrt(ret/(lista->ListaLargo()-4));
      }
      return ret; 
}

void IntervaloPrediccion::Calcular(Lista * lista, float xk, float yk, float  b0,float b1, float & range, float & upi, float & lpi){

    float n = lista->ListaLargo();
    float xa= SumatoriaX(lista)/n;
    float sxxa2= SumatoriaXXA2(lista,xa);
    IntegrarSimpson integrar_simpson;
    float p=0.35;
    float dof=n-2;
    float x = integrar_simpson.CalcularX(p,dof);
    float desv= CalcularDesviacion(lista, b0,b1);
    range=x*desv*sqrt(1+1/n+pow(xk-xa,2)/sxxa2);
    upi=yk+range;
    lpi=yk-range;
    //printf("Calculo de intervalo prediccion. Resualtados [ x[%f], desv[%f],range[%f] ]\n", x,desv,range);
}

void IntervaloPrediccion::CalcularMultiple(Lista * lista, float wk, float xk, float yk, float zk, float  b0,float b1, float b2, float b3, float & range, float & upi, float & lpi){

    float n = lista->ListaLargo();
    float wa= SumatoriaW(lista)/n;
    float xa= SumatoriaX(lista)/n;
    float ya= SumatoriaY(lista)/n;
    float swwa2= SumatoriaWWA2(lista,wa);
    float sxxa2= SumatoriaXXA2(lista,xa);
    float syya2= SumatoriaYYA2(lista,ya);
    IntegrarSimpson integrar_simpson;
    float p=0.35;
    float dof=n-4;
    float x = integrar_simpson.CalcularX(p,dof);
    float desv= CalcularDesviacionMultiple(lista, b0,b1,b2,b3);
    range=x*desv*sqrt(1 + 1/n + pow(wk-wa,2)/swwa2 + pow(xk-xa,2)/sxxa2 + pow(yk-ya,2)/syya2);
    upi=zk+range;
    lpi=zk-range;
    //printf("Calculo de intervalo prediccion multiple. Resualtados [ swwa2[%f], sxxa2[%f], syya2[%f], x[%f], desv[%f],range[%f] ]\n", swwa2, sxxa2,syya2, x,desv,range);
}


