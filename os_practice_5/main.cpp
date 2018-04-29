#include <stdio.h>
#include <vector>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;

using namespace std;

void* thread(int x)
{
    //wait
    //sem_wait(&mutex);
    printf("\nEntered..%d\n", x);

    //critical section
    sleep(2);

    //signal
    printf("\nJust Exiting...%d\n", x);
    //sem_post(&mutex);
}


int main()
{
    int number = 1;
    sem_init(&mutex, 0, 1);
    pthread_t t1,t2;
    vector<pthread_t> a;
    for(unsigned int i = 0; i < 10; i++){
      pthread_t temp;
      pthread_create(&temp, NULL, thread, number);
      number++;
      a.push_back(temp);
    }

    for(unsigned int i = 0; i < a.size(); i++){
      pthread_join(a[i], NULL);
    }
    //pthread_create(&t1,NULL,thread,NULL);
    //sleep(2);
    //pthread_create(&t2,NULL,thread,NULL);
    //pthread_join(t1,NULL);
    //pthread_join(t2,NULL);
    sem_destroy(&mutex);
    return 0;
}
