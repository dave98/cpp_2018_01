#include <iostream>
#include "m_vector.h"
#include "m_matriz.h"
#include "ecuaciones.h"

using namespace std;

int main(){
  int n_1 = 10;
  cout<<"Integer: "<<n_1<<endl;

  cout<<"VECTORES R2"<<endl;
  m_vector<int> v_a(2);
  cin >> v_a;

  m_vector<int> v_b(2);
  cin >> v_b;

  m_vector<int> v_c(2);
  v_c = v_a + v_b;

  cout<<"(a + b): "<<v_a<< " + "<<v_b<<" = "<<v_c<<endl;
  cout<<"n * c: "<< n_1 * v_c<<endl;
  //cout<<"Multi n_1 * a: "<<n_1 * a<<endl;

  cout<<"MATRICES"<<endl;
  m_matriz<int> m_a(2);
  cin>>m_a;

  m_matriz<int> m_b(2);
  cin>>m_b;

  m_matriz<int> m_c(2);
  m_c = m_a + m_b;
  cout<<"a + b: "<<endl<<m_a<<endl<< " + "<<endl<<m_b<<endl<<" = "<<endl<<m_c<<endl;
  cout<<"n * c:"<<endl<<n_1*m_c <<endl;

  cout<<"ECUACIONES"<<endl;

  ecuaciones a("x^2 + y");
  cin>>a;

  ecuaciones b("x^3 + y");
  cin>>b;

  cout<<a + b<<endl;

}
