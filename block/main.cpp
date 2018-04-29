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

int main(){

  vector<int> a(4, 100);
  vector<int> b(2, 22);

  a = b;
  print_v(a);
  cout<<"  "<<a.size()<<endl;


/*
  if(a == b){
    cout<<"True"<<endl;
  }
  else{
    cout<<"False"<<endl;
  }
*/

}


//RESULTS: 372 mb for a million of ints an long ints, don't get it.
