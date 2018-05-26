#ifndef C_NODO_H
#define C_NODO_H

#include <iostream>
#include <vector>
#include "c_point.h"//Manejo de puntos para una dimension.
#include <thread>
using namespace std;

template <class M>
class menor{
  bool evalua(M x, M y){
    return(x < y);
  }
};

template <class M>
class mayor{
  bool evalua(M x, M y){
    return(x > y);
  }
};

//Primer punto entrante se reacomoda a los rangos imppuesto por el segundo.
template <class P, int S, class F>
void compare_thread(c_point<P, S> &a, c_point<P,S> &b){
  F exchange;
  for(int i  = 0; i < S; i++){
    if(exchange.evalua(a.p_data[i], b.p_data[i])){
      a.p_data[i] = b.p_data[i];
    }
  }
}


////CLASE NODO///////////////////////////////////////////////////////////////////////////////

template<class T, int D, int C>//T data type, D data dimension, C puntos por nodos >= 4
class c_nodo{
public:
  bool is_leaf; //Determina si es una hoja o un nodo de paso.
  vector< c_point<T,D> > inner_points;//Mantiene la data
  vector< c_nodo<T,D,C>* > region;//Empezamos con cero apuntadores. Si es un nodo de paso, es una region con datos internos.
  c_nodo<T,D,C>* dad;//Puntero al origen del nodo.
  c_point<T, D> l_d; //left down, punto izquierdo inferior
  c_point<T, D> u_r; //right up punto derecho superior.

  int node_id;//Podríamos usar *this, pero el id hace mas util tratar con muchos nodos
              //Propuesto a eliminarse, es mucho espacio, aparte limita mucho mi cantidad de nodos permitidos.


  c_nodo();//Contructor por defecto
  c_nodo(c_point<T, D>); //Un unico punto en este nodo, actua de ambos limites.
  c_nodo(c_point<T, D>, c_point<T, D>);//Constructor con parametros para setear nuevos limites instantaneos
  ~c_nodo();


  ///FUNCIONES_PRIMARIAS.
  //VERIFICADAS->OPTIMIZADAS EN LO POSIBLE
  void add_point(c_point<T, D>); //Añadimos un punto en el almacen.
  void verified_both_ranges(const c_point<T, D>);
  void add_region(c_nodo<T,D,C>*);
  void add_region(c_nodo<T,D,C>*, bool);
    void verified_region_ranges(c_nodo<T,D,C>*);

  void change_state();//Pasa el estado de hoja a rama y viceversa.
  bool right_number_of_menbers();//Verifica si aún se mantiene el numero permitido de puntos
  bool right_number_of_regions();//Verifica si aún mantiene un número correcto de regiones.
  int right_leaf(const c_point<T,D>);//Funcionalidad que retorna la mejor region a la podemos saltar con el punto que ingresamos
  void nodo_select_picks(int* , int* );//Devuelve la posición de los puntos mas distantes dentro del inner_points
  void nodo_select_picks_region(int*, int*);//Devuelve las regiones mas distantes dentro de region
  ///FUNCIONES SECUNDARIAS.
  void print_nodo();
  void nodo_overview();
  void nodo_general_view();
  float nodo_get_area();//Simplifica el proceso de pedir el area en esta region
  float nodo_get_affected_area(const c_point<T, D>);//Retorna la supuesta area del nodo al ingresar un punto
  float nodo_get_affected_area_by_region(const c_nodo<T,D,C>&);//Retorna la supuesta area del nodo al ingresar una region nueva.
  c_point<T,D> get_middle_point();

};

//constructor por defecto
//PROBADO so so
template<class T, int D, int C>
c_nodo<T,D,C>::c_nodo(){
  this->is_leaf = true; //Por defecto empieza como hoja
  this->inner_points = vector< c_point<T, D> >(0, c_point<T,D>());//EVALUA. Primera forma
  this->region = vector< c_nodo<T,D,C>* >(0, NULL); //EVALUA, primera forma; //FIND BEST WAY
  this->dad = NULL;
  this->l_d = c_point<T,D>();//En el constructor por defecto ambos empiezan con punto igual a cero.
  this->u_r = c_point<T,D>();//En el constructor por defecto ambos empiezan con punto igual a cero.
  this->node_id = 0;
}

//Proved but can't be used automatically SO, SO
//It works perfectly in a vector enviroment. Don' know why
template<class T, int D, int C>
c_nodo<T,D,C>::c_nodo(c_point<T,D> incoming_point){
  this->is_leaf = true;
  this->inner_points = vector< c_point<T,D> >(1, incoming_point);//Starting the node with one point
  //this->inner_points.push_back(incoming_point);//Starting this node with one point
  this->region = vector< c_nodo<T,D,C>* >(0, NULL); //EVALUA, primera forma; //FIND BEST WAY
  this->dad = NULL;
  this->l_d = incoming_point;
  this->u_r = incoming_point;
  this->node_id = 0;
}

