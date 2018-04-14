/*A Ministry for Defense sent a general to inspect the Super Secret Military Squad under the command of the Colonel SuperDuper. Having learned the news, the colonel ordered to all n squad soldiers
to line up on the parade ground.

By the military charter the soldiers should stand in the order of non-increasing of their height. But as there's virtually no time to do that, the soldiers lined up in the arbitrary order.
However, the general is rather short-sighted and he thinks that the soldiers lined up correctly if the first soldier in the line has the maximum height and the last soldier has the minimum height.
Please note that the way other solders are positioned does not matter, including the case when there are several soldiers whose height is maximum or minimum. Only the heights of the first and the last soldier are important.

For example, the general considers the sequence of heights (4, 3, 4, 2, 1, 1) correct and the sequence (4, 3, 1, 2, 2) wrong.

Within one second the colonel can swap any two neighboring soldiers. Help him count the minimum time needed to form a line-up which the general will consider correct.*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool compare_1(int, int);
bool compare_2(int, int);


int main(){
  int soldier_number;
  vector<int> soldiers_height;

cin>>soldier_number;
for(int i = 0; i < soldier_number; i++){
  int k;
  cin>>k;
  soldiers_height.push_back(k);
}

int max_s = soldiers_height[0];
int min_s = soldiers_height[0];
int max_c = 0;
int min_c = soldiers_height.size();


  //recorremos a todos los soldados.
for(unsigned int i = 0; i < soldiers_height.size(); i++){
  if(soldiers_height[i] > max_s){
    max_s = soldiers_height[i];
    max_c = i;
  }
  if(soldiers_height[i] <= min_s){
    min_s = soldiers_height[i];
    min_c = soldiers_height.size() - i - 1;
  }
}

soldier_number = min_c + max_c;

if(soldier_number < (int)soldiers_height.size()){
  cout<<soldier_number<<endl;
}
else{
  cout<<--soldier_number<<endl;;
}

return 0;
}
