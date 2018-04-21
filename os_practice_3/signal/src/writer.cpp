#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


using namespace std;
int random_number = 0;
char* myfifo = "/tmp/myfifo";
int fd;

void singhandler(int);

int main(){

  mkfifo(myfifo, 0666);

  signal(SIGUSR1, singhandler);
  cout<<"Id: "<<getpid()<<endl;

  //int i = 40;
  while(true/*i > 0*/){
    cout<<"."<<endl;
    //i--;
    sleep(1);
  }

  unlink(myfifo);
  return 0;
}

void singhandler(int signum){
  cout<<"Signal received: "<<signum<<endl;
  random_number = rand()%9 + 1;
  char tempo = random_number + '0';
  cout<<"Generated number: "<<tempo<<endl;


  fd = open(myfifo, O_WRONLY);
  write(fd, &tempo, sizeof(char) );
  close(fd);

}

//It cannot be compiled with atom. Only from cygwin
//SIGUSR1 = 30;
//SIGUSR2= 31;
