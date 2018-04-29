#ifndef C_NODO_H
#define C_NODO_H

#include <iostream>
#include <vector>
#include "c_point.h"//Manejo de puntos para una dimension.
using namespace std;

template<class T, int D, int C>//T data type, D data dimension, C puntos por nodos >= 4
class c_nodo{
public:
  vector< c_point<T, D> > inners_points;//Podemos usar el size para ver los datos almacenados
  bool state; //Indica si este nodo almancena ono datos, true si lo hace, false solo de paso
  c_point<T, D> l_d;//Izquierda inferior
  c_point<T, D> u_r;//Margen derecha superior, espero quedos datos abarquen la gran mayoria.
  c_nodo* hijos[C];


//BASIC FUNCTIONS
  c_nodo();//Empezamos con una lista vacia, no tenemos limites.
  c_nodo(c_point<T, D>, c_point<T, D>);//Empezamos con una lista vacia, pero esta vez los límites si existen
  ~c_nodo();

//Primary functions
  void add_point(c_point<T, D>);//Añadimos un punto como tal
  void node_split();
  void print_nodo();

//Secondary functions
  void polarize_l_d(c_point<T, D>);//Accede directamente a l_d, INECESARIO
  void polarize_u_r(c_point<T, D>);//Accede directamente a u_R, INECESARIO
};

template <class T, int D, int C>
c_nodo<T,D,C>::c_nodo(){
  vector< c_point<T,D> > a;//Por defecto es vacío
  this->inners_points = a;//Iniciamos vacio el nodo;
  this->state = true; //Somos una hoja que va a contener datos
  for(int i = 0; i < C; i++){
      this->hijos[i] = NULL;
  }
}

template <class T, int D, int C>
c_nodo<T,D,C>::c_nodo(c_point<T,D> _l_d, c_point<T,D> _u_r){
  vector< c_point<T,D> > a;//Por defecto tenemos un vector vacio
  this->inners_points = a;
  this->state = true;//Iniciamos como una hoja
  this->l_d = _l_d;//Definimos el margen inferior de nuestra n-region
  this->u_R = _u_r;//Definimos el margen superior derecho como limite para nuestra region;
  for(int i = 0; i < C; i++){
    this->hijos[i] = NULL;
  }
}

template <class T, int D, int C>
c_nodo<T,D,C>::~c_nodo(){
}

//Añade un punto a nuestro array de puntos, además modifica los limites en la area de este
//rectangulo. Ah por cierto, cada nodo representaun rectángulo.
//De momento solo crece, el area incrementara si asi lo requiere
template <class T, int D, int C>
void c_nodo<T,D,C>::add_point(c_point<T, D> a){
  if(inners_points.size == 0){//El primer punto es en si un rectangulo
    this->u_r = a;
    this->d_l = a;
  }
  else{
    this->polarize_l_d(a);//Con esto actualizamos la informacion en ambos extremos.
    this->polarize_u_r(a);//Con esto actualizamos la informacion en ambos extremos.
  }

  if(this->state){
    this->inners_points.push_back(a);//Punto añadido.

    if(this->inners_points.size() >= C){//S sobrepasamos el limite en nuestro almacenamiento
      this->node_split();
    }
  }

}

template <class T, int D, int C>
void c_nodo<T,D,C>::print_nodo(){
  if(this->inners_points.size() != 0){
    for(unsigned int i = 0; i < this->inners_points.size(); i++){
      cout<<this->inners_points[i]<<" ";
    }
    cout<<endl;
  }
}

template <class T, int D, int C>
void c_nodo<T,D,C>::node_split(){
  this->state = false;//Ahora solo somos una hoja de paso.
  for(unsigned int i = 0; this->inners_points.size() != 0; ){//Van a existir mas de cuatro puntos, SIEMPRE
    float rundance_distance = 0;
    int stop = 0;
    for(unsigned int j = i+1; j < this->inners_points.size(); j++){
      
    }
  }
  this->inners_points.empty();
}

//UNnecessary functions, no borrar//////////////////////////////////////////////////////////:
template <class T, int D, int C>
void c_nodo<T,D,C>::polarize_l_d(c_point<T,D> incoming){
  for(unsigned int i = 0; i < D; i++){
    if(this->l_d.p_data[i] > incoming.p_data[i]){
      this->l_d.p_data[i] = incoming.p_data[i];
    }
  }
}

template <class T, int D, int C>
void c_nodo<T,D,C>::polarize_u_r(c_point<T, D> incoming){
  for(unsigned int i = 0; i < D; i++){
    if(this->u_r.p_data[i] < incoming.p_data[i]){
      this->l_d.p_data[i] = incoming.p_data[i];
    }
  }
}



#endif
