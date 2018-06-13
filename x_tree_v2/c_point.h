#ifndef C_POINT_H
#define C_POINT_H

#include <iostream>
#include <vector>
#include <math.h>
#include <cmath>

using namespace std;


template<class T, int O>//T indica el tipo de dato que sealamcena, S indica la cantidad de datos que hay en este punto
class c_point{
public:
  vector<T> p_data;

  c_point();
  c_point(vector<T>);
  c_point(const c_point<T, O> &x);
  c_point(bool);//Inicia el punto con datos aleatorios
  ~c_point();
  void set_random_point(int);//Permite setear en el punto valores aleatorios

  //Overload section: Interaction between points
  //+ sobrecarga afuera, dont´t know what happen when it's inside class.
  //c_point<T, O>& operator + (const c_point<T, O> &x);//Will work just with points in the same dimensions;
  bool operator == (const c_point<T, O> &x);
  c_point<T, O>& operator = (const c_point<T, O> &x);

  template <class S, int P>
  friend ostream& operator << (ostream &o, const c_point<S, P> &x);
  template <class S, int P>
  friend istream& operator >> (istream &o, c_point<S, P> &x);
};

//outer
template<class S, int P>
c_point<S, P> operator + (const c_point<S,P>&, const c_point<S,P>&);

template<class S, int P>
c_point<S, P> operator / (const c_point<S,P>&, const float&);

template<class S, int P>
float distance(const c_point<S, P>&, const c_point<S,P>&);

template<class S, int P>
float area_n_dimension(const c_point<S, P>&, const c_point<S, P>&);

template<class S, int P>
float area_n_dimension_no(const c_point<S, P>&, const c_point<S, P>&);

template<class S, int P>
c_point<S,P> middle_point(const c_point<S, P>&, const c_point<S, P>&);


template <class T, int O>
c_point<T,O>::c_point(bool incoming){
  this->p_data = vector<T>(O, (T)0);
  for(int i = 0; i < O; i++){
    this->p_data[i] = (T)(rand()%20 + 1);
  }
}

//No podemos perder la dimension de nuestros puntos
//EL PARAMETRO ES UN VECTOR QUE DEBERÍA SER EQUIVALENTE A LA DIMENSION DEL PUNTO
template <class T, int O>//Si le pasamos un dato de mayor dimension al interno dicho dato se verá recortado a esta nueva dimension
c_point<T, O>::c_point( vector<T> _point){
  this->p_data = vector<T>(O, (T)0);
  if(_point.size() < O){
    for(unsigned int i = 0; i < _point.size(); i++){
      this->p_data[i] = _point[i];
    }
  }else{
    for(unsigned int i = 0; i < O; i++){
      this->p_data[i] = _point[i];
    }
  }
}

//ESTE CONSTRUCTOR RECIBE UN PUNTO DE LA MISMA DIMENSION
template <class T, int O>//No hay necesidad de acortar nada, ambos estan en la misma dimension
c_point<T, O>::c_point(const c_point<T, O> &x){
  this->p_data = x.p_data;//Copiamos los datos incrustados en el punto entrante en nuestro punto
}

//CONSTRUCTOR POR DEFECTO. USAR SIN ARGUMENTOS, AGILIZA METODOS DE CREACION PASAJERA.
template <class T, int O>
c_point<T, O>::c_point(){
  this->p_data = vector<T>(O, (T)0);
}

//POR IMPLEMENTAR//
template<class T, int O>
c_point<T, O>::~c_point(){
  this->p_data.clear();
}


//La sobrecarga de igualdad en vectores retorna true sin contienen los mismos datos y el mismo tamaño
template <class T, int O>
bool c_point<T, O>::operator == (const c_point<T, O> &x){
  return (this->p_data == x.p_data);
}
/*
template <class T, int O>//Ambos puntos estan en la misma dimension.
c_point<T, O>& c_point<T, O>::operator + (const c_point<T, O> &x){
  for(unsigned int i = 0; i < this->p_data.size(); i++){
    this->p_data[i] += + x.p_data[i];
  }
  return *this;
}
*/
template <class T, int O>
c_point<T, O>& c_point<T, O>::operator = (const c_point<T, O> &x){
  if(this != &x){
      this->p_data = x.p_data;
  }
  return *this;
}

//BORRA PUNTOS INTERNOSS YCOLOCA NUEVOS DATOS
template <class T, int O>
void c_point<T,O>::set_random_point(int range){
  for(int i = 0; i < O; i++){
    this->p_data[i] = (T)(rand()%range + 1);
  }
}


template <class S, int P>
ostream& operator << (ostream &o, const c_point<S, P> &x){
  o << "(" << x.p_data[0];
  for(unsigned int i = 1; i < P; i++){
    o<<";"<<x.p_data[i];
  }
  o << ") ";
  return o;
}

template <class S, int P>
istream& operator >> (istream &o, c_point<S, P> &x){
  for(unsigned int i = 0; i < P; i++){
    o >> x.p_data[i];
    o.ignore();
  }
  return o;
}


//SOBRECARGAS EXTERNAS
template<class S, int P>
c_point<S, P> operator + (const c_point<S,P> &a, const c_point<S,P> &b){
  c_point<S, P> answer;
  for(unsigned int i = 0; i < P; i++){
    answer.p_data[i] = a.p_data[i] + b.p_data[i];
  }
  return answer;
}

template<class S, int P>
c_point<S, P> operator / (const c_point<S,P> &a, const float &b){
  c_point<S, P> answer;
  if(b != 0){
    for(unsigned int i = 0; i < P; i++){
      answer.p_data[i] = a.p_data[i] / b;
    }
    return answer;
  }
  else{
    answer = a;
    return answer;
  }
}

template<class S, int P>
float distance(const c_point<S, P> &a, const c_point<S,P> &b){
  float distancia = 0.0;
  for(unsigned int i = 0; i < P; i++){
    distancia = distancia + pow(a.p_data[i] - b.p_data[i], 2);
  }
  distancia = sqrt(distancia);
  return distancia;
}

//Ahora b tiene que ser el mayor
template<class S, int P>
float area_n_dimension(const c_point<S, P> &a, const c_point<S,P> &b){
  float area = b.p_data[0] - a.p_data[0];
  for(unsigned int i = 1; i < P; i++){
    area = area * (b.p_data[i] - a.p_data[i]);
  }
  //return abs(area);
  if(area < 0){
    cout<<"Aviso area_n_dimension esta regresando un valor negativo"<<endl;
  }
  return area;
}

//Ahora b tiene que ser el mayor
template<class S, int P>
float area_n_dimension_no(const c_point<S, P> &a, const c_point<S,P> &b){
  float area = 1.0;
  for(unsigned int i = 0; i < P; i++){
    //area = area + (a.p_data[i] * b.p_data[i]);
    area = area * (b.p_data[i] - a.p_data[i]);
  }
  return area;
}

template<class S, int P>
c_point<S,P> middle_point(const c_point<S, P> &a, const c_point<S, P> &b){
  c_point<S, P> answer = a + b;
  answer = answer/2;
  return answer;
}




#endif
