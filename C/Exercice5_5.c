#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int compt = 0;             // compteur global
pthread_mutex_t lock;      // mutex
int limite;                // valeur limite

// Thread 1 : incrémente le compteur
void *incrementer(void *arg)
{
    while (1)
    {
        int t;
        pthread_mutex_lock(&lock);
        if (compt >= limite)
        {
            pthread_mutex_unlock(&lock);
            break;
        }
        compt++;
        printf("[Thread incrémentation] compteur = %d\n", compt);
        pthread_mutex_unlock(&lock);

        // attendre un temps aléatoire entre 1 et 5 sec
        t = (rand() % 5) + 1;
        sleep(t);
    }
    return NULL;
}

// Thread 2 : affiche le compteur toutes les 2 sec
void *afficher(void *arg)
{
    while (1)
    {
        sleep(2);

        pthread_mutex_lock(&lock);
        if (compt >= limite)
        {
            pthread_mutex_unlock(&lock);
            break;
        }
        printf("[Thread affichage] compteur = %d\n", compt);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t th1, th2;
    if (argc != 2)
    {
        printf("Usage: %s <valeur_limite>\n", argv[0]);
        return 1;
    }

    limite = atoi(argv[1]);
    if (limite <= 0)
    {
        printf("La limite doit être un entier positif.\n");
        return 1;
    }

    srand(time(NULL));

    pthread_mutex_init(&lock, NULL);

    // création des threads
    pthread_create(&th1, NULL, incrementer, NULL);
    pthread_create(&th2, NULL, afficher, NULL);

    // attendre la fin
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    pthread_mutex_destroy(&lock);

    printf("Compteur final = %d\n", compt);
    return 0;
}