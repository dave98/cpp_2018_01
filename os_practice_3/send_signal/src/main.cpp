#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>

using namespace std;

int main(){
  int target_id = 0;
  int signal_number = 30;
  //int i = 20;

  cout<<"Waiting for signal ID process: "<<endl;
  cin>>target_id;

  while(true){
    cout<<"Sending a signal: "<<signal_number<<endl;
    kill(target_id, signal_number);
    sleep(1);
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
