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
  vector<int> a;
  a.push_back(1);
  a.push_back(2);
  a.push_back(3);
  a.push_back(4);
  a.push_back(5);
  print_v(a);
  a.erase(a.begin()+0);
  print_v(a);
  a.erase(a.begin()+1-1);
  print_v(a);
  cout<<*a.end()<<endl;


}


//RESULTS: 372 mb for a million of ints an long ints, don't get it.
