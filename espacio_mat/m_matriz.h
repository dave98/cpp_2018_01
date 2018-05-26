#ifndef M_MATRIZ_H
#define M_MATRIZ_H

#include <iostream>
#include <vector>

using namespace std;

//JUST WORK WITH CUADRATIC MATRIZ

template<class T>
class m_matriz{
public:
  vector< vector<T> > inner_data;
  int range;

  m_matriz(int);
  ~m_matriz();
  void insert_data();

  m_matriz<T>& operator = (const m_matriz<T> &x);
  template <class P>
  friend ostream& operator << (ostream &o, const m_matriz<P> &x);
  template <class P>
  friend istream& operator >> (istream &o, m_matriz<P> &x);
};

///EXTERN OVERLOADS//////////////////////////////////////////////////////////////////////////
template<class P>
m_matriz<P> operator + (const m_matriz<P> &a, const m_matriz<P> &b);

template <class P>
m_matriz<P> operator * (const int &a, const m_matriz<P> &b);

template <class P>
m_matriz<P> operator * (const m_matriz<P> &b, const int &a);
////////////////////////////////////////////////////////////////////////////////////////////


template <class T>
m_matriz<T>::m_matriz(int coming){
  this->range = coming;
  this->inner_data = vector< vector<T> >(coming, vector<T>(coming, 0));
}

template <class T>
void m_matriz<T>::insert_data(){
  cout<<"Nuevo matriz de "<<this->range * this->range<<" puntos:"<<endl;
  for(int i = 0; i < this->range; i++){
    for(int j = 0; j < this->range; j++){
      cin>>this->inner_data[i][j];
    }
  }
}

template <class T>
m_matriz<T>::~m_matriz(){}

//OUTER EXPRESSION////////////////////////////////////////////////////////////////////
template <class P>
ostream& operator << (ostream &o, const m_matriz<P> &x){
  for(int i = 0; i < x.range; i++){
    o << "("<<x.inner_data[i][0];
    for(int j = 1; j < x.range; j++){
      o << ";"<<x.inner_data[i][j];
    }
    o << ")"<<endl;
  }
  return o;
}

template <class P>
istream& operator >> (istream &o, m_matriz<P> &x){
  x.insert_data();
  return o;
}

//OVERLOAD EXPRESSIONS/////////////////////////////////////////////////////////////////
template <class T>
m_matriz<T>& m_matriz<T>::operator = (const m_matriz<T> &x){
  if(this != &x){
    this->range = x.range;
    for(int i = 0; i < x.range; i++){
      this->inner_data[i] = x.inner_data[i];
    }
  }
  return *this;
}

template <class P>
m_matriz<P> operator + (const m_matriz<P> &a, const m_matriz<P> &b){
  if(a.range != b.range){cout<<"Cannot make this operation"; return a;}
  else{
    m_matriz<P> answer(a.range);//Creamos el resultado que contendrá la respuesta
    for(int i = 0; i < a.range; i++){
      for(int j = 0; j < a.range; j++){
        answer.inner_data[i][j] = a.inner_data[i][j] + b.inner_data[i][j];
      }
    }
    return answer;
  }
}

template <class P>
m_matriz<P> operator * (const int &a, const m_matriz<P> &b){
  m_matriz<P> answer(b.range);//Creamos el resultado que contendrá la respuesta
  for(int i = 0; i < b.range; i++){
    for(int j = 0; j < b.range; j++){
      answer.inner_data[i][j] = a * b.inner_data[i][j];
    }
  }  return answer;
}

template <class P>
m_matriz<P> operator * (const m_matriz<P> &b, const int &a){
  m_matriz<P> answer(b.range);//Creamos el resultado que contendrá la respuesta
  for(int i = 0; i < b.range; i++){
    for(int j = 0; j < b.range; j++){
      answer.inner_data[i][j] = a * b.inner_data[i][j];
    }
  }  return answer;
}



#endif
