#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

double u = 1.0;           // variable globale
int compteur = 0;          // compteur global
pthread_mutex_t lock;      // mutex

// fonction f1(x) = (x-1)^2 / 4
double f1(double x)
{
    return ((x - 1) * (x - 1)) / 4.0;
}

// fonction f2(x) = (x-2)^2 / 6
double f2(double x)
{
    return ((x - 2) * (x - 2)) / 6.0;
}

// Thread T1
void *thread1(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&lock);
        compteur++;
        u = f1(u);
        printf("[T1] compteur = %d, u = %.5f\n", compteur, u);
        pthread_mutex_unlock(&lock);

        int t = (rand() % 5) + 1; // 1 à 5 sec
        sleep(t);
    }
    return NULL;
}

// Thread T2
void *thread2(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&lock);
        compteur++;
        u = f2(u);
        printf("[T2] compteur = %d, u = %.5f\n", compteur, u);
        pthread_mutex_unlock(&lock);

        int t = (rand() % 5) + 1;
        sleep(t);
    }
    return NULL;
}

int main()
{
    pthread_t th1, th2;
    srand(time(NULL));

    pthread_mutex_init(&lock, NULL);

    // Création des threads
    pthread_create(&th1, NULL, thread1, NULL);
    pthread_create(&th2, NULL, thread2, NULL);

    // Attente infinie (Ctrl+C pour arrêter)
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    pthread_mutex_destroy(&lock);

    return 0;
}