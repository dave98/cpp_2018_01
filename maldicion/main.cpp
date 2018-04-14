#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <fstream>

using namespace std;

float g_aleatorios();

template <class T>
float get_distances(vector<T>, vector<T>);

template <class T>
void print_m(vector<vector<T> >);


int main(){
  //srand(time(NULL));
  int d, cant = 0;
  vector< vector<float> > data;

  float max_distance = -1;
  float min_distance = 2;
  float prom_distance = 0;

  //DATA IS SAVED IN(There must exit these files to save data obtained):
  fstream minus("data_min.txt", fstream::app);
  fstream normal("data_nor.txt", fstream::app);
  fstream max("data_max.txt", fstream::app);

  cout<<"Cantidad/Dimension: "<<endl;
  cin>>cant;
  cin>>d;

  cout<<"---------------------------"<<endl;

  for(int j = 0; j < cant; j++){
    vector<float> temp(d, 0.0);
    for(vector<float>::iterator i = temp.begin(); i != temp.end(); i++){
      *i = g_aleatorios();
    }
    data.push_back(temp);
  }

  //print_m(data);

  float tempo = 0.0;
  cant = 0;
  for(unsigned int i = 0; i < data.size(); i++){
    /*for(unsigned int j = 0; j < i; j++){
        cout<<get_distances(data[i], data[j])<<endl;
    }*/
    for(unsigned int j = i+1; j < data.size(); j++){
        //cout<<get_distances(data[i], data[j])<<endl;
        tempo = get_distances(data[i], data[j]);
        cant++;
        prom_distance = prom_distance + tempo;
        if(min_distance > tempo){min_distance = tempo;}
        if(max_distance < tempo){max_distance = tempo;}
    }
  }

  prom_distance = prom_distance/(cant);

  cout<<"Distancia minima: "<<min_distance<<endl;
  cout<<"Distancia maxima: "<<max_distance<<endl;
  cout<<"Distancia promedio: "<<prom_distance<<endl;

  minus<<d<<" "<<min_distance<<endl;
  normal<<d<<" "<<prom_distance<<endl;
  max<<d<<" "<<max_distance<<endl;

  minus.close(); normal.close(); max.close();

}
//Todo ha sido probado con 200 puntos

float g_aleatorios(){
    return (float)rand()/100000;
}

template <class T>
void print_m(vector< vector<T> > chariot){
  for(unsigned int i = 0; i < chariot.size(); i++){
    for(unsigned int j = 0; j < chariot[i].size(); j++){
      cout<<chariot[i][j]<<" ";
    }
    cout<<endl;
  }
}

template <class T>
float get_distances(vector<T> a, vector<T> b){//Ambos vectores son del mismo tamaño
  float distance= 0.0;
  for(unsigned int i = 0; i < a.size(); i++){
    distance = distance + pow((a[i] - b[i]), 2);
  }
  distance = sqrt(distance);
  return distance;
}
