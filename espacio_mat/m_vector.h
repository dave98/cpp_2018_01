#ifndef M_VECTOR_H
#define M_VECTOR_H

#include <iostream>
#include <vector>

using namespace std;

template <class T>
class m_vector{
public:
  int quantity;
  vector<T> inner_data;

  m_vector(int);
  void insert_data();
  ~m_vector();

  m_vector<T>& operator = (const m_vector<T> &x);

  template <class P>
  friend ostream& operator << (ostream &o, const m_vector<P> &x);

  template <class P>
  friend istream& operator >> (istream &o, m_vector<P> &x);
};

//OUTER EXPRESSION //////////////////////////////////////////////////////////////////////
template <class P>
m_vector<P> operator + (const m_vector<P>&, const m_vector<P>&);

template <class P>
m_vector<P> operator * (const int&, const m_vector<P>&);

/////////////////////////////////////////////////////////////////////////////////////////

template <class T>
void m_vector<T>::insert_data(){
  cout<<"Nuevo vector de "<<this->quantity<<" puntos:"<<endl;
  for(unsigned int i  = 0; i < this->inner_data.size(); i++){
    cin>>inner_data[i];
  }
}

template <class T>
m_vector<T>::m_vector(int coming){
  this->quantity = coming;
  this->inner_data = vector<T>(coming, 0);
}

template <class T>
m_vector<T>::~m_vector(){}

//OUTER EXPRESSION ///////////////////////////////////////////////////////////////////////

template <class P>
ostream& operator << (ostream &o, const m_vector<P> &x){
  o << "(" << x.inner_data[0];
  for(unsigned int i = 1; i < x.inner_data.size(); i++){
    o << ";"<< x.inner_data[i];
  }
  o << ")";
  return o;
}

template <class P>
istream& operator >> (istream &o, m_vector<P> &x){
  x.insert_data();
  return o;
}

template <class P>
m_vector<P> operator + (const m_vector<P> &a, const m_vector<P> &b){
  int range = a.quantity;
  m_vector<P> answer(range);
  for(int i = 0; i < range; i++){
    answer.inner_data[i] = a.inner_data[i] + b.inner_data[i];
  }
  return answer;
}

template <class P>
m_vector<P> operator * (const int &a, const m_vector<P> &b){
  int range = b.quantity;
  m_vector<P> answer(range);
  for(int i = 0; i < range; i++){
    answer.inner_data[i] = b.inner_data[i] * a;
  }
  return answer;
}

template <class T>
m_vector<T>& m_vector<T>::operator = (const m_vector<T> &x){
  if(this != &x){
    this->quantity = x.quantity;
    this->inner_data = x.inner_data;
  }
  return *this;
}
//////////////////////////////////////////////////////////////////////////////////////////
#endif
