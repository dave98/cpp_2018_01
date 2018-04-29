#include <iostream>
#include <vector>
#include "c_r_tree.h"
#include "c_point.h" //Alllows me to interact with points of n dimensions
#include "c_nodo.h"


using namespace std;

int main(){

  vector<int> a(3, 20);// 5 datos con 20

  c_nodo<int, 4, 6> nodo_1;
  c_r_tree<int, 4, 6> tree_1;

  c_point<int, 4> b(a);
  //c_point<int, 4> c(b);
  //c_point<int, 4> d;
  //d = b + c;


  cout<<"b: "<<b<<endl;
  b = b/2;
  cout<<"b: "<<b<<endl;

  //cout<<"c: "<<c<<endl;
  //cout<<"d: "<<d<<endl;
  //cout<<"b+c: "<<b+c<<endl;

  return 0;
}
