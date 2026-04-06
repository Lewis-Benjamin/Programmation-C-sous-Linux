#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

int N;                      // nombre de threads
int compteur = 0;            // threads arrivés au rendez-vous
pthread_mutex_t lock;
sem_t sem_rdv;

void *thread_rdv(void *arg)
{
    int id = *((int *)arg);

    while (1) {
        int t = (rand() % 5) + 1; // 1 à 5 sec
        printf("[Thread %d] traitement %d sec\n", id, t);
        sleep(t);

        pthread_mutex_lock(&lock);
        compteur++;
        if (compteur == N) {
            // tous les threads sont arrivés -> réveiller tous
            for (int i = 0; i < N; i++) sem_post(&sem_rdv);
            compteur = 0; // réinitialiser pour prochaine itération
        }
        pthread_mutex_unlock(&lock);

        sem_wait(&sem_rdv); // attendre que tous arrivent
        printf("[Thread %d] continue après rendez-vous\n", id);

        sleep(1); // on peut répéter ou finir
        break;    // une seule itération pour exemple
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <nombre_threads>\n", argv[0]);
        return 1;
    }

    N = atoi(argv[1]);
    if (N <= 1)
    {
        printf("N doit être >= 2\n");
        return 1;
    }

    pthread_t threads[N];
    int ids[N];
    pthread_mutex_init(&lock, NULL);
    sem_init(&sem_rdv, 0, 0);
    srand(time(NULL));

    for (int i = 0; i < N; i++)
    {
        ids[i] = i+1;
        pthread_create(&threads[i], NULL, thread_rdv, &ids[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(threads[i], NULL);

    pthread_mutex_destroy(&lock);
    sem_destroy(&sem_rdv);

    return 0;
}