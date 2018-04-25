#include <iostream>
#include <vector>

using namespace std;
vector<int> values;

void f(int);
void swap(int&, int&);

int main(){
  int x; cin>>x;

  if(x == 1){cout<<1;}
  else{
    values.push_back(x);
    f(x-1);
    for(unsigned int i = 0; i < values.size(); i++){
        cout<<values[values.size()-1 - i]<<" ";
    }
  }


  return 0;
}

void f(int x){
  if(x == 1){
    values.push_back(x);
    swap(values[values.size()-1], values[values.size()-2]);
    return;
  }
  else{
    values.push_back(x);
    swap(values[values.size()-1], values[values.size()-2]);
    f(x-1);
  }
}


void swap(int &a, int &b){
  int c = a;
  a = b;
  b = c;
}
