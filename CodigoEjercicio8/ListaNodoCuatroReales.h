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

#ifndef __LISTANODOCUATROREAL_H
#define __LISTANODOCUATROREAL_H
#include "ListaNodo.h"

class ListaNodoCuatroReales 
    : public ListaNodo{
    private:
	       float w;
           float x;
		   float y;
		   float z;
    public:
	       float ObtenerW();
           float ObtenerX();
           float ObtenerY();
		   float ObtenerZ();
		   void AsignarW(float w);
           void AsignarX(float x);
           void AsignarY(float y);
		   void AsignarZ(float z);
};

#endif
