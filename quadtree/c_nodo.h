#ifndef C_NODO_H
#define C_NODO_H

#include <iostream>
#include "c_punto.h"

using namespace std;

class c_nodo{
public:
  c_nodo* hijos[4];
  //string info;
  float x;
  float y;
  c_punto dir;
  bool color; //verdadero = negro, falso = blanco

  c_nodo(float, float);
  ~c_nodo();

  void print();
};


c_nodo::c_nodo(float _x, float _y){
  this->x = _x;
  this->y = _y;
  this->color = false;
  this->dir.set_p(_x, _y);
  //this->dir = new c_punto(_x, _y);
}

void c_nodo::print(){
  cout<<"("<<this->x<<";"<<y<<")"<<endl;
}

c_nodo::~c_nodo(){}

#endif
