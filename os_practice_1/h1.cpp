#include "h1.h"

template <class T>
punto<T>::punto(T _x, T _y){
  this->x = _x;
  this->y = _y;
  this->inner_data="empty";
}

template <class T>
punto<T>::~punto(){}

template <class T>
void punto<T>::set_new_punto(T _x, T _y){
  this->x = _x;
  this->y = _y;
}

template <class T>
void punto<T>::set_data(string _data){
  this->inner_data = _data;
}

template <class T>
T punto<T>::get_x(){
  return this->x;
}

template <class T>
T punto<T>::get_y(){
  return this->y;
}

template <class T>
string punto<T>::get_data(){
  return this->inner_data;
}

template class punto<int>;
template class punto<float>;
