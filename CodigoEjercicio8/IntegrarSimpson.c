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
#include "IntegrarSimpson.h"
#define NUMSEG 10
#define E 0.000001

IntegrarSimpson::IntegrarSimpson(){
}

IntegrarSimpson::~IntegrarSimpson(){
}

float IntegrarSimpson::Gamma(float x){
      if (x==1){
          return 1;
      }else if (x==0.5) {
          return sqrt(M_PI);
      } else{
          return(x-1) * Gamma(x-1);
      }	  
}

float IntegrarSimpson::F(float x, float dof){
      float ret= (Gamma((dof+1)/2)/(sqrt(dof*M_PI)*Gamma(dof/2)))*pow((1+x*x/dof),-(dof+1)/2);
      //printf("DEBUG F x[%f], dof[%f], constanteSup [%f], constanteInf[%f],ret[%f]\n",x,dof,sqrt(dof*M_PI),Gamma(dof/2),ret);
      return ret;
}

float IntegrarSimpson::SumatoriaF(float ini, float n,float k,float w,float dof){
      float ret=0;
      for(int i=ini;i<=n;i=i+2){
	     ret+=k*F(i*w,dof);
      }
      //printf("DEBUG SumatoriaF, ini[%f], n[%f], k[%f], w[%f], dof[%f], ret[%f]\n",ini,n,k,w,dof,ret);
      return ret;
}


float IntegrarSimpson::Calcular(float xi, float xf, float dof){
    float numseg = NUMSEG;
    float p1 =1;
    float p2 =2;
    float w;
    while ((p1-p2>E && p1-p2>0)|| (p2-p1>E && p2-p1>0)){
	w=xf/numseg;
        p1=w/3*(F(xi,dof)+SumatoriaF(1,numseg-1,4,w,dof)+SumatoriaF(2,numseg-2,2,w,dof)+F(xf,dof));
	numseg=numseg*2;
	w=xf/numseg;
	p2=w/3*(F(xi,dof)+SumatoriaF(1,numseg-1,4,w,dof)+SumatoriaF(2,numseg-2,2,w,dof)+F(xf,dof));
        //printf("DEBUG Calcular [%f],p1[%f],p2[%f],abs(p1-p2)[%f],e[%f] \n",w,p1,p2,p1-p2,E);
    }
    return p1;
}

float IntegrarSimpson::CalcularX(float po, float dof){
    float x =1;
	typedef int local_Type;
    float d =0.5;
    bool UltimoSignoPositivo = true;
    float pc =Calcular(0, x, dof);
	while ((po-pc>E && po-pc>0)|| (pc-po>E && pc-po>0)){
	//printf("DEBUG CalcularX po[%f], pc[%f], x[%f], d[%f] pc-po[%f], UltimoSignoPositivo[%s]\n",po,pc,x,d,pc-po,UltimoSignoPositivo?"Si":"No");
        if (pc>po){
		     if (!UltimoSignoPositivo){
			    d=d/2;
			 }
			 UltimoSignoPositivo=true;
                         x=x-d;
		}else{
		     if (UltimoSignoPositivo){
			    d=d/2;
			 }
			 UltimoSignoPositivo=false;
                         x=x+d;
		}
                if (x==0){
                        pc=0;
                }else{
		        pc =Calcular(0, x, dof);
                }
	}
    return x;
}


