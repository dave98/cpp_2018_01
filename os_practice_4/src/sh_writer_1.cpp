#include <iostream>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <mqueue.h>

using namespace std;
#define SHMSZ 30

int main(){
  int shmid;
  key_t key;
  char *shm, *s;
  string message;

  key = 5050;
  if((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0){
    perror("shmget");
    exit(1);//No se pudo crear la shared memory.
  }

  if((shm = (char*)shmat(shmid, NULL, 0)) == (char*)-1){
    perror("shmat");
    exit(1);
  }
  s = shm;

  while(true){
    cin>>message;
    for(unsigned int i = 0; i < message.size(); i++){
      *s = NULL;
      *s++ = message[i];
    }
    s = shm;
    message.empty();
    sleep(1);
  }
  return 0;
}
