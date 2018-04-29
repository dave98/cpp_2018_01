#ifndef C_R_TRRE_H
#define C_R_TRRE_H

#include <iostream>
#include "c_nodo.h"
#include "c_point.h"

using namespace std;

template <class T, int D, int C>//De momento no añadimos ningún parámetro propio del rtree
class c_r_tree{
public:
  c_nodo<T,D,C>* head;

  c_r_tree();
  ~c_r_tree();

  void insert(c_point<T, D>);//Al igual que el quadtree insertaremos puntos.
};

template <class T, int D, int C>
c_r_tree<T,D,C>::c_r_tree(){
  this->head = NULL; //Iniciamos con la cabeza vacia JAJAJAJA
}

template <class T, int D, int C>
c_r_tree<T,D,C>::~c_r_tree(){
}

template <class T, int D, int C>
void c_r_tree<T,D,C>::insert(c_point<T,D> a){
  if(this->head == NULL){
    this->head = new c_nodo<T,D,C>;
    this->head->add_point(a);
  }
  else{

  }

}




#endif