//Constructor muy limitado a el orden de ingresos en los puntos margenes.
//Proved: Works well but it needs a refactoring
/*
template<class T, int D, int C>
c_nodo<T, D, C>::c_nodo(c_point<T, D> _l_d, c_point<T, D> _u_r){
  this->is_leaf = true;//Siempre empezamos como hoja
  this->inner_points = vector< c_point<T,D> > (0, c_point<T, D>());
  this->region = vector< c_nodo<T,D,C>* >(0, NULL); //EVALUA, primera forma; //FIND BEST WAY
  this->dad = NULL;
  this->l_d = _l_d; //Igualamos este limite a los parametro ingresantes.
  this->u_r = _u_r; //Igualamos este limite a los parametro ingresantes.
  this->node_id = 0;
}
*/
//Now the order of incoming points is not important anymore. There is not differences applying a thread
template <class T, int D, int C>
c_nodo<T,D,C>::c_nodo(c_point<T,D> _l_d, c_point<T,D> _u_r){
  this->is_leaf = true;
  this->inner_points = vector<c_point<T,D> > (0, c_point<T,D>());
  this->region = vector< c_nodo<T,D,C>* > (0, NULL);
  this->dad = NULL;
  for(int i = 0; i < D; i++){
    if(_l_d.p_data[i] < _u_r.p_data[i]){
      this->l_d.p_data[i] = _l_d.p_data[i];
      this->u_r.p_data[i] = _u_r.p_data[i];
    }
    else{
      this->l_d.p_data[i] = _u_r.p_data[i];
      this->u_r.p_data[i] = _l_d.p_data[i];
    }
  }
  this->node_id = 0;
}


template<class T, int D, int C>
c_nodo<T,D,C>::~c_nodo(){
  this->inner_points.clear();
  this->region.clear();
}

////////////////////////FUNCIONES PRIMARIAS//////////////////////////
//Cumple la funcion de añadir un punto a la region. Nada más.
template<class T, int D, int C>
void c_nodo<T,D,C>::add_point(c_point<T, D> incoming_point){
    this->inner_points.push_back(incoming_point);
    this->verified_both_ranges(incoming_point);
}


template<class T, int D, int C>
void c_nodo<T,D,C>::verified_both_ranges(const c_point<T,D> incoming_point){
  for(unsigned int i = 0; i < D; i++){
    if(l_d.p_data[i] > incoming_point.p_data[i]){
      l_d.p_data[i] = incoming_point.p_data[i];
    }
    if(u_r.p_data[i] < incoming_point.p_data[i]){
      u_r.p_data[i] = incoming_point.p_data[i];
    }
  }
}




template<class T, int D, int C>
void c_nodo<T,D,C>::add_region(c_nodo<T,D,C>* incoming_region){
  this->region.push_back(incoming_region);
  //No hay necesidad de verificar la regiones puesto que estas derivaban de puntos que ya existían en el padre
  //ISSUES La afirmanción de arriba no es segura, revisala por favor
  //this->verified_region_ranges(incoming_region);
}

template<class T, int D, int C>
void c_nodo<T,D,C>::add_region(c_nodo<T,D,C>* incoming_region, bool review){
  this->is_leaf = false;//Si por lo menos existe un region ya somos un nodo de paso.
  if(review){
    this->region.push_back(incoming_region);
    this->verified_region_ranges(incoming_region);
  }
  else{
    this->region.push_back(incoming_region);
  }
}

