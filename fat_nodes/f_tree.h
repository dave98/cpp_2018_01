#ifndef F_TREE_H
#define F_TREE_H

#include <iostream>
#include "f_nodo.h"
using namespace std;

template<class T>
class f_tree{
public:
  f_nodo<T>* head;
  int members_number;
  vector<int> changes;

  f_tree();
  ~f_tree();

  void insert_data(T, int);
  bool look_for_position(f_nodo<T>** &, int);
  void print_tree();
  void undo(int);
  void extensive_undo();
};

template<class T>
f_tree<T>::f_tree(){
  this->head = NULL;
  this->members_number = 0;
  this->changes = vector<int>();
}

template<class T>
f_tree<T>::~f_tree(){}

//Yo inserto un nodo con un valor T y un id definido por mi.
template<class T>
bool f_tree<T>::look_for_position(f_nodo<T>** &navegante, int basic_id){
  bool continue_ = true;
  while((*navegante) and continue_){
    if((*navegante)->id_node == basic_id){
      continue_ = false;
    }
    else{
      navegante = &((*navegante)->hijos[(*navegante)->id_node < basic_id]);
    }
  }

  return !continue_;
  //Si retorna true es que hemos encontrado el ID que buscabamos
  //Falso cuando no existe el id y hay que crear un nuevo nodo.
}

template<class T>
void f_tree<T>::insert_data(T incoming_data, int current_id){
  f_nodo<T>** navegante = &this->head;
  this->changes.push_back(current_id);
  if(this->look_for_position(navegante, current_id)){
    //cout<<"Se encontro un nodo con este id. Creando una nueva version"<<endl;
    (*navegante)->insert_data(incoming_data);
  }
  else{
    //cout<<"No se encontro el id solicitado. Insertando nuevo nodo"<<endl;
    (*navegante) = new f_nodo<T>(incoming_data, current_id);
    this->members_number++;
  }
}

template <class T>
void f_tree<T>::undo(int incoming_id){
  f_nodo<T>** navegante = &this->head;
  if(this->look_for_position(navegante, incoming_id)){
    cout<<"Undo in nodo: "<<incoming_id<<endl;
    (*navegante)->undo();
  }
  else{
    cout<<"Nodo no encontrado"<<endl;
  }
}

template <class T>
void f_tree<T>::extensive_undo(){
  if(this->changes.size() != 0){
    int erase = this->changes[changes.size()-1];
    this->changes.pop_back();
    this->undo(erase);
  }
}

template <class T>
void f_tree<T>::print_tree(){
  cout<<endl<<"PRINT TREE-------------------------------------------"<<endl;
  vector<f_nodo<T>* > stack(1, this->head);
  while(!stack.empty()){
    stack[0]->print_nodo();
    for(int i = 0; i < 2; i++){
      if(stack[0]->hijos[i]){
        stack.push_back(stack[0]->hijos[i]);
      }
    }
    stack.erase(stack.begin());
  }

}


#endif
