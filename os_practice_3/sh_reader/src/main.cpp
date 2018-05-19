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
  //if((shmid = shmget(key, SHMZ, IPC_EXCL)) < 0){
    perror("shmget");
    exit(1);//No se pudo crear la shared memory.
  }

  if((shm = (char*)shmat(shmid, NULL, 0)) == (char*)-1){
    perror("shmat");
    exit(1);
  }

  for(s = shm; *s != NULL; s++){
    *s = NULL;
  }

  cout<<"An intance of a shared memory has been added."<<endl;

  /*while(true){
    for(s = shm; *s != NULL; s++){
      cout<<*s<<" , ";
    }
    cout<<endl<<endl;
    //sleep(2);
  }*/

  while(true){
    s = shm;
    if(*s != NULL){
      for(; *s != NULL; s++){
        cout<<*s<<" , ";
        //*s = NULL;
      }
      cout<<endl;
      //s = shm; *s = NULL;
    }

  }


  return 0;
}
