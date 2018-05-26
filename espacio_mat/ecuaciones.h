#ifndef ECUACIONES_H
#define ECUACIONES_H

#include <iostream>

using namespace std;

class ecuaciones{
public:
  string expression;
  ecuaciones(string);
  void set_data();
  ~ecuaciones();

  ecuaciones operator = (const ecuaciones &x);

  friend ostream& operator << (ostream &o, const ecuaciones &x);
  friend istream& operator >> (istream &o, ecuaciones &x);
};

ecuaciones operator + (const ecuaciones &a, const ecuaciones &b);
ecuaciones operator * (const string &a, const ecuaciones &b);
string parentesis(string);

//DESARROLLO///////////////////////////////////////////////////////////////////////////
ecuaciones::ecuaciones(string incoming_data){
  this->expression = incoming_data;
}

void ecuaciones::set_data(){
  cout<<"Nueva funcion: "<<endl;
  cin>>this->expression;
}

ostream& operator << (ostream &o, const ecuaciones &x){
  o << x.expression;
  return o;
}

istream& operator >> (istream &o, ecuaciones &x){
  x.set_data();
  return o;
}

ecuaciones::~ecuaciones(){}


//OVERLOAD OPERATORS///////////////////////////////////////////////////////////////////
ecuaciones ecuaciones::operator = (const ecuaciones &x){
  if(this != &x){
    this->expression = x.expression;
  }
  return *this;
}

ecuaciones operator + (const ecuaciones &a, const ecuaciones &b){
  string answer = parentesis(a.expression) + " + " + parentesis(b.expression);
  return ecuaciones(answer);
}

ecuaciones operator * (const string &a, const ecuaciones &b){
  string answer = a + "*" + b.expression;
  return ecuaciones(answer);
}

string parentesis(string coming){
  string answer = "(" + coming + ")";
  return answer;
}
#endif
