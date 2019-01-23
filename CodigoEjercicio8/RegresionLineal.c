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
#include "RegresionLineal.h"
#include "ListaNodoCuatroReales.h"
#include "Gauss.h"

RegresionLineal::RegresionLineal(){
}

RegresionLineal::~RegresionLineal(){
}

float RegresionLineal::SumatoriaW(Lista * lista){
      float ret=0;
      ListaNodoCuatroReales * nodo;
      for(int i=1;i<=lista->ListaLargo();i++){
	     nodo=(ListaNodoCuatroReales *)lista->ObtenerListaNodo(i);
	     ret+=nodo->ObtenerW();
	  }
	  return ret;
}

float RegresionLineal::SumatoriaX(Lista * lista){
      float ret=0;
      ListaNodoCuatroReales * nodo;
      for(int i=1;i<=lista->ListaLargo();i++){
	     nodo=(ListaNodoCuatroReales *)lista->ObtenerListaNodo(i);
	     ret+=nodo->ObtenerX();
	  }
	  return ret;
}

float RegresionLineal::SumatoriaY(Lista * lista){
      float ret=0;
      ListaNodoCuatroReales * nodo;
      for(int i=1;i<=lista->ListaLargo();i++){
	     nodo=(ListaNodoCuatroReales *)lista->ObtenerListaNodo(i);
	     ret+=nodo->ObtenerY();
	  }
	  return ret;
}

float RegresionLineal::SumatoriaZ(Lista * lista){
      float ret=0;
      ListaNodoCuatroReales * nodo;
      for(int i=1;i<=lista->ListaLargo();i++){
	     nodo=(ListaNodoCuatroReales *)lista->ObtenerListaNodo(i);
	     ret+=nodo->ObtenerZ();
	  }
	  return ret;
}

float RegresionLineal::SumatoriaXY(Lista * lista){
      float ret=0;
      ListaNodoCuatroReales * nodo;
      for(int i=1;i<=lista->ListaLargo();i++){
	     nodo=(ListaNodoCuatroReales *)lista->ObtenerListaNodo(i);
	     ret+=nodo->ObtenerX()*nodo->ObtenerY();
	  }
	  return ret;
}

float RegresionLineal::SumatoriaWX(Lista * lista){
      float ret=0;
      ListaNodoCuatroReales * nodo;
      for(int i=1;i<=lista->ListaLargo();i++){
	     nodo=(ListaNodoCuatroReales *)lista->ObtenerListaNodo(i);
	     ret+=nodo->ObtenerW()*nodo->ObtenerX();
	  }
	  return ret;
}

float RegresionLineal::SumatoriaWY(Lista * lista){
      float ret=0;
      ListaNodoCuatroReales * nodo;
      for(int i=1;i<=lista->ListaLargo();i++){
	     nodo=(ListaNodoCuatroReales *)lista->ObtenerListaNodo(i);
	     ret+=nodo->ObtenerW()*nodo->ObtenerY();
	  }
	  return ret;
}

float RegresionLineal::SumatoriaWZ(Lista * lista){
      float ret=0;
      ListaNodoCuatroReales * nodo;
      for(int i=1;i<=lista->ListaLargo();i++){
             nodo=(ListaNodoCuatroReales *)lista->ObtenerListaNodo(i);
             ret+=nodo->ObtenerW()*nodo->ObtenerZ();
          }
          return ret;
}

float RegresionLineal::SumatoriaXZ(Lista * lista){
      float ret=0;
      ListaNodoCuatroReales * nodo;
      for(int i=1;i<=lista->ListaLargo();i++){
             nodo=(ListaNodoCuatroReales *)lista->ObtenerListaNodo(i);
             ret+=nodo->ObtenerX()*nodo->ObtenerZ();
          }
          return ret;
}

float RegresionLineal::SumatoriaYZ(Lista * lista){
      float ret=0;
      ListaNodoCuatroReales * nodo;
      for(int i=1;i<=lista->ListaLargo();i++){
             nodo=(ListaNodoCuatroReales *)lista->ObtenerListaNodo(i);
             ret+=nodo->ObtenerY()*nodo->ObtenerZ();
          }
          return ret;
}

float RegresionLineal::SumatoriaW2(Lista * lista){
      float ret=0;
      ListaNodoCuatroReales * nodo;
      for(int i=1;i<=lista->ListaLargo();i++){
	     nodo=(ListaNodoCuatroReales *)lista->ObtenerListaNodo(i);
	     ret+=nodo->ObtenerW()*nodo->ObtenerW();
	  }
	  return ret;
}

