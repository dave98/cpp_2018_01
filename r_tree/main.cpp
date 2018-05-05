#include <iostream>
#include <vector>
#include "c_r_tree.h"
#include "c_point.h" //Alllows me to interact with points of n dimensions
#include "c_nodo.h"


using namespace std;

int main(){
  c_r_tree<int, 2, 4> primer_arbol;

  c_point<int, 2> p_1;
  c_point<int, 2> p_2;
  c_point<int, 2> p_3;
  c_point<int, 2> p_4;


  cin>>p_1;
  cin>>p_2;
  cin>>p_3;
  cin>>p_4;

  cout<<"Todos los puntos listos: "<<p_1<<" "<<p_2<<" "<<p_3<<" "<<p_4<<endl;
  primer_arbol.insert(p_1);
  primer_arbol.insert(p_2);
  primer_arbol.insert(p_3);
  primer_arbol.insert(p_4);



/*
  c_point<int, 4> a_point;
  cin>>a_point;

  c_point<int, 4> b_point;
  cin>>b_point;

  c_nodo<int, 4, 5> a(a_point);
  a.nodo_general_view();
  a.add_point(b_point);
  a.nodo_general_view();
  a.add_point(b_point);
  a.add_point(b_point);
  a.add_point(b_point);
  a.add_point(b_point);

  a.nodo_general_view();
*/

  return 0;
}
