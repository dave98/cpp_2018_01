#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <thread>

using namespace std;

int main(){
  int target_id = 0;
  int signal_number = 30;
  int sent_signal = 0;
  //int i = 20;

  cout<<"Waiting for signal ID process: "<<endl;
  cin>>target_id;
  cout<<"Number of signals to send: "<<endl;
  cin>>sent_signal;


  int i = 0;
  //while(true){
  while(i <  sent_signal){
    cout<<"Signal N: "<<++i<<" "<<signal_number<<endl;
    thread(kill, target_id, signal_number).detach();
    //kill(target_id, signal_number);//Envia la señal, funcion kill
    //sleep(1);
  }
  return 0;
}


/*kill(pit_id id, int sig)
pit_id:
 pit_id > 0 : Send to the process with pit_id.
 pit_id = 0 : The signal is sent to every process in  the process group of the calling process
 pit_id = -1 : Send to every process for wihch the calling process has permission to send signals exept for process 1(Init)/(Don't use)
 pit_id < -1 : then sig	 is  sent  to  every  process  in  the process group whose ID is -pid.

*/


//Informe [Parcial Practico]
