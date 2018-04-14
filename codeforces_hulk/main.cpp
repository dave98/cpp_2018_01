/*Dr. Bruce Banner hates his enemies (like others don't). As we all know, he can barely talk when he turns into the incredible Hulk. That's why he asked you to help him to express his feelings.

Hulk likes the Inception so much, and like that his feelings are complicated. They have n layers. The first layer is hate, second one is love, third one is hate and so on...

For example if n = 1, then his feeling is "I hate it" or if n = 2 it's "I hate that I love it", and if n = 3 it's "I hate that I love that I hate it" and so on.

Please help Dr. Banner.*/
#include <iostream>


using namespace std;

int main(){
  int feeling_cant;
  cin>>feeling_cant;


  string h = "I hate ";
  string h_1 = "I hate ";
  string l = "I love ";
  string s_c1 = "it ";
  string s_c2 = "that ";

  for(int i = 0; i <= feeling_cant; i++){
    if(i + 1 == feeling_cant){
      h = h + s_c1;
      cout<<h<<endl;
      return 0;
    }
    else{
      h = h + s_c2;
      if(i%2 == 1){
        h = h + h_1;
      }
      else{
        h = h + l;
      }
    }
  }
  return 0;
}
