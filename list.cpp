
#include "list.h"
#include <stdio.h>

struct node{
   double  val;
   node   *next;
};

struct list{
   int   size;
   node *first;
   node *last;
};

// genera una lista vacia
list* newList(){
   list *li = new list;

   li->size  = 0;
   li->first = NULL;
   li->last  = NULL;

   return li;
} // new_list

// cantidad de elementos en la lista
int cantElemen(list *l){
   return l->size;
} // cant_elemen_list

// agrega un nuevo elemento a la lista
void addList( list *&l, double n){

   node *nuevo = new node;
   nuevo->val  = n;
   nuevo->next = NULL;

   if (cantElemen(l) == 0){
      l->first = nuevo;
      l->last  = nuevo;
   }else{
      node *ultimo = l->last;

      l->last      = nuevo;
      ultimo->next = nuevo;
   } // if

   l->size++;

} // add_list

// borra el elemento de la lista en la posicion pos
void elimList( list *&l, int pos){

   // si la posicion es valida para la lista
   if ( (pos <= cantElemen(l)-1) && (pos >= 0) ){

      if (pos == 0){

         node *borrar = l->first;

         if (cantElemen(l) == 1){
            l->size  = 0;
            l->first = NULL;
            l->last  = NULL;
         }else{
            l->size--;
            l->first = borrar->next;
         } // if

         delete borrar;

      }else{

         node *tmp = l->first;
         node *borrar;

         for (int i=1; i<pos; i++){
            tmp = tmp->next;
         } // for

         borrar = tmp->next;

         tmp->next = borrar->next;

         if (tmp->next == NULL){
            l->last = tmp;
         } // if

         delete borrar;
         l->size--;

      } // if (pos == 1)

   } // if

} // elim_list

// obtiene el elemento de la lista en la posicion pos
node* getNodeList( list *l, int pos){

   if ( (pos <= cantElemen(l)-1) && (pos >= 0) ){

      node *tmp = l->first;

      for (int i=0; i<pos; i++){
         tmp = tmp->next;
      } // for

      return tmp;
   }else{
      return NULL;
   }

} // get_node_list

// borra la lista
void deleteList( list *&l){

   int cant = cantElemen(l);

   for (int i = 0; i < cant; i++){
      elimList(l,0);
   }

   delete l;

} // delete_list

// imprime todos los elementos de la lista
void printList( list *l){

   int cant = cantElemen(l);
   node * n;

   for (int i = 0; i < cant; i++){
      n = getNodeList(l,i);
      cout << n->val << ",";
   } // for

   cout << endl;

} // print_list

// retorna el valor de un nodo
double getNodeVal( node *n){

   return n->val;

} //get_node_val
