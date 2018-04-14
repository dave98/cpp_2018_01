#include <iostream>
#include <dlfcn.h>
#include "h1.h"
#include "sanpa.h"

using namespace std;

 int main(int argc, char **argv){
   cout<<"Hello world"<<endl;

   cout<<"Starting uses of a dynamic library"<<endl;
   void* handle = dlopen("sanpa.dll", RTLD_LAZY);

   sanpa* (*create)();
   void (*destroy)(sanpa*);

   create = (sanpa* (*)())dlsym(handle, "create_object");
   destroy = (void (*)(sanpa*))dlsym(handle, "destroy_object");

   sanpa* my_sanpa = (sanpa*)create();
   my_sanpa->do_something();
   destroy(my_sanpa);

   cout<<"Done"<<endl;
   cout<<"Starting uses of a static library"<<endl;


   punto<int> a(1, 2);
   a.set_data("primer punto");

   cout<<"( "<<a.get_x()<<"; "<<a.get_y()<<") -> "<<a.get_data()<<endl;

   return 0;
}
