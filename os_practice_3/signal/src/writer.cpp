#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <mutex>
#include <thread>

using namespace std;
//int temporal_number = 0;
sig_atomic_t temporal_number = 0;

int random_number = 0;
char* myfifo = "/tmp/myfifo";
int fd;
mutex candado;

void singhandler(int);
void fifo_function();
void fifo_function_v2(int);


mutex stop_work;

int main(){

  //pid_t retrieval_id = getpid();
  ///mkfifo(myfifo, 0666);

  signal(SIGUSR1, singhandler);
  cout<<"Id: "<<getpid()<<endl;

  int i = 0;
  while(true/*i > 0*/){
    if(temporal_number > 0){
      random_number = rand()%10 + 1;
      thread(fifo_function_v2, random_number).detach();
      cout<<"Reducing queue: "<<i++<<endl;
      //fifo_function();
      //thread(fifo_function).detach();
      temporal_number--;
    }
    //cout<<".  "<<retrieval_id<<endl;
    //i--;
    //sleep(1);
  }

  ///unlink(myfifo);
  return 0;
}

void singhandler(int signum){
  stop_work.lock();
  temporal_number++;
  //cout<<"TN: "<<temporal_number<<endl;
  ///cout<<"Signal received: "<<signum<<endl;
  ///random_number = rand()%5 + 1;
  ///char tempo = random_number + '0';
  ///cout<<"Generated number: "<<tempo<<endl;

  ///fd = open(myfifo, O_WRONLY);
  ///write(fd, &tempo, sizeof(char) );
  ///close(fd);

  stop_work.unlock();
}


void fifo_function(){
  random_number = rand()%5 + 1;
  char tempo = random_number + '0';

  fd = open(myfifo, O_WRONLY);
  write(fd, &tempo, sizeof(char));
  close(fd);
}

void  fifo_function_v2(int incoming_value){
  candado.lock();
  char tempo = random_number + '0';
  fd = open(myfifo, O_WRONLY);
  write(fd, &tempo, sizeof(char));
  close(fd);
  candado.unlock();
}
//It cannot be compiled with atom. Only from cygwin
//SIGUSR1 = 30;
//SIGUSR2= 31;
