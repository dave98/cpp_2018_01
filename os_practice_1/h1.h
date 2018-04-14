#ifndef H1_H
#define H1_H

#include <iostream>
using namespace std;


template <class T>
class punto{
public:
  T x;
  T y;
  string inner_data;

  punto(T, T);
  ~punto();

  void set_new_punto(T, T);
  void set_data(string);
  T get_x();
  T get_y();
  string get_data();
};


#endif
