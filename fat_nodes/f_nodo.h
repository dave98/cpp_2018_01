#ifndef F_NODO_H
#define F_NODO_H

#include <iostream>
#include <vector>

using namespace std;

template <class T>
class f_nodo{
public:
  vector<T> inner_data;
  int id_node; //Alow us to give the nodo a specific  id in case of direct insertion.
  int actual_version;
  f_nodo* hijos[2];

  f_nodo(T, int);
  ~f_nodo();
  void insert_data(T);
  void print_nodo();
  void undo();
};

template <class T>
f_nodo<T>::f_nodo(T incoming_data, int _id_node){
  this->inner_data = vector<T>(1,incoming_data);
  this->id_node = _id_node;
  this->actual_version = 0;
  this->hijos[0] = NULL;
  this->hijos[1] = NULL;
}

template <class T>
f_nodo<T>::~f_nodo(){}

template <class T>
void f_nodo<T>::undo(){
  if(this->inner_data.size() !=0){
    this->inner_data.pop_back();
  }
}

template <class T>
void f_nodo<T>::insert_data(T incoming_data){
  this->inner_data.push_back(incoming_data);
  this->actual_version++;
}

template<class T>
void f_nodo<T>::print_nodo(){
  if(this->inner_data.size() != 0){
    cout<<"Id NODO: "<<this->id_node<<" -----------------------------"<<endl;
    for(unsigned int i = 0; i < this->inner_data.size(); i++){
      cout<<"[ "<<"T"<<i<<".0"<<" - "<<this->inner_data[i]<<" ]"<<endl;
    }
    cout<<"---------------------------------------"<<endl<<endl;
  }
}
#endif
