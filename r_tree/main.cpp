#include <iostream>
#include <vector>
#include "c_r_tree.h"
#include "c_point.h" //Alllows me to interact with points of n dimensions
#include "c_nodo.h"

//CREATED BY jose david mamani vilca. jose.mamani.vilca@ucsp.edu.pe

const int dimension = 2;
const int cant_per_node = 4;

using namespace std;

int main(){
  bool continue_ = true;
  char answer;
  c_r_tree<int, dimension, cant_per_node> arbol ;


  while(continue_){
      c_point<int, 2> temp;
      cout<<"Insertar punto y/n: ";
      cin>>answer;

      if(answer ==  'y'){
        cout<<"Coordenadas del punto, 2 dimensiones: "<<endl;
        cin>>temp;
        arbol.insert(temp);
      }
      else{
        continue_=false;
      }
  }
  continue_ = true;
  while(continue_){
    c_point<int, 2> temp;
    cout<<"Buscar punto y/n: ";
    cin>>answer;

    if(answer == 'y'){
      cout<<"Inserte punto a buscar"<<endl;
      cin>>temp;
      arbol.search(temp);
    }
    else{
      continue_ = false;
    }
  }

/*
  c_r_tree<int, 2, 4> primer_arbol;

  c_point<int, 2> p_1;
  c_point<int, 2> p_2;
  c_point<int, 2> p_3;
  c_point<int, 2> p_4;
  c_point<int, 2> p_5;


  cin>>p_1;
  cin>>p_2;
  cin>>p_3;
  cin>>p_4;
  cin>>p_5;

  cout<<"Todos los puntos listos: "<<p_1<<" "<<p_2<<" "<<p_3<<" "<<p_4<<" "<<p_5<<endl;
  primer_arbol.insert(p_1);
  primer_arbol.insert(p_2);
  primer_arbol.insert(p_3);
  primer_arbol.insert(p_4);
  primer_arbol.insert(p_5);
*/
  return 0;
}
