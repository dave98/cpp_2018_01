#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

using namespace std;

int main(){
  char linea[250];
  FILE* data;
  data = fopen("country.csv", "r");
  if(data == NULL){
    cout<<"No se pudo abrir el archivo"<<endl;
  }
  else{
    cout<<"El archivo abierto"<<endl;
  }
  while(!feof(data)){
    fgets(linea, 250, data);
    cout<<linea<<endl;
  }

  return 0;
}
