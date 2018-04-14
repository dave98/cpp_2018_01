#include <iostream>

#include "c_point.h"
#include "c_nodo.h"
#include "c_tree.h"

using namespace std;
//Este main esta estructurado para recibir txt con un formato unico, ver crimes.txt
//consola windows: a.exe < crimes.txt
int main(){
  int n_data;
  int l_data;
  c_tree arbol(50000);

  cin>>n_data;
  //cout<<"Se han insertado "<<n_data<<" elementos"<<endl;
  for(int i = 0; i < n_data; i++){
    float x, y;
    cin>>x;
    cin>>y;
    arbol.insert(x, y);
  }

  cout<<"El arbol ha sido creado con "<<arbol.numero_puntos<<" puntos."<<endl;

  cin>>l_data;
  for(int i = 0; i < l_data; i++){
    float x, y;
    cin>>x;
    cin>>y;
    arbol.find(x, y);
  }
  return 0;
}
