#include <stdio.h>


void message_1(void){
  puts("Primera funcion de la libreria");
}

void message_2(void){
  puts("Segunda funcion de la libreria");
}

void message_3(void){
  puts("Tercera funcion de la libreria");
}

void __attribute__ ((constructor)) initLibrary(void){
  printf("Library is initialized\n");
}

void __attribute__((destructor)) cleanUpLibrary(void){
  printf("Library is exited\n");
}
