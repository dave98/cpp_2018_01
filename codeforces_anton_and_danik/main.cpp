/*Anton likes to play chess, and so does his friend Danik.

Once they have played n games in a row. For each game it's known who was the winner — Anton or Danik. None of the games ended with a tie.

Now Anton wonders, who won more games, he or Danik? Help him determine this.*/

#include <iostream>

using namespace std;

int main(){
  int games_cant;
  string score;

  cin>>games_cant;
  cin>>score;
  int a = 0;
  int d = 0;
  for(int i = 0; i < games_cant; i++){
    if(score[i] == 'A'){
      a++;
    }
    else{
      d++;
    }
  }
  if(a == d){cout<<"Friendship"<<endl;}
  else{
    if(a>d){
      cout<<"Anton"<<endl;
    }
    else{
      cout<<"Danik"<<endl;
    }
  }
  return 0;
}
