
#include "listPairDouble.h"

struct nodePairDouble{
   double         val1;
   double         val2;
   nodePairDouble *next;
};

struct listPairDouble{
   int             size;
   nodePairDouble *first;
   nodePairDouble *last;
};

// genera una lista vacia
listPairDouble* newListPairDouble(){
   listPairDouble *li = new listPairDouble;

   li->size  = 0;
   li->first = NULL;
   li->last  = NULL;

   return li;
} // new_list

// cantidad de elementos en la lista
int cantElemen(listPairDouble *l){
   return l->size;
} // cant_elemen_list

// agrega un nuevo elemento a la lista
void addList( listPairDouble *&l, double n1, double n2){

   nodePairDouble *nuevo = new nodePairDouble;
   nuevo->val1  = n1;
   nuevo->val2  = n2;
   nuevo->next = NULL;

   if (cantElemen(l) == 0){
      l->first = nuevo;
      l->last  = nuevo;
   }else{
      nodePairDouble *ultimo = l->last;

      l->last      = nuevo;
      ultimo->next = nuevo;
   } // if

   l->size++;

} // add_list

// borra el elemento de la lista en la posicion pos
void elimList( listPairDouble *&l, int pos){

   // si la posicion es valida para la lista
   if ( (pos <= cantElemen(l)-1) && (pos >= 0) ){

      if (pos == 0){

         nodePairDouble *borrar = l->first;

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

         nodePairDouble *tmp = l->first;
         nodePairDouble *borrar;

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
nodePairDouble* getNodeList( listPairDouble *l, int pos){

   if ( (pos <= cantElemen(l)-1) && (pos >= 0) ){

      nodePairDouble *tmp = l->first;

      for (int i=0; i<pos; i++){
         tmp = tmp->next;
      } // for

      return tmp;
   }else{
      return NULL;
   }

} // get_node_list

// borra la lista
void deleteList( listPairDouble *&l){

   int cant = cantElemen(l);

   for (int i = 0; i < cant; i++){
      elimList(l,0);
   }

   delete l;

} // delete_list

// imprime todos los elementos de la lista
void printList( listPairDouble *l){

   int cant = cantElemen(l);
   nodePairDouble * n;

   for (int i = 0; i < cant; i++){
      n = getNodeList(l,i);
      cout << "(" << n->val1 << "," << n->val2 << ")" << ",";
   } // for

   cout << endl;

} // print_list

// crea un nuevo elemento de tipo nodo
nodePairDouble* newNodePairDouble(double n1, double n2){

   nodePairDouble *nuevo = new nodePairDouble;
   nuevo->val1  = n1;
   nuevo->val2  = n2;

   return nuevo;

} // newNodePairDouble

// borra el nodo
void deleteNodePairDouble( nodePairDouble *&n){

   delete n;

} // deleteNodePairDouble

// retorna el valor de un nodo
double getNodeVal_1( nodePairDouble *n){

   return n->val1;

} //getNodeVal_1

// retorna el valor de un nodo
double getNodeVal_2( nodePairDouble *n){

   return n->val2;

} //getNodeVal_2
