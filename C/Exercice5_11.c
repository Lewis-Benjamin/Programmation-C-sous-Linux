#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define TAILLE 15

char base[TAILLE];
int nb_lecteurs = 0;

pthread_mutex_t mutex;
sem_t wrt;

void *lecteur(void *arg);
void *redacteur(void *arg);

int main()
{
    int N, M;
    pthread_t lecteurs[N], redacteurs[M];
    int idL[N], idR[M];

    printf("Nombre de lecteurs : ");
    scanf("%d", &N);

    printf("Nombre de redacteurs : ");
    scanf("%d", &M);
  
    srand(time(NULL));

    // Initialisation base à 0
    for (int i = 0; i < TAILLE; i++)
        base[i] = 0;

    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt, 0, 1);

    // Création lecteurs
    for (int i = 0; i < N; i++)
    {
        idL[i] = i + 1;
        pthread_create(&lecteurs[i], NULL, lecteur, &idL[i]);
    }

    // Création rédacteurs
    for (int i = 0; i < M; i++)
    {
        idR[i] = i + 1;
        pthread_create(&redacteurs[i], NULL, redacteur, &idR[i]);
    }

    // Attente infinie
    for (int i = 0; i < N; i++)
        pthread_join(lecteurs[i], NULL);

    for (int i = 0; i < M; i++)
        pthread_join(redacteurs[i], NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}

void *lecteur(void *arg)
{
    int id = *((int *)arg);
    int index;

    while (1)
    {
        sleep((rand() % 3) + 1);

        // Entrée section lecture
        pthread_mutex_lock(&mutex);
        nb_lecteurs++;
        if (nb_lecteurs == 1)
            sem_wait(&wrt);  // premier lecteur bloque écrivains
        pthread_mutex_unlock(&mutex);

        // Lecture
        index = rand() % TAILLE;
        printf("[Lecteur %d] lit base[%d] = %d\n", id, index, base[index]);

        // Sortie section lecture
        pthread_mutex_lock(&mutex);
        nb_lecteurs--;
        if (nb_lecteurs == 0)
            sem_post(&wrt);  // dernier lecteur libère écrivains
        pthread_mutex_unlock(&mutex);
    }
}

void *redacteur(void *arg)
{
    int id = *((int *)arg);
    int index;

    while (1)
    {
        sleep((rand() % 10) + 1);

        sem_wait(&wrt); // accès exclusif

        index = rand() % TAILLE;
        base[index] = rand() % 100;

        printf("[Redacteur %d] écrit base[%d] = %d\n", id, index, base[index]);

        sem_post(&wrt);
    }
}