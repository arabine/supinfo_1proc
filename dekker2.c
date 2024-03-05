#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

pthread_t tid[2];
int counter; // critical section

bool wants_to_enter[2] = { false };
int prefered_thread = 0;

void* doSomeThing(void *arg)
{    
    int me = *(int*)(arg);
    int other = (me + 1) % 2; // other thread
    printf("Me: %d, other: %d\n", me, other);
    
    
    do 
    {
    clock_t start, end;
    double cpu_time_used;
    start = clock();
   
    
    wants_to_enter[me] = false;
    while (wants_to_enter[other] == false) {
        wants_to_enter[me] = true;
        while (prefered_thread == other) 
        wants_to_enter[me] = false;
    }
    
     /*
    wants_to_enter[me] = true;
    
   
    while (wants_to_enter[other] == true) {
 
        // if 2nd thread is more favored
        if (prefered_thread == other) {

            // gives access to other thread
            wants_to_enter[me] = false;

            // wait until this thread is favored
            while (prefered_thread != me);

            wants_to_enter[me] = true;
        }
    }
    */
    
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    // ================= CRITICAL SECTION =================
 
    
    printf("\n Thread %d started with counter = %d, waited time: %f\n", me, counter, cpu_time_used);
    counter += 1;
    for(int i=0; i<(0xFFFFFFF);i++);
    printf("\n Thread %d finished with counter = %d\n", me, counter);
 
    prefered_thread = other;
    wants_to_enter[me] = true;
    /*
 
    // favor the 2nd thread
    prefered_thread = other;

    // exit section
    // indicate thread1 has completed
    // its critical section
    wants_to_enter[me] = false;
    */
  
    // ================= REMINDER SECTION =================
    
    } while(1);

    return NULL;
}

int main(void)
{
    int t1 = 0;
    int t2 = 1;
    int err;

    err = pthread_create(&(tid[0]), NULL, &doSomeThing, &t1);
    if (err != 0)
        printf("\ncan't create thread :[%s]", strerror(err));
    
    err = pthread_create(&(tid[1]), NULL, &doSomeThing, &t2);
    if (err != 0)
        printf("\ncan't create thread :[%s]", strerror(err));
    
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    return 0;
}
