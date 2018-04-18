#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>

using namespace std;

#define SHMZ 27

int main(){
  int shmid;
  key_t key;
  char *shm, *s;

  key = 5678;

  if((shmid = shmget(key, SHMZ, 0666)) < 0){
    perror("shmget");
    exit(1);//No se pudo crear la shared memory.
  }

  if((shm = (char*)shmat(shmid, NULL, 0)) == (char*)-1){
    perror("shmat");
    exit(1);
  }
  cout<<"An intance of a shared memory has been added."<<endl;

  while(true){
    for(s = shm; *s != NULL; s++){
      cout<<*s<<" , ";  
    }
    cout<<endl;
    sleep(2);
  }


  return 0;
}
