/*
One day n friends gathered together to play "Mafia". During each round of the game some player must be the supervisor and other n - 1 people take part in the game.
For each person we know in how many rounds he wants to be a player, not the supervisor: the i-th person wants to play ai rounds.
What is the minimum number of rounds of the "Mafia" game they need to play to let each person play at least as many rounds as they want?*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
  int player_cant;
  vector<int> player_wishes;
  vector<int>::iterator max;

  cin>>player_cant;
  for(int i = 0; i < player_cant; i++){
    int tempo;
    cin>>tempo;
    player_wishes.push_back(tempo);
  }

  max = max_element(player_wishes.begin(), player_wishes.end());
  cout<<(*max) + 1<<endl;

  return 0;
}
