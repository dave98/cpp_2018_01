#include <stdio.h>
#include "add.h"
#include "answer.h"
//#include "foo.h"


int main(void){
  //puts("This is a shared library test...");
  //foo();
  return 0;
  setSummand(5);
  printf("5 + 7 = %d\n", add(7));
  printf("And the answer is %d\n", answer());
  return 0;
}
