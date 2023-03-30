#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int resource = 0;

void *thread_1(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        if (resource == 0) {
            printf("Thread 1 acquired the resource\n");
            resource = 1;
            sleep(1);
        }
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void *thread_2(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        if (resource == 1) {
            printf("Thread 2 acquired the resource\n");
            resource = 0;
            sleep(1);
        }
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[2];
    int i;

    for (i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, (i == 0 ? thread_1 : thread_2), NULL);
    }

    for (i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
