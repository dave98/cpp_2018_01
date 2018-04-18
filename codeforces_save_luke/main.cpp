/*Luke Skywalker got locked up in a rubbish shredder between two presses. R2D2 is already working on his rescue, but Luke needs to stay alive as long as possible.
 For simplicity we will assume that everything happens on a straight line, the presses are initially at coordinates 0 and L, and they move towards each other with
 speed v1 and v2, respectively. Luke has width d and is able to choose any position between the presses. Luke dies as soon as the distance between the presses is less than his width. Your task is to determine for how long Luke can stay alive.*/

 #include <iostream>

 using namespace std;

 //d ancho
 //L press location
 //v1, v2;

 int main(){
   double l_width;
   double press_l;
   double v1;
   double v2;
   cin>>l_width>>press_l>>v1>>v2;

   v1 = v1 + v2;
   press_l = press_l - l_width;

   press_l = press_l/v1;

   printf("%.20f", press_l);

   return 0;
 }
