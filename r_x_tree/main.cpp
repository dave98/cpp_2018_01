#include <iostream>
#include <math.h>
#include <vector>
#include "c_r_tree.h"
#include "c_point.h" //Alllows me to interact with points of n dimensions
#include "c_nodo.h"
#include <ctime>
#include <fstream>

//CREATED BY jose david mamani vilca. jose.mamani.vilca@ucsp.edu.pe

using namespace std;

void read_document(c_r_tree<float, 2, 3>*);

int main(){
  //vector <c_point<int, 2> > record;
  c_r_tree<float, 2, 3> a_a;
  //ofstream myfile;
  //myfile.open("ruta.txt");

  /*while(true){
    c_point<int, 2> tempo;
    cout<<"Inserte datos"<<endl;
    cin>>tempo;
    a_a.insert(tempo);
    //myfile<<tempo.p_data[0]<<" ; "<<tempo.p_data[1]<<endl<<flush ;
    //record.push_back(tempo);
    //for(unsigned int i = 0; i < record.size(); i++){
      //cout<<record[i]<<" ";
    //}
    //cout<<endl;
  }
  //myfile.close();
  */
  read_document(&a_a);
  cout<<"Lectura finalizada"<<endl;
  return 0;
}

void read_document(c_r_tree<float, 2, 3>* tree){
  int counter = 0;
  float x, y;
  char txt_name[20];
  cout<<"Nombre del archivo"<<endl;
  cin>>txt_name;

  fstream reader(txt_name, ios::in);

  while(reader>>x and reader>>y){
    //cout<<"Insertando"<<x<<" - "<<y<<endl;
    vector<float> tiran(1, x); tiran.push_back(y);
    c_point<float, 2> tempo(tiran);
    tree->insert(tempo);
    counter++;
  }
  cout<<"Existen "<<tree->tree_records_number<<" de datos"<<endl;
  cout<<"Datos leidos: "<<counter<<endl;
}




/*
c_r_tree<int, 2, 3> a_a;
while(true){
  c_point<int, 2> tempo;
  cout<<"Inserte datos"<<endl;
  cin>>tempo;
  a_a.insert(tempo);
}
*/

/* EVALUATING HIGH AMOUNT OF POINTS
  char a;
  t0 = clock();
  vector< c_point<int, 90> > v_a(500000, c_point<int,90>(true));
  t1 = clock();

  double time = (double(t1-t0)/CLOCKS_PER_SEC);
  cout << "Execution Time: " << time << endl;
  cin>>a;
*/

//Es equivalente al tratamiento con puro vector:
// cien mil puntos 90 dimensiones: 0.049, 0.062, 0.058, 0.056
