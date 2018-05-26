#ifndef C_NODO_H
#define C_NODO_H

#include <iostream>
#include <vector>
#include "c_point.h"//Manejo de puntos para una dimension.
using namespace std;

template<class T, int D, int C>
extern vector< c_point<T, D> > arriba_derecha;

template<class T, int D, int C>
extern vector< c_point<T, D> > abajo_izquierda;


template<class T, int D, int C>//T data type, D data dimension, C puntos por nodos >= 4
class c_nodo{
public:
  bool is_leaf; //Determina si esuna hoja o un nodo de pasamos
  vector< c_point<T,D> > inner_points;
  //c_nodo<T, D, C>* region[C]; CAMBIADO POR VECTOR PARA UN MANEJO MAS INTUITIVO
  vector< c_nodo<T,D,C>* > region;//Empezamos con cero apuntadores.
  c_point<T, D> l_d; //left down, punto izquierdo inferior
  c_point<T, D> u_r; //right up punto derecho superior.
  int node_id;


  c_nodo();//Contructor por defecto
  c_nodo(c_point<T, D>); //Un unico punto en este nodo, actua de ambos limites.
  c_nodo(c_point<T, D>, c_point<T, D>);//Constructor con parametros para setear nuevos limites instantaneos
  ~c_nodo();

  ///FUNCIONES_PRIMARIAS.
  void add_point(c_point<T, D>); //Añadimos un punto en el almacen.
    void verified_both_ranges(c_point<T, D>);
  void add_region(c_nodo<T,D,C>*);
    void verified_region_ranges(c_nodo<T,D,C>*);

  void change_state();//Pasa el estado de hoja a rama y viceversa.
  bool right_number_of_menbers();//Verifica si aún se mantiene el numero permitido de puntos
  bool right_number_of_regions();//Verifica si aún mantiene un número correcto de regiones.
  ///FUNCIONES SECUNDARIAS.
  void print_nodo();
  void nodo_overview();
  void nodo_general_view();
  c_point<T,D> get_middle_point();

};

//constructor por defecto
template<class T, int D, int C>
c_nodo<T,D,C>::c_nodo(){
  c_point<T, D> temp;
  this->l_d = temp;//En el constructor por defecto ambos empiezan con punto igual a cero.
  this->u_r = temp;//En el constructor por defecto ambos empiezan con punto igual a cero.
  this->is_leaf = true; //Por defecto empieza como hoja
  this->node_id = 0;
}

template<class T, int D, int C>
c_nodo<T,D,C>::c_nodo(c_point<T,D> incoming_point){
  this->l_d = incoming_point;
  this->u_r = incoming_point;
  this->is_leaf = true;
  this->inner_points.push_back(incoming_point);//Starting this node with one point
  this->node_id = 0;
}


template<class T, int D, int C>
c_nodo<T, D, C>::c_nodo(c_point<T, D> _l_d, c_point<T, D> _u_r){
  this->l_d = _l_d; //Igualamos este limite a los parametro ingresantes.
  this->u_r = _u_r; //Igualamos este limite a los parametro ingresantes.
  this->is_leaf = true; //Siempre empezamos como hoja.
  this->node_id = 0;
}

template<class T, int D, int C>
c_nodo<T,D,C>::~c_nodo(){
}

////////////////////////FUNCIONES PRIMARIAS//////////////////////////
template<class T, int D, int C>
void c_nodo<T,D,C>::add_point(c_point<T, D> incoming_point){
    this->inner_points.push_back(incoming_point);
    this->verified_both_ranges(incoming_point);
}

template<class T, int D, int C>
void c_nodo<T,D,C>::verified_both_ranges(c_point<T,D> incoming_point){
  for(unsigned int i = 0; i < D; i++){
    if(l_d.p_data[i] > incoming_point.p_data[i]){
      l_d.p_data[i] = incoming_point.p_data[i];
    }
    if(u_r.p_data[i] < incoming_point.p_data[i]){
      u_r.p_data[i] = incoming_point.p_data[i];
    }
  }

  //añadiendo la regiones al grafico.
  arriba_derecha<T,D,C>.push_back(this->u_r);
  abajo_izquierda<T,D,C>.push_back(this->l_d);
}

template<class T, int D, int C>
void c_nodo<T,D,C>::add_region(c_nodo<T,D,C>* incoming_region){
  this->region.push_back(incoming_region);
  this->verified_region_ranges(incoming_region);
}

template<class T, int D, int C>
void c_nodo<T,D,C>::verified_region_ranges(c_nodo<T,D,C>* incoming_region){
  for(unsigned int i = 0; i < D; i++){
    if(l_d.p_data[i] > incoming_region->l_d.p_data[i]){
      l_d.p_data[i] = incoming_region->l_d.p_data[i];
    }
    if(u_r.p_data[i] > incoming_region->u_r.p_data[i]){
      u_r.p_data[i] = incoming_region->u_r.p_data[i];
    }
  }
}

template<class T, int D, int C>
void c_nodo<T,D,C>::change_state(){
  this->is_leaf = !is_leaf;
}

template<class T, int D, int C>
bool c_nodo<T,D,C>::right_number_of_menbers(){
  if(this->inner_points.size() <= C){
    return true;
  }
  else{
    return false;
  }
}

template<class T, int D, int C>
bool c_nodo<T,D,C>::right_number_of_regions(){
  if(this->region.size() <= C){
    return true;
  }
  else{
    return false;
  }
}

/////////////////////////FUNCIONES SECUNDARIAS///////////////////////////
template<class T, int D, int C>
void c_nodo<T,D,C>::print_nodo(){
  for(unsigned int i = 0; i < this->inner_points.size(); i++){
    cout<<inner_points[i]<<" ";
  }
  cout<<endl;
}

template<class T, int D, int C>
void c_nodo<T,D,C>::nodo_overview(){
  if(!this->is_leaf){
    cout<<"Rama de regiones"<<endl;
  }
  else{
    cout<<"Hoja de Datos"<<endl;
  }
}

template<class T, int D, int C>
c_point<T,D> c_nodo<T,D,C>::get_middle_point(){
  c_point<T, D> answer = middle_point(this->l_d, this->u_r);
  return answer;
}


template<class T, int D, int C>
void c_nodo<T,D,C>::nodo_general_view(){
  cout<<"l_d: "<<this->l_d<<endl;
  cout<<"u_r: "<<this->u_r<<endl;
  cout<<"Is_leaf: "<<this->is_leaf<<endl;
  cout<<"Right number of menbers: "<<this->right_number_of_menbers()<<endl;
  this->print_nodo();
}

#endif
