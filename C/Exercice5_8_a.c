#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define ITER 10

sem_t sem_T1, sem_T2;

// Thread 1
void *thread1(void *arg)
{
    for (int i = 0; i < ITER; i++) {
        printf("[T1] itération %d : début traitement\n", i+1);
        sleep(2); // traitement 2 sec
        printf("[T1] itération %d : fin traitement, attend T2\n", i+1);

        // signal à T2 que T1 a fini
        sem_post(&sem_T2);

        // attendre que T2 ait fini
        sem_wait(&sem_T1);
    }
    return NULL;
}

// Thread 2
void *thread2(void *arg)
{
    for (int i = 0; i < ITER; i++)
    {
        // attendre que T1 ait fini
        sem_wait(&sem_T2);

        int t = (rand() % 6) + 4; // 4 à 9 sec
        printf("[T2] itération %d : traitement %d sec\n", i+1, t);
        sleep(t);

        // signal à T1 que T2 a fini
        sem_post(&sem_T1);
    }
    return NULL;
}

int main()
{
    pthread_t th1, th2;
    srand(time(NULL));

    // Initialisation des sémaphores
    sem_init(&sem_T1, 0, 0);
    sem_init(&sem_T2, 0, 0);

    pthread_create(&th1, NULL, thread1, NULL);
    pthread_create(&th2, NULL, thread2, NULL);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    sem_destroy(&sem_T1);
    sem_destroy(&sem_T2);

    return 0;
}