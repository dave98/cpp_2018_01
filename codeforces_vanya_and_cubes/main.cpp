/*Vanya got n cubes. He decided to build a pyramid from them. Vanya wants to build the pyramid as follows: the top level of the pyramid must consist of 1 cube,
the second level must consist of 1 + 2 = 3 cubes, the third level must have 1 + 2 + 3 = 6 cubes, and so on. Thus, the i-th level of the pyramid must have 1 + 2 + ... + (i - 1) + i cubes.

Vanya wants to know what is the maximum height of the pyramid that he can make using the given cubes.*/

#include <iostream>

using namespace std;

int main(){
  int cubes_cant;
  cin>>cubes_cant;

  int i;
  int sumatoria = 0;//Used cubes
  for(i = 1; cubes_cant >= (i + sumatoria); i++){
    sumatoria = i+sumatoria;
    cubes_cant = cubes_cant - sumatoria;
  }
  cout<<--i<<endl;
}
