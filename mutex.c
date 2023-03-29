#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

void *increment_counter(void *arg) {
    int i;
    for (i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutex);
        counter++;
        printf("Thread %ld incremented counter to %d\n", (long) arg, counter);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[2];
    int i;

    for (i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, increment_counter, (void *) i);
    }

    for (i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
