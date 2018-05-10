#include <iostream>
#include <vector>

using namespace std;

void print_v(vector<int> x){
  for(unsigned int i = 0; i < x.size(); i++){
    cout<<x[i]<<" ";
  }
  cout<<endl;
}

vector<int> operator +(const vector<int> &a, const vector<int> &b){
  if(a.size() > b.size()){
    vector<int> answer(b.size(), 0);
    for(unsigned int i = 0; i < b.size(); i++){
        answer[i] = a[i] + b[i];
    }
    return answer;
  }
  else{
    vector<int> answer(a.size(), 0);
    for(unsigned int i = 0; i < a.size(); i++){
        answer[i] = a[i] + b[i];
    }
    return answer;
  }
}

class pair_{
public:
  int x;
  int y;
  pair_(int _x, int _y){
    this->x = _x;
    this->y = _y;
  }
  ~pair_(){};
};

int main(){
  pair_ p1(5,7);
  pair_ p2(6,8);
  pair_ p3(7,9);
  pair_ p4(8,10);

  vector< pair_ > a;
  a.push_back(p1);
  a.push_back(p2);
  a.push_back(p3);
  a.push_back(p4);

  cout<<(a.back()).x<<endl;
}


//RESULTS: 372 mb for a million of ints an long ints, don't get it.
