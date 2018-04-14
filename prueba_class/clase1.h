#ifndef CLASE1_H
#define CLASE1_H

#include <iostream>

using namespace std;

class arbol{
public:
  int valor;
  int hojas;

  arbol(int, int);
  ~arbol();
  void print();
};

arbol::arbol(int value, int leaf){
  this->valor = value;
  this->hojas = leaf;
}

arbol::~arbol(){
}

void arbol::print(){
  cout<<"( "<<this->valor<<" ; "<<this->hojas<<" )"<<endl;
}

#endif
