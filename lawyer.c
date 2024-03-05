#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define C 5 // number of chairs in the waiting room
#define U 10 // number of clients

sem_t waiting_room; // binary semaphore to protect the waiting room
sem_t chairs; // C chairs queue
sem_t lawyer_office; // binary semaphore to protect the lawyer's office

void *client(void *arg) {
    int id = *(int *) arg;
    
    sleep(rand() % 5); // simulate client's arrival
    
    printf("Client %d wants to enters the waiting room.\n", id);
    
    sem_wait(&chairs); // enter critical section
    
    printf("Client %d sits on a chair and waits.\n", id);
    
    sem_post(&waiting_room); // signal the lawyer that we arrived

    sem_wait(&lawyer_office); // wait to enter to the office
    
    sem_post(&chairs); // on libère la chaise 
    
    printf("Client %d is being served.\n", id);
    sleep(rand() % 5); // simulate time with the client
    
    sem_post(&waiting_room); // on quitte le cabinet

    
    printf("Client %d quit the office.\n", id);
}

void *lawyer(void *arg) {
    while (1) {
        printf("The lawyer is sleeping in the office.\n");
        
        sem_wait(&waiting_room); // wait for a client
        
        

        sem_post(&lawyer_office); // kick the client
        
        
        
        printf("The lawyer is awake and ready to serve.\n");
    }
}

int main() {
    srand(time(NULL));
    
    sem_init(&waiting_room, 0, 0);
    sem_init(&lawyer_office, 0, 1);
    sem_init(&chairs, 0, 5);
    
    pthread_t lawyer_thread;
    pthread_create(&lawyer_thread, NULL, lawyer, NULL);
    
    pthread_t client_threads[U];
    int client_ids[U];
    for (int i = 0; i < U; i++) {
        client_ids[i] = i+1;
        pthread_create(&client_threads[i], NULL, client, &client_ids[i]);
    }
    
    pthread_join(lawyer_thread, NULL);
    
    for (int i = 0; i < U; i++) {
        pthread_join(client_threads[i], NULL);
    }
    
    sem_destroy(&waiting_room);
    sem_destroy(&lawyer_office);
    sem_destroy(&chairs);
    
    return 0;
}
