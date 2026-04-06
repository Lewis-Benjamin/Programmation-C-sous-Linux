#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define TAILLE 10

char buffer[TAILLE];
int sommet = -1;

sem_t vide, plein;
pthread_mutex_t mutex;

void *producteur(void *arg);
void *consommateur(void *arg);

int main()
{
    int N, M;

    printf("Nombre de producteurs : ");
    scanf("%d", &N);

    printf("Nombre de consommateurs : ");
    scanf("%d", &M);

    pthread_t prod[N], cons[M];
    int id_prod[N], id_cons[M];

    srand(time(NULL));

    // Initialisation
    sem_init(&vide, 0, TAILLE);
    sem_init(&plein, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Création producteurs
    for (int i = 0; i < N; i++)
    {
        id_prod[i] = i + 1;
        pthread_create(&prod[i], NULL, producteur, &id_prod[i]);
    }

    // Création consommateurs
    for (int i = 0; i < M; i++) {
        id_cons[i] = i + 1;
        pthread_create(&cons[i], NULL, consommateur, &id_cons[i]);
    }

    // Attente (boucle infinie ici)
    for (int i = 0; i < N; i++)
        pthread_join(prod[i], NULL);

    for (int i = 0; i < M; i++)
        pthread_join(cons[i], NULL);

    // Destruction
    sem_destroy(&vide);
    sem_destroy(&plein);
    pthread_mutex_destroy(&mutex);

    return 0;
}

void *producteur(void *arg)
{
    int id = *((int *)arg);

    while (1)
    {
        sleep((rand() % 3) + 1);

        char item = 'A' + (rand() % 26);

        sem_wait(&vide);            // attendre place libre
        pthread_mutex_lock(&mutex);

        sommet++;
        buffer[sommet] = item;
        printf("[Prod %d] produit %c (sommet=%d)\n", id, item, sommet);

        pthread_mutex_unlock(&mutex);
        sem_post(&plein);           // signaler élément dispo
    }
    return NULL;
}

void *consommateur(void *arg)
{
    int id = *((int *)arg);

    while (1)
    {
        sleep((rand() % 3) + 1);

        sem_wait(&plein);           // attendre élément
        pthread_mutex_lock(&mutex);

        char item = buffer[sommet];
        sommet--;
        printf("[Cons %d] consomme %c (sommet=%d)\n", id, item, sommet);

        pthread_mutex_unlock(&mutex);
        sem_post(&vide);            // libérer place
    }
    return NULL;
}