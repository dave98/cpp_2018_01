#include "sanpa.h"
#include <iostream>

using namespace std;

extern "C" sanpa* create_object(){
  return new sanpa;
}

extern "C" void destroy_object(sanpa* object){
  delete object;
}

sanpa::sanpa(){
  x = 25;
}

void sanpa::do_something(){
  cout<<x<<endl;
}
