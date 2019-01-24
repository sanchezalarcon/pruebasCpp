
#ifndef LISTPAIRDOUBLE_H_
#define LISTPAIRDOUBLE_H_

#include <iostream>
using namespace std;

struct nodePairDouble;
struct listPairDouble;

// genera una lista vacia
listPairDouble* newListPairDouble();

// cantidad de elementos en la lista
int cantElemen(listPairDouble *l);

// agrega un nuevo elemento a la lista
void addList( listPairDouble *&l, double n1, double n2);

// borra el elemento de la lista en la posicion pos
void elimList( listPairDouble *&l, int pos);

// obtiene el nodo de la lista en la posicion pos
nodePairDouble* getNodeList( listPairDouble *l, int pos);

// borra todos los elementos de la lista
void deleteList( listPairDouble *&l);

// imprime todos los elementos de la lista
void printList( listPairDouble *l);

// crea un nuevo nodo con los elementos pasados
nodePairDouble* newNodePairDouble(double n1, double n2);

// borra el nodo
void deleteNodePairDouble( nodePairDouble *&n);

// retorna el primer valor de un nodo
double getNodeVal_1( nodePairDouble *n);

// retorna el segundo valor de un nodo
double getNodeVal_2( nodePairDouble *n);

#endif /* LISTPAIRDOUBLE_H_ */
