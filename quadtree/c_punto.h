#ifndef C_PUNTO_H
#define C_PUNTO_H

#include <iostream>

using namespace std;

class c_punto{
public:
  float x;
  float y;

  c_punto();
  c_punto(float, float);
  void set_p(float, float);
  ~c_punto();

  bool operator == (const c_punto &exe) const;
};

c_punto::c_punto(){
  this->x = 0;
  this->y = 0;
}
c_punto::c_punto(float _x, float _y){
  this->x = _x;
  this->y = _y;
}

void c_punto::set_p(float _x, float _y){
  this->x = _x;
  this->y = _y;
}

bool c_punto::operator == (const c_punto &exe) const{
  if(this->x == exe.x and this->y == exe.y){
    return true;
  }
  else{
    return false;
  }
}

c_punto::~c_punto(){}
#endif
