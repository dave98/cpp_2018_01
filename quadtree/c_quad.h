#ifndef C_QUAD_H
#define C_QUAD_H

#include <iostream>
#include "c_nodo.h"
#include "c_punto.h"

using namespace std;

class c_quad{
public:
  c_nodo* head;
  int counter;

  c_quad();
  ~c_quad();
  void insert(float, float);
  void show_data();
  int get_region(float, float, float, float);
  int get_region_v2(c_punto, c_punto);
};

c_quad::c_quad(){
  this->head = NULL;
  this->counter = 0;
}

c_quad::~c_quad(){}

void c_quad::insert(float _x, float _y){
  c_nodo** chariot = &this->head;
  c_nodo* n_nuevo = new c_nodo(_x, _y);

  while(*chariot != NULL){
    //chariot = &(*chariot->hijos[get_region_v2(chariot->dir, *n_nuevo->dir)];
    chariot = &(*chariot->hijos[0]);
  }
}
//Working with region : 0 -> r1, 1 -> r2, 2 -> r3, 3 -> r4
int c_quad::get_region(float x, float y, float _x, float _y){
  if(_y > y){
    if(_x < x){ return 0;}
    else{ return 1;}
  }
  else{
    if(_x < x){ return 2;}
    else{ return 3;}
  }
}

//Using class c_punto, b is looking for a position respect a
int c_quad::get_region_v2(c_punto a, c_punto b){
  if(b.y > a.y){
    if(b.x < a.x){return 0;}
    else{return 1;}
  }
  else{
    if(b.x < a.x){return 2;}
    else{ return 3;}
  }
}

void c_quad::show_data(){
  cout<<"Existen "<<this->counter<<" datos."<<endl;
}


#endif