template<class T, int D, int C>
void c_nodo<T,D,C>::verified_region_ranges(c_nodo<T,D,C>* incoming_region){
  for(unsigned int i = 0; i < D; i++){
    if(l_d.p_data[i] > incoming_region->l_d.p_data[i]){
      l_d.p_data[i] = incoming_region->l_d.p_data[i];
    }
    if(u_r.p_data[i] < incoming_region->l_d.p_data[i]){
      u_r.p_data[i] = incoming_region->l_d.p_data[i];
    }

    if(l_d.p_data[i] > incoming_region->u_r.p_data[i]){
      l_d.p_data[i] = incoming_region->u_r.p_data[i];
    }

    if(u_r.p_data[i] < incoming_region->u_r.p_data[i]){
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

template<class T, int D, int C>
int c_nodo<T,D,C>::right_leaf(const c_point<T,D> incoming_point){
  int answer = 0;//Por defecto, y ya salvando errores, saltamos a la regon 0
  float recursive_area = 0;//Guarda el area [a procesar](importante) si a esa region se le añade un punto
  float best_area = this->region[0]->nodo_get_affected_area(incoming_point) - this->region[0]->nodo_get_area();
  for(unsigned int i = 1; i < this->region.size(); i++){
    recursive_area = this->region[i]->nodo_get_affected_area(incoming_point) - this->region[i]->nodo_get_area();
    if(recursive_area <= best_area){
      best_area = recursive_area;
      answer = i;
    }
  }
  //EXPANDIREMOS el area de cada region por donde pasemos.
  this->verified_both_ranges(incoming_point);
  return answer;
}

template <class T, int D, int C>
void c_nodo<T,D,C>::nodo_select_picks(int* a, int *b){
  *a = 0;
  *b = 0;
  float min_distance_l_d = distance(this->l_d, this->inner_points[0]);
  float min_distance_u_r = distance(this->u_r, this->inner_points[0]);
  float tempo_area = 0.0;
  for(unsigned int i = 1; i < this->inner_points.size(); i++){//No uso C porque no sabemos en realidad cuantos puntos hay en la region
    tempo_area = distance(this->l_d, this->inner_points[i]);
    if(tempo_area <= min_distance_l_d){
      min_distance_l_d = tempo_area;
      *a = i;
    }
    tempo_area = distance(this->u_r, this->inner_points[i]);
    if(tempo_area <= min_distance_u_r){
      min_distance_u_r = tempo_area;
      *b = i;
    }
  }
  if(*a == *b){cout<<"Oye hay un error en nodo_select_picks ven a revisar."<<endl;}
}


template <class T, int D, int C>
void c_nodo<T,D,C>::nodo_select_picks_region(int* a, int* b){//a for l_d and b for u_r
  *a = 0;
  *b = 0;
  float min_distance_l_d = distance(this->l_d, this->region[0]->u_r);
  float min_distance_u_r = distance(this->u_r, this->region[0]->l_d);
  float tempo_area = 0.0;
  for(unsigned int i = 1; i < this->region.size(); i++){
    tempo_area = distance(this->l_d, this->region[i]->u_r);
    if(tempo_area <= min_distance_l_d){
      min_distance_l_d = tempo_area;
      *a = i;
    }
    tempo_area = distance(this->u_r, this->region[i]->l_d);
    if(tempo_area <= min_distance_u_r){
      min_distance_u_r = tempo_area;
      *b = i;
    }
  }
  if(*a == *b){cout<<"Oye hay un error en nodo_select_picks_region ven a revisar."<<endl;}
}

/////////////////////////FUNCIONES SECUNDARIAS///////////////////////////
template<class T, int D, int C>
void c_nodo<T,D,C>::print_nodo(){
cout<<"**************************DESCRIBIENDO NODO*************************"<<endl;
  cout<<"Es hoja: "<<(bool)this->is_leaf<<endl;
  cout<<"Puntos internos (cant): "<<this->inner_points.size()<<" listando -> "<<endl;
  for(unsigned int i = 0; i < this->inner_points.size(); i++){
    cout<<this->inner_points[i]<<" ";
  }
  cout<<endl;
  cout<<"Regiones internas (cant): "<<this->region.size()<<" listando -> "<<endl;
  for(unsigned int i = 0; i < this->region.size(); i++){
    cout<<this->region[i]<<endl;
  }
  cout<<endl;

  cout<<"Padre (pointer): "<<this->dad<<endl;
  cout<<"Margen izquierdo inferior (l_d): "<<this->l_d<<endl;
  cout<<"Margen derecho superior (u_r): "<<this->u_r<<endl;
  cout<<"Id del nodo: "<<this->node_id<<endl;
  cout<<"**************************FINALIZADO*************************"<<endl;
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

template <class T, int D, int C>
float c_nodo<T,D,C>::nodo_get_area(){
  //funcion en el archivo de Puntos
  return area_n_dimension(this->l_d, this->u_r);
}

template <class T, int D, int C>
float c_nodo<T,D,C>::nodo_get_affected_area(const c_point<T,D> incoming_point){//Area affected by a point
  c_point<T,D> _l_d = this->l_d;
  c_point<T,D> _u_r = this->u_r;
  for(int i = 0; i < D; i++){
    if(_l_d.p_data[i] > incoming_point.p_data[i]){
      _l_d.p_data[i] = incoming_point.p_data[i];
    }
    if(_u_r.p_data[i] < incoming_point.p_data[i]){
      _u_r.p_data[i] = incoming_point.p_data[i];
    }
  }
  return area_n_dimension(_l_d, _u_r);
}

template <class T, int D, int C>
float c_nodo<T,D,C>::nodo_get_affected_area_by_region(const c_nodo<T,D,C>& incoming_region){
  c_point<T,D> _l_d = this->l_d;
  c_point<T,D> _u_r = this->u_r;
  for(int i = 0; i < D; i++){
    if(_l_d.p_data[i] > incoming_region.l_d.p_data[i]){
      _l_d.p_data[i] = incoming_region.l_d.p_data[i];
    }
    if(_u_r.p_data[i] < incoming_region.l_d.p_data[i]){
      _u_r.p_data[i] = incoming_region.l_d.p_data[i];
    }

    if(_l_d.p_data[i] > incoming_region.u_r.p_data[i]){
      _l_d.p_data[i] = incoming_region.u_r.p_data[i];
    }
    if(_u_r.p_data[i] < incoming_region.u_r.p_data[i]){
      _u_r.p_data[i] = incoming_region.u_r.p_data[i];
    }
  }
  return area_n_dimension(_l_d, _u_r);
}



#endif