float RegresionLineal::SumatoriaX2(Lista * lista){
      float ret=0;
      ListaNodoCuatroReales * nodo;
      for(int i=1;i<=lista->ListaLargo();i++){
	     nodo=(ListaNodoCuatroReales *)lista->ObtenerListaNodo(i);
	     ret+=nodo->ObtenerX()*nodo->ObtenerX();
	  }
	  return ret;
}

float RegresionLineal::SumatoriaY2(Lista * lista){
      float ret=0;
      ListaNodoCuatroReales * nodo;
      for(int i=1;i<=lista->ListaLargo();i++){
	     nodo=(ListaNodoCuatroReales *)lista->ObtenerListaNodo(i);
	     ret+=nodo->ObtenerY()*nodo->ObtenerY();
	  }
	  return ret;
}

void RegresionLineal::Calcular(Lista * lista, float xk, float & b0, float & b1, float & rxy, float &r2, float & yk){
    float n = lista->ListaLargo();
    float sx= SumatoriaX(lista);
    float sy= SumatoriaY(lista);
    float sxy= SumatoriaXY(lista);
    float sx2= SumatoriaX2(lista);
    float sy2= SumatoriaY2(lista);
    float xa = sx/n;
    float ya = sy/n;
    //float x2a = sx2/n;
    b1=(sxy-n*xa*ya)/(sx2-n*xa*xa);
    b0=ya-b1*xa;
    rxy=(n*sxy-sx*sy)/sqrt((n*sx2-sx*sx)*(n*sy2-sy*sy));
    r2=rxy*rxy;
    yk=b0+b1*xk;
    //printf("Debug: n[%f],sx[%f],sy[%f],sxy[%f],sx2[%f],sy2[%f]\n",n,sx,sy,sxy,sx2,sy2);
}

void RegresionLineal::CalcularMultiple(Lista * lista, float wk, float xk, float yk, float & b0, float & b1, float & b2, float & b3,float & rxy, float &r2, float & zk){
    float n = lista->ListaLargo();
    float sw= SumatoriaW(lista);
    float sx= SumatoriaX(lista);
    float sy= SumatoriaY(lista);
    float sz= SumatoriaZ(lista);
    float swx= SumatoriaWX(lista);
    float swy= SumatoriaWY(lista);
    float sxy= SumatoriaXY(lista);
    float swz= SumatoriaWZ(lista);
    float sxz= SumatoriaXZ(lista);
    float syz= SumatoriaYZ(lista);
    float sw2= SumatoriaW2(lista);
    float sx2= SumatoriaX2(lista);
    float sy2= SumatoriaY2(lista);

    //printf("Debug: wk[%f],xk[%f],yk[%f],sw[%f],sx[%f] sy[%f], sz[%f]\n",wk,xk,yk,sw,sx,sy,sz);
    float ** m = (float **)malloc (5*sizeof(float *));
    for (int i=0;i<5;i++)
         m[i] = (float *) malloc (4*sizeof(float));

    m[0][0]=n;  m[0][1]=sw;  m[0][2]=sx; m[0][3]=sy; m[0][4]=sz;
    m[1][0]=sw; m[1][1]=sw2; m[1][2]=swx; m[1][3]=swy; m[1][4]=swz;
    m[2][0]=sx; m[2][1]=swx; m[2][2]=sx2; m[2][3]=sxy; m[2][4]=sxz;
    m[3][0]=sy; m[3][1]=swy; m[3][2]=sxy; m[3][3]=sy2; m[3][4]=syz;
	
    Gauss gauss;
    gauss.Escalerizar(m,4,5);
	
    //Sustitucion hacia atras
    b3=m[3][4]/m[3][3];
    b2=(m[2][4]-b3*m[2][3])/m[2][2];
    b1=(m[1][4]-b3*m[1][3]-b2*m[1][2])/m[1][1];
    b0=(m[0][4]-b3*m[0][3]-b2*m[0][2]-b1*m[0][1])/m[0][0];
	
    rxy=(n*sxy-sx*sy)/sqrt((n*sx2-sx*sx)*(n*sy2-sy*sy));
    r2=rxy*rxy;
    zk= b0+ wk*b1 + xk*b2 + yk*b3;
    //printf("Debug: n[%f],sx[%f],sy[%f],sxy[%f],sx2[%f],sy2[%f]\n",n,sx,sy,sxy,sx2,sy2);
}

