/******************************************************************/
/* Program Assignment:  Ejercicio7 PSP 2015 FING                  */
/* Name:                Agustin Young                             */
/* Date:                Mayo 2015                                 */
/* Description:         Programa para calcluar la sgnificancia y  */
/*                         prediccion                             */
/******************************************************************/
/******************************************************************/
/* Listing Contents:                                              */
/*    Reuse instructions                                          */
/*        El progrma recibe como primer parametro xk y luego pares*/
/*        de datos para los calculos.                             */
/*        Para ver ejemplos de invocacion ver PruebasEjercicio7.sh*/
/*    Modification instructions                                   */
/*        La interaccion del programa se puede modificar editando */
/*        el archivo Ejercicio7.c para que por ejemplo vaya       */
/*        solicitando los parametros de entrada uno a uno.        */
/*    Compilation instructions                                    */
/*        Ejecutar makefile o el archivo PruebasEjercicio7.sh     */
/*    Class declarations:                                         */
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
/*           void Calcular(Lista * lista, float xk, float yk,     */
/*                       float & range, float & upi, float & lpi) */
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
/*       Clase ListaNodoParReales                                 */
/*         Se definio esta lista para representar pares de reales */
/*         Funciones disponibles:                                 */
/*           float ObtenerX();                                    */
/*           float ObtenerY();                                    */
/*           void AsignarX(float x);                              */
/*           void AsignarY(float y);                              */
/*       Clase RegresionLineal                                    */
/*         Funciones disponibles:                                 */
/*           void Calcular(Lista * lista, float xk, float & b0,   */
/*               float & b1, float & rxy, float &r2, float & yk); */
/*           Realiza todos los calculos de la regresion lineal    */
/*       Clase Significancia                                      */
/*         Funciones disponibles:                                 */
/*           void Calcular(float n, float rxy)                    */
/*           Realiza todos los calculos de la significancia       */
/******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "ListaNodo.h"

ListaNodo::ListaNodo(){
}

ListaNodo::~ListaNodo(){
}

ListaNodo * ListaNodo::ObtenerSiguiente(){
      return sig;
}

void ListaNodo::AsignarSiguiente(ListaNodo * nodo){
      sig=nodo;
}
