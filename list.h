
#ifndef LIST_H_
#define LIST_H_

#include <iostream>
using namespace std;

struct node;
struct list;

// genera una lista vacia
list* newList();

// cantidad de elementos en la lista
int cantElemen(list *l);

// agrega un nuevo elemento a la lista
void addList( list *&l, double n);

// borra el elemento de la lista en la posicion pos
void elimList( list *&l, int pos);

// obtiene el nodo de la lista en la posicion pos
node* getNodeList( list *l, int pos);

// borra todos los elementos de la lista
void deleteList( list *&l);

// imprime todos los elementos de la lista
void printList( list *l);

// retorna el valor de un nodo
double getNodeVal( node *n);

#endif /* LIST_H_ */
