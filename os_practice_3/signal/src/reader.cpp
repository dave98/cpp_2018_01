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


//This is our server
//net start cygserver

using namespace std;

#define MAX_BUF 1024
#define SHMSZ 27

//////////////queue///////////
#define SERVER_QUEUE_NAME   "/sp-example-server"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10

void analyze_data(int);
bool odds(int);

int main()
{
    int fd;
    char * myfifo = "/tmp/myfifo";
    char buf[MAX_BUF];
    int incoming_value = 0;
    char data;

//shared memory section///////////////////////////////////////////
    char c;
    int shmid;//Share memory id
    key_t key;//llave;
    char *shm, *s;


    key = 5678;
    if((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0){
      perror("shmget");
      exit(1);//No se pudo crear la shared memory.
    }


    if((shm = (char*)shmat(shmid, NULL, 0)) == (char*)-1){
      perror("shmat");
      exit(1);
    }
    cout<<"An intance of shared memory has been created."<<endl;

    s = shm;
////////////////////////////////////////////////////////////////////7
/////queue SECTION //////////////////////////////////////////////////
  mqd_t qd_server, qd_client;   // queue descriptors
  int token_number = 1; // next token to be given to client
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
  char out_buffer [MSG_BUFFER_SIZE];

/////////////////////////////////////////////////////////////////////

    /* open, read, and display the message from the FIFO */


    while(true){
      fd = open(myfifo, O_RDONLY);
      read(fd, &data, MAX_BUF);
      incoming_value = data - '0';
      cout<<"Received number: "<<incoming_value<<" -> ";

      //analyze_data(incoming_value);

      if(odds(incoming_value)){//Añadimos el char que identifica el numero
        cout<<"Par -> Shared Memeory"<<endl;
        *s++ = data;
      }
      else{//Using queues
        cout<<"Impar -> Queue"<<endl;
        if (mq_receive (qd_server, in_buffer, MSG_BUFFER_SIZE, NULL) == -1) {
            perror ("Server: mq_receive");
            exit (1);
        }

        //printf ("Server: message received.\n");
        //printf ("Client: %s\n",in_buffer);

        if ((qd_client = mq_open (in_buffer, O_WRONLY)) == 1) {
            perror ("Server: Not able to open client queue");
            continue;
        }

        //sprintf (out_buffer, "%ld", token_number);
        token_number = data - '0';
        sprintf (out_buffer, "%ld", token_number);

        if (mq_send (qd_client, out_buffer, strlen (out_buffer), 0) == -1) {
            perror ("Server: Not able to send message to client");
            continue;
        }
        //printf ("Server: response sent to client.\n");
        token_number++;
      }

      *s = NULL;
      close(fd);
      sleep(1);
    }

    return 0;
}

void analyze_data(int x){
  if(x %2 == 0){
    cout<<"  Par"<<endl;
  }
  else{
    cout<<"  Impar"<<endl;
  }
}

bool odds(int x){
  return(x%2 == 0);
}
