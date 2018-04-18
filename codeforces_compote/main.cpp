/*Nikolay has a lemons, b apples and c pears. He decided to cook a compote. According to the recipe the fruits should be in the ratio 1: 2: 4.
It means that for each lemon in the compote should be exactly 2 apples and exactly 4 pears. You can't crumble up, break up or cut these fruits into pieces.
These fruits — lemons, apples and pears — should be put in the compote as whole fruits.
Your task is to determine the maximum total number of lemons, apples and pears from which Nikolay can cook the compote. It is possible that Nikolay can't use any fruits, in this case print 0.*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
  int lemons; //1
  int apples; //2
  int pears;  //4
  vector<int> rests;
  vector<int>::iterator min;

  cin>>lemons>>apples>>pears;

  rests.push_back(lemons);
  rests.push_back((int)(apples/2));
  rests.push_back((int)(pears/4));

  min = min_element(rests.begin(), rests.end());

  cout<<(*min)+(*min*2)+(*min*4)<<endl;

  return 0;
}
