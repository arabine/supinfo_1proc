#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_t tid[2];
int counter;

int thread_number = 0;

void* doSomeThing(void *arg)
{
    unsigned long i = 0;
    
    int t = *(int*)(arg);
    
    do {
    
    clock_t start, end;
    double cpu_time_used;

    start = clock();
   
   
    
    while (thread_number != t);
    
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    
    printf("\n Thread %d started with counter = %d, waited time: %f\n", t, counter, cpu_time_used);

    counter += 1;
    for(i=0; i<(0xFFFFFFF);i++);
    printf("\n Thread %d finished with counter = %d\n", t, counter);
    
    thread_number = (++thread_number) %2;
    
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
