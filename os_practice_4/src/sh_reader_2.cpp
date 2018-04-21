#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>

using namespace std;

#define SHMZ 30


#define SERVER_QUEUE_NAME   "/sp-example-server"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 20
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10


int main(){
  int shmid;
  key_t key;
  char *shm, *s;
  string message;
  key = 5050;
  if((shmid = shmget(key, SHMZ, 0666)) < 0){
    perror("shmget");
    exit(1);//No se pudo crear la shared memory.
  }
  if((shm = (char*)shmat(shmid, NULL, 0)) == (char*)-1){
    perror("shmat");
    exit(1);
  }
  cout<<"An intance of a shared memory has been added."<<endl;

/////queue SECTION //////////////////////////////////////////////////
  mqd_t qd_server, qd_client;   // queue descriptors
  int token_number=1; // next token to be given to client
  struct mq_attr attr;

  attr.mq_flags = 0;
  attr.mq_maxmsg = MAX_MESSAGES;
  attr.mq_msgsize = MAX_MSG_SIZE;
  attr.mq_curmsgs = 0;

  if ((qd_server = mq_open (SERVER_QUEUE_NAME, O_RDONLY | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1) {
    perror ("Server: mq_open (server)");
    exit (1);
  }

  char in_buffer [MSG_BUFFER_SIZE];
  char out_buffer [MSG_BUFFER_SIZE] = "";

/////////////////////////////////////////////////////////////////////
  while(true){
    message = ""; //Captura el mensaje completo desde el shared memory
    for(s = shm; *s != NULL; s++){
      //cout<<*s;
      message = message + *s;
      *s = NULL;
    }
  /////////////////////////////////
    if (mq_receive (qd_server, in_buffer, MSG_BUFFER_SIZE, NULL) == -1) {
        perror ("Server: mq_receive");
        exit (1);
    }
    if ((qd_client = mq_open (in_buffer, O_WRONLY)) == 1) {
        perror ("Server: Not able to open client queue");
        continue;
    }

    for(unsigned int i = 0; i < message.size(); i++){
      out_buffer[i] = (char)message[i];
    }

    cout<<out_buffer<<endl;

    if (mq_send (qd_client, out_buffer, strlen(out_buffer), 0) == -1) {
        perror ("Server: Not able to send message to client");
        continue;
    }
    //strcpy(out_buffer, "");
    token_number++;
    sleep(1);
  }

  if (mq_close (qd_client) == -1) {
      perror ("Client: mq_close");
      exit (1);
  }

  exit (0);
}
