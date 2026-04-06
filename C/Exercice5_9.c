#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

char buffer;        // variable globale (1 octet)
sem_t vide, plein;

// Émetteur
void *emetteur(void *arg)
{
    while (1) {
        sleep((rand() % 3) + 1);

        char c = 'A' + (rand() % 26);

        sem_wait(&vide);

        buffer = c;
        printf("[Emetteur] envoie : %c\n", c);

        sem_post(&plein);
    }
    return NULL;
}

// Récepteur
void *recepteur(void *arg)
{
    while (1) {
        sem_wait(&plein);

        char c = buffer;
        printf("[Recepteur] reçoit : %c\n", c);

        sem_post(&vide);

        sleep((rand() % 3) + 1);
    }
    return NULL;
}

int main()
{
    pthread_t th1, th2;
    srand(time(NULL));

    sem_init(&vide, 0, 1);
    sem_init(&plein, 0, 0);

    pthread_create(&th1, NULL, emetteur, NULL);
    pthread_create(&th2, NULL, recepteur, NULL);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    sem_destroy(&vide);
    sem_destroy(&plein);

    return 0;
}