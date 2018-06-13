#include <iostream>
#include "f_tree.h"
using namespace std;

int main(){
  f_tree<int> a;
  int temp_value = 0;
  char answer;
  int temp_id = 0;

  bool continue_ = true;
while(true){
  while(continue_){
    cout<<"Insert(Y/N)";
    cin>>answer;
    if(answer == 'y'){
      cout<<"Id: ";
      cin>>temp_id;
      cout<<"Value: ";
      cin>>temp_value;
      a.insert_data(temp_value, temp_id);
      a.print_tree();
    }
    else{
      continue_ = false;
    }
  }
continue_ = true;
//a.print_tree();
  while(continue_){
      cout<<"Undo(Y/N)";
      cin>>answer;
      if(answer == 'y'){
        cout<<"Id: ";
        cin>>temp_id;
        if(temp_id < 0){
          a.extensive_undo();
          a.print_tree();
        }
        else{
          a.undo(temp_id);
          a.print_tree();
        }
      }
      else{
        a.print_tree();
        continue_ = false;
    }
  }
  continue_ = true;
}

//a.print_tree();
/*  a.insert_data(1, 10);
  a.insert_data(4, 10);
  a.insert_data(2, 9);
  a.insert_data(6, 11);
  a.print_tree();
*/

  return 0;
}
