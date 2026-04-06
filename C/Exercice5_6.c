#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define N 100

double tableau[N];
pthread_mutex_t lock;

// Thread 1 : calcul des moyennes
void *moyenne(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&lock);

        // Tableau temporaire pour stocker les nouvelles valeurs
        double tmp[N];
        tmp[0] = tableau[0];
        tmp[N-1] = tableau[N-1];

        for (int i = 1; i < N-1; i++)
        {
            tmp[i] = (tableau[i-1] + tableau[i] + tableau[i+1]) / 3.0;
        }

        // Copier dans le tableau global
        for (int i = 1; i < N-1; i++)
            tableau[i] = tmp[i];

        pthread_mutex_unlock(&lock);

        // attente aléatoire 1 à 3 secondes
        int t = (rand() % 3) + 1;
        sleep(t);
    }
    return NULL;
}

// Thread 2 : affichage
void *afficher(void *arg)
{
    while (1)
    {
        sleep(4);

        pthread_mutex_lock(&lock);
        printf("Tableau : ");
        for (int i = 0; i < N; i++)
            printf("%.2f ", tableau[i]);
        printf("\n");
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main()
{
    srand(time(NULL));
    pthread_t th1, th2;
    pthread_mutex_init(&lock, NULL);

    // Initialisation du tableau
    tableau[0] = 0;
    tableau[N-1] = 0;
    for (int i = 1; i < N-1; i++)
        tableau[i] = ((double)rand() / RAND_MAX) * 100;

    // Création des threads
    pthread_create(&th1, NULL, moyenne, NULL);
    pthread_create(&th2, NULL, afficher, NULL);

    // Attendre indéfiniment (ou Ctrl+C pour arrêter)
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    pthread_mutex_destroy(&lock);
    return 0;
}
